// Copyright (c) 2008-2009 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "libcef/request_impl.h"

#include <string>
#include <vector>

#include "libcef/cef_thread.h"
#include "libcef/http_header_utils.h"

#include "base/logging.h"
#include "net/base/upload_data.h"
#include "net/base/upload_data_stream.h"
#include "net/base/upload_element_reader.h"
#include "net/base/upload_bytes_element_reader.h"
#include "net/base/upload_file_element_reader.h"
#include "net/http/http_request_headers.h"
#include "net/url_request/url_request.h"
#include "third_party/WebKit/Source/Platform/chromium/public/WebURLRequest.h"

using WebKit::WebHTTPBody;
using WebKit::WebString;
using WebKit::WebURL;
using WebKit::WebURLRequest;

namespace {

// A subclass of net::UploadBytesElementReader that keeps the associated
// UploadElement alive until the request completes.
class BytesElementReader : public net::UploadBytesElementReader {
 public:
  explicit BytesElementReader(scoped_ptr<net::UploadElement> element)
      : net::UploadBytesElementReader(element->bytes(),
                                      element->bytes_length()),
        element_(element.Pass()) {
    DCHECK_EQ(net::UploadElement::TYPE_BYTES, element_->type());
  }

  virtual ~BytesElementReader() {}

 private:
  scoped_ptr<net::UploadElement> element_;

  DISALLOW_COPY_AND_ASSIGN(BytesElementReader);
};

// A subclass of net::UploadFileElementReader that keeps the associated
// UploadElement alive until the request completes.
class FileElementReader : public net::UploadFileElementReader {
 public:
  explicit FileElementReader(scoped_ptr<net::UploadElement> element)
      : net::UploadFileElementReader(
            CefThread::GetMessageLoopProxyForThread(CefThread::FILE),
            element->file_path(),
            element->file_range_offset(),
            element->file_range_length(),
            element->expected_file_modification_time()),
        element_(element.Pass()) {
    DCHECK_EQ(net::UploadElement::TYPE_FILE, element_->type());
  }

  virtual ~FileElementReader() {}

 private:
  scoped_ptr<net::UploadElement> element_;

  DISALLOW_COPY_AND_ASSIGN(FileElementReader);
};

}  // namespace


CefRefPtr<CefRequest> CefRequest::CreateRequest() {
  CefRefPtr<CefRequest> request(new CefRequestImpl());
  return request;
}

CefRequestImpl::CefRequestImpl()
    : method_("GET"),
      flags_(WUR_FLAG_NONE) {
}

CefString CefRequestImpl::GetURL() {
  AutoLock lock_scope(this);
  return url_;
}

void CefRequestImpl::SetURL(const CefString& url) {
  AutoLock lock_scope(this);
  url_ = url;
}

CefString CefRequestImpl::GetMethod() {
  AutoLock lock_scope(this);
  return method_;
}

void CefRequestImpl::SetMethod(const CefString& method) {
  AutoLock lock_scope(this);
  method_ = method;
}

CefRefPtr<CefPostData> CefRequestImpl::GetPostData() {
  AutoLock lock_scope(this);
  return postdata_;
}

void CefRequestImpl::SetPostData(CefRefPtr<CefPostData> postData) {
  AutoLock lock_scope(this);
  postdata_ = postData;
}

void CefRequestImpl::GetHeaderMap(HeaderMap& headerMap) {
  AutoLock lock_scope(this);
  headerMap = headermap_;
}

void CefRequestImpl::SetHeaderMap(const HeaderMap& headerMap) {
  AutoLock lock_scope(this);
  headermap_ = headerMap;
}

void CefRequestImpl::Set(const CefString& url,
                         const CefString& method,
                         CefRefPtr<CefPostData> postData,
                         const HeaderMap& headerMap) {
  AutoLock lock_scope(this);
  url_ = url;
  method_ = method;
  postdata_ = postData;
  headermap_ = headerMap;
}

void CefRequestImpl::Set(net::URLRequest* request) {
  AutoLock lock_scope(this);

  url_ = request->url().spec();
  method_ = request->method();

  net::HttpRequestHeaders headers = request->extra_request_headers();

  // Ensure that we do not send username and password fields in the referrer.
  GURL referrer(request->GetSanitizedReferrer());

  // Strip Referer from request_info_.extra_headers to prevent, e.g., plugins
  // from overriding headers that are controlled using other means. Otherwise a
  // plugin could set a referrer although sending the referrer is inhibited.
  headers.RemoveHeader(net::HttpRequestHeaders::kReferer);

  // Our consumer should have made sure that this is a safe referrer.  See for
  // instance WebCore::FrameLoader::HideReferrer.
  if (referrer.is_valid())
    headers.SetHeader(net::HttpRequestHeaders::kReferer, referrer.spec());

  // Transfer request headers
  GetHeaderMap(headers, headermap_);

  // Transfer post data, if any
  const net::UploadDataStream* data = request->get_upload();
  if (data) {
    postdata_ = CefPostData::CreatePostData();
    static_cast<CefPostDataImpl*>(postdata_.get())->Set(*data);
  }
}

void CefRequestImpl::Set(const WebKit::WebURLRequest& request) {
  DCHECK(!request.isNull());
  AutoLock lock_scope(this);

  url_ = request.url().spec().utf16();
  method_ = request.httpMethod();

  const WebHTTPBody& body = request.httpBody();
  if (!body.isNull()) {
    postdata_ = new CefPostDataImpl();
    static_cast<CefPostDataImpl*>(postdata_.get())->Set(body);
  } else if (postdata_.get()) {
    postdata_ = NULL;
  }

  headermap_.clear();
  GetHeaderMap(request, headermap_);

  int flags = WUR_FLAG_NONE;
  if (request.cachePolicy() == WebURLRequest::ReloadIgnoringCacheData)
    flags |= WUR_FLAG_SKIP_CACHE;
  if (request.allowStoredCredentials())
    flags |= WUR_FLAG_ALLOW_CACHED_CREDENTIALS;
  if (request.allowCookies())
    flags |= WUR_FLAG_ALLOW_COOKIES;
  if (request.reportUploadProgress())
    flags |= WUR_FLAG_REPORT_UPLOAD_PROGRESS;
  if (request.reportLoadTiming())
    flags |= WUR_FLAG_REPORT_LOAD_TIMING;
  if (request.reportRawHeaders())
    flags |= WUR_FLAG_REPORT_RAW_HEADERS;
  flags_ = static_cast<cef_weburlrequest_flags_t>(flags);

  first_party_for_cookies_ = request.firstPartyForCookies().spec().utf16();
}

#define SETBOOLFLAG(obj, flags, method, FLAG) \
    obj.method((flags & (FLAG)) == (FLAG))

void CefRequestImpl::Get(WebKit::WebURLRequest& request) {
  request.initialize();
  AutoLock lock_scope(this);

  std::string urlStr(url_);
  GURL gurl = GURL(urlStr);
  request.setURL(WebURL(gurl));

  std::string method(method_);
  request.setHTTPMethod(WebString::fromUTF8(method.c_str()));
  request.setTargetType(WebURLRequest::TargetIsMainFrame);

  WebHTTPBody body;
  if (postdata_.get()) {
    body.initialize();
    static_cast<CefPostDataImpl*>(postdata_.get())->Get(body);
    request.setHTTPBody(body);
  }

  SetHeaderMap(headermap_, request);

  request.setCachePolicy((flags_ & WUR_FLAG_SKIP_CACHE) ?
      WebURLRequest::ReloadIgnoringCacheData :
      WebURLRequest::UseProtocolCachePolicy);

  SETBOOLFLAG(request, flags_, setAllowStoredCredentials,
              WUR_FLAG_ALLOW_CACHED_CREDENTIALS);
  SETBOOLFLAG(request, flags_, setAllowCookies,
              WUR_FLAG_ALLOW_COOKIES);
  SETBOOLFLAG(request, flags_, setReportUploadProgress,
              WUR_FLAG_REPORT_UPLOAD_PROGRESS);
  SETBOOLFLAG(request, flags_, setReportLoadTiming,
              WUR_FLAG_REPORT_LOAD_TIMING);
  SETBOOLFLAG(request, flags_, setReportRawHeaders,
              WUR_FLAG_REPORT_RAW_HEADERS);

  if (!first_party_for_cookies_.empty()) {
    std::string cookiesStr(first_party_for_cookies_);
    GURL gurl = GURL(cookiesStr);
    request.setFirstPartyForCookies(WebURL(gurl));
  }
}

CefRequest::RequestFlags CefRequestImpl::GetFlags() {
  AutoLock lock_scope(this);
  return flags_;
}
void CefRequestImpl::SetFlags(RequestFlags flags) {
  AutoLock lock_scope(this);
  flags_ = flags;
}

CefString CefRequestImpl::GetFirstPartyForCookies() {
  AutoLock lock_scope(this);
  return first_party_for_cookies_;
}
void CefRequestImpl::SetFirstPartyForCookies(const CefString& url) {
  AutoLock lock_scope(this);
  first_party_for_cookies_ = url;
}

// static
void CefRequestImpl::GetHeaderMap(const net::HttpRequestHeaders& headers,
                                  HeaderMap& map) {
  net::HttpRequestHeaders::Iterator it(headers);
  do {
    map.insert(std::make_pair(it.name(), it.value()));
  } while (it.GetNext());
}

// static
void CefRequestImpl::GetHeaderMap(const WebKit::WebURLRequest& request,
                                  HeaderMap& map) {
  HttpHeaderUtils::HeaderVisitor visitor(&map);
  request.visitHTTPHeaderFields(&visitor);
}

// static
void CefRequestImpl::SetHeaderMap(const HeaderMap& map,
                                  WebKit::WebURLRequest& request) {
  HeaderMap::const_iterator it = map.begin();
  for (; it != map.end(); ++it)
    request.setHTTPHeaderField(string16(it->first), string16(it->second));
}

CefRefPtr<CefPostData> CefPostData::CreatePostData() {
  CefRefPtr<CefPostData> postdata(new CefPostDataImpl());
  return postdata;
}

CefPostDataImpl::CefPostDataImpl() {
}

size_t CefPostDataImpl::GetElementCount() {
  AutoLock lock_scope(this);
  return elements_.size();
}

void CefPostDataImpl::GetElements(ElementVector& elements) {
  AutoLock lock_scope(this);
  elements = elements_;
}

bool CefPostDataImpl::RemoveElement(CefRefPtr<CefPostDataElement> element) {
  AutoLock lock_scope(this);

  ElementVector::iterator it = elements_.begin();
  for (; it != elements_.end(); ++it) {
    if (it->get() == element.get()) {
      elements_.erase(it);
      return true;
    }
  }

  return false;
}

bool CefPostDataImpl::AddElement(CefRefPtr<CefPostDataElement> element) {
  bool found = false;

  AutoLock lock_scope(this);

  // check that the element isn't already in the list before adding
  ElementVector::const_iterator it = elements_.begin();
  for (; it != elements_.end(); ++it) {
    if (it->get() == element.get()) {
      found = true;
      break;
    }
  }

  if (!found)
    elements_.push_back(element);

  return !found;
}

void CefPostDataImpl::RemoveElements() {
  AutoLock lock_scope(this);
  elements_.clear();
}

void CefPostDataImpl::Set(const net::UploadData& data) {
  AutoLock lock_scope(this);

  CefRefPtr<CefPostDataElement> postelem;

  const ScopedVector<net::UploadElement>& elements = data.elements();
  ScopedVector<net::UploadElement>::const_iterator it = elements.begin();
  for (; it != elements.end(); ++it) {
    postelem = CefPostDataElement::CreatePostDataElement();
    static_cast<CefPostDataElementImpl*>(postelem.get())->Set(**it);
    AddElement(postelem);
  }
}

void CefPostDataImpl::Set(const net::UploadDataStream& data_stream) {
  AutoLock lock_scope(this);

  CefRefPtr<CefPostDataElement> postelem;

  const ScopedVector<net::UploadElementReader>& elements =
      data_stream.element_readers();
  ScopedVector<net::UploadElementReader>::const_iterator it = elements.begin();
  for (; it != elements.end(); ++it) {
    postelem = CefPostDataElement::CreatePostDataElement();
    static_cast<CefPostDataElementImpl*>(postelem.get())->Set(**it);
    AddElement(postelem);
  }
}

void CefPostDataImpl::Get(net::UploadData& data) {
  AutoLock lock_scope(this);

  ScopedVector<net::UploadElement> data_elements;
  ElementVector::iterator it = elements_.begin();
  for (; it != elements_.end(); ++it) {
    net::UploadElement* element = new net::UploadElement();
    static_cast<CefPostDataElementImpl*>(it->get())->Get(*element);
    data_elements.push_back(element);
  }
  data.swap_elements(&data_elements);
}

net::UploadDataStream* CefPostDataImpl::Get() {
  AutoLock lock_scope(this);

  ScopedVector<net::UploadElementReader> element_readers;
  ElementVector::const_iterator it = elements_.begin();
  for (; it != elements_.end(); ++it) {
    element_readers.push_back(
        static_cast<CefPostDataElementImpl*>(it->get())->Get());
  }

  return new net::UploadDataStream(&element_readers, 0);
}

void CefPostDataImpl::Set(const WebKit::WebHTTPBody& data) {
  AutoLock lock_scope(this);

  CefRefPtr<CefPostDataElement> postelem;
  WebKit::WebHTTPBody::Element element;
  size_t size = data.elementCount();
  for (size_t i = 0; i < size; ++i) {
    if (data.elementAt(i, element)) {
      postelem = CefPostDataElement::CreatePostDataElement();
      static_cast<CefPostDataElementImpl*>(postelem.get())->Set(element);
      AddElement(postelem);
    }
  }
}

void CefPostDataImpl::Get(WebKit::WebHTTPBody& data) {
  AutoLock lock_scope(this);

  WebKit::WebHTTPBody::Element element;
  ElementVector::iterator it = elements_.begin();
  for (; it != elements_.end(); ++it) {
    static_cast<CefPostDataElementImpl*>(it->get())->Get(element);
    if (element.type == WebKit::WebHTTPBody::Element::TypeData) {
      data.appendData(element.data);
    } else if (element.type == WebKit::WebHTTPBody::Element::TypeFile) {
      data.appendFile(element.filePath);
    } else {
      NOTREACHED();
    }
  }
}

CefRefPtr<CefPostDataElement> CefPostDataElement::CreatePostDataElement() {
  CefRefPtr<CefPostDataElement> element(new CefPostDataElementImpl());
  return element;
}

CefPostDataElementImpl::CefPostDataElementImpl() {
  type_ = PDE_TYPE_EMPTY;
  memset(&data_, 0, sizeof(data_));
}

CefPostDataElementImpl::~CefPostDataElementImpl() {
  SetToEmpty();
}

void CefPostDataElementImpl::SetToEmpty() {
  AutoLock lock_scope(this);
  if (type_ == PDE_TYPE_BYTES)
    free(data_.bytes.bytes);
  else if (type_ == PDE_TYPE_FILE)
    cef_string_clear(&data_.filename);
  type_ = PDE_TYPE_EMPTY;
  memset(&data_, 0, sizeof(data_));
}

void CefPostDataElementImpl::SetToFile(const CefString& fileName) {
  AutoLock lock_scope(this);
  // Clear any data currently in the element
  SetToEmpty();

  // Assign the new data
  type_ = PDE_TYPE_FILE;
  cef_string_copy(fileName.c_str(), fileName.length(), &data_.filename);
}

void CefPostDataElementImpl::SetToBytes(size_t size, const void* bytes) {
  AutoLock lock_scope(this);
  // Clear any data currently in the element
  SetToEmpty();

  // Assign the new data
  void* data = malloc(size);
  DCHECK(data != NULL);
  if (data == NULL)
    return;

  memcpy(data, bytes, size);

  type_ = PDE_TYPE_BYTES;
  data_.bytes.bytes = data;
  data_.bytes.size = size;
}

CefPostDataElement::Type CefPostDataElementImpl::GetType() {
  AutoLock lock_scope(this);
  return type_;
}

CefString CefPostDataElementImpl::GetFile() {
  AutoLock lock_scope(this);
  DCHECK(type_ == PDE_TYPE_FILE);
  CefString filename;
  if (type_ == PDE_TYPE_FILE)
    filename.FromString(data_.filename.str, data_.filename.length, false);
  return filename;
}

size_t CefPostDataElementImpl::GetBytesCount() {
  AutoLock lock_scope(this);
  DCHECK(type_ == PDE_TYPE_BYTES);
  size_t size = 0;
  if (type_ == PDE_TYPE_BYTES)
    size = data_.bytes.size;
  return size;
}

size_t CefPostDataElementImpl::GetBytes(size_t size, void* bytes) {
  AutoLock lock_scope(this);
  DCHECK(type_ == PDE_TYPE_BYTES);
  size_t rv = 0;
  if (type_ == PDE_TYPE_BYTES) {
    rv = (size < data_.bytes.size ? size : data_.bytes.size);
    memcpy(bytes, data_.bytes.bytes, rv);
  }
  return rv;
}

void CefPostDataElementImpl::Set(const net::UploadElement& element) {
  AutoLock lock_scope(this);

  if (element.type() == net::UploadElement::TYPE_BYTES) {
    SetToBytes(element.bytes_length(), element.bytes());
  } else if (element.type() == net::UploadElement::TYPE_FILE) {
    SetToFile(element.file_path().value());
  } else {
    NOTREACHED();
  }
}

void CefPostDataElementImpl::Set(
    const net::UploadElementReader& element_reader) {
  AutoLock lock_scope(this);

  const net::UploadBytesElementReader* bytes_reader =
      element_reader.AsBytesReader();
  if (bytes_reader) {
    SetToBytes(bytes_reader->length(), bytes_reader->bytes());
    return;
  }

  const net::UploadFileElementReader* file_reader =
      element_reader.AsFileReader();
  if (file_reader) {
    SetToFile(file_reader->path().value());
    return;
  }

  NOTREACHED();
}

void CefPostDataElementImpl::Get(net::UploadElement& element) {
  AutoLock lock_scope(this);

  if (type_ == PDE_TYPE_BYTES) {
    element.SetToBytes(static_cast<char*>(data_.bytes.bytes), data_.bytes.size);
  } else if (type_ == PDE_TYPE_FILE) {
    base::FilePath path = base::FilePath(CefString(&data_.filename));
    element.SetToFilePath(path);
  } else {
    NOTREACHED();
  }
}

net::UploadElementReader* CefPostDataElementImpl::Get() {
  AutoLock lock_scope(this);

  if (type_ == PDE_TYPE_BYTES) {
    net::UploadElement* element = new net::UploadElement();
    element->SetToBytes(static_cast<char*>(data_.bytes.bytes),
                        data_.bytes.size);
    return new BytesElementReader(make_scoped_ptr(element));
  } else if (type_ == PDE_TYPE_FILE) {
    net::UploadElement* element = new net::UploadElement();
    base::FilePath path = base::FilePath(CefString(&data_.filename));
    element->SetToFilePath(path);
    return new FileElementReader(make_scoped_ptr(element));
  } else {
    NOTREACHED();
    return NULL;
  }
}

void CefPostDataElementImpl::Set(const WebKit::WebHTTPBody::Element& element) {
  AutoLock lock_scope(this);

  if (element.type == WebKit::WebHTTPBody::Element::TypeData) {
    SetToBytes(element.data.size(),
        static_cast<const void*>(element.data.data()));
  } else if (element.type == WebKit::WebHTTPBody::Element::TypeFile) {
    SetToFile(string16(element.filePath));
  } else {
    NOTREACHED();
  }
}

void CefPostDataElementImpl::Get(WebKit::WebHTTPBody::Element& element) {
  AutoLock lock_scope(this);

  if (type_ == PDE_TYPE_BYTES) {
    element.type = WebKit::WebHTTPBody::Element::TypeData;
    element.data.assign(
        static_cast<char*>(data_.bytes.bytes), data_.bytes.size);
  } else if (type_ == PDE_TYPE_FILE) {
    element.type = WebKit::WebHTTPBody::Element::TypeFile;
    element.filePath.assign(string16(CefString(&data_.filename)));
  } else {
    NOTREACHED();
  }
}
