// Copyright (c) 2011 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include "include/cef.h"
#include "web_urlrequest_impl.h"
#include "cef_thread.h"
#include "request_impl.h"
#include "response_impl.h"

#include "base/logging.h"
#include "base/memory/scoped_ptr.h"
#include "googleurl/src/gurl.h"
#include "third_party/WebKit/Source/WebKit/chromium/public/WebURLError.h"
#include "third_party/WebKit/Source/WebKit/chromium/public/WebURLLoaderClient.h"
#include "third_party/WebKit/Source/WebKit/chromium/public/WebURLRequest.h"
#include "third_party/WebKit/Source/WebKit/chromium/public/WebURLResponse.h"
#include "webkit/glue/weburlloader_impl.h"

using WebKit::WebURLError;
using WebKit::WebURLLoader;
using WebKit::WebURLRequest;
using WebKit::WebURLResponse;

namespace {
class CefWebURLLoaderClientImpl;
};

// Manages the lifespan of WebKit objects. Methods of this class will only be
// called on the UI thread.
class CefWebURLRequestImpl::Context :
    public base::RefCountedThreadSafe<CefWebURLRequestImpl::Context,
                                      CefThread::DeleteOnUIThread>
{
public:
  Context(CefRefPtr<CefWebURLRequestImpl> client)
    : client_(client)
  {
  }
  virtual ~Context()
  {
  }

  void initialize(CefRefPtr<CefRequest> request);
  void destroy();
  void cancel();

  CefRefPtr<CefWebURLRequestImpl> client() { return client_; }

protected:
   CefRefPtr<CefWebURLRequestImpl> client_;
   scoped_ptr<webkit_glue::WebURLLoaderImpl> url_loader_;
   scoped_ptr<CefWebURLLoaderClientImpl> url_client_;
};


namespace {

// Implements the WebURLLoaderClient interface. Methods of this class will only
// be called on the UI thread.
class CefWebURLLoaderClientImpl : public WebKit::WebURLLoaderClient
{
public:
  CefWebURLLoaderClientImpl(CefWebURLRequestImpl::Context* context)
    : context_(context)
  {
  }
  virtual ~CefWebURLLoaderClientImpl()
  {
  }

  // =====================================================================
  // WebKit::WebURLLoaderClient API
  //

  // Called when following a redirect.  |newRequest| contains the request
  // generated by the redirect.  The client may modify |newRequest|.
  virtual void willSendRequest(WebKit::WebURLLoader*,
                               WebKit::WebURLRequest& newRequest, 
                               const WebKit::WebURLResponse& redirectResponse)
  {
    REQUIRE_UIT();
    if(!context_)
      return;

    CefRefPtr<CefWebURLRequestImpl> client = context_->client();
    if (client.get()) {
      CefRefPtr<CefWebURLRequestClient> handler = client->GetHandler();
      if (handler.get()) {
        CefRefPtr<CefRequestImpl> cefRequest(new CefRequestImpl());
        CefRefPtr<CefResponse> cefResponse(
            new CefResponseImpl(redirectResponse));

        cefRequest->Set(newRequest);
        handler->OnRedirect(client.get(), cefRequest.get(), cefResponse);
        cefRequest->Get(newRequest);
      }
    }
  }

  // Called to report upload progress.  The bytes reported correspond to
  // the HTTP message body.
  virtual void didSendData(WebKit::WebURLLoader*, unsigned long long bytesSent,
                           unsigned long long totalBytesToBeSent)
  {
    REQUIRE_UIT();
    if(!context_)
      return;

    CefRefPtr<CefWebURLRequestImpl> client = context_->client();
    if (client.get()) {
      CefRefPtr<CefWebURLRequestClient> handler = client->GetHandler();
      if (handler.get())
        handler->OnProgress(client.get(), bytesSent, totalBytesToBeSent);
    }
  }

  // Called when response headers are received.
  virtual void didReceiveResponse(WebKit::WebURLLoader*,
                                  const WebKit::WebURLResponse& response)
  {
    REQUIRE_UIT();
    if(!context_)
      return;

    CefRefPtr<CefWebURLRequestImpl> client = context_->client();
    if (client.get()) {
      client->DoStateChange(WUR_STATE_HEADERS_RECEIVED);
      CefRefPtr<CefWebURLRequestClient> handler = client->GetHandler();
      if (handler.get()) {
        CefRefPtr<CefResponse> cefResponse(new CefResponseImpl(response));
        handler->OnHeadersReceived(client.get(), cefResponse);
      }
    }
  }

  // Called when a chunk of response data is downloaded.  This is only called
  // if WebURLRequest's downloadToFile flag was set to true.
  virtual void didDownloadData(WebKit::WebURLLoader*, int dataLength)
  {
    NOTREACHED();
  }

  // Called when a chunk of response data is received.
  virtual void didReceiveData(WebURLLoader*, const char* data, int dataLength,
                              int lengthReceived)
  {
    REQUIRE_UIT();
    if(!context_)
      return;

    CefRefPtr<CefWebURLRequestImpl> client = context_->client();
    if (client.get()) {
      client->DoStateChange(WUR_STATE_LOADING);
      CefRefPtr<CefWebURLRequestClient> handler = client->GetHandler();
      if (handler.get()) {
        handler->OnData(client.get(), data, dataLength);
      }
    }
  }

  // Called when a chunk of renderer-generated metadata is received from 
  // the cache.
  virtual void didReceiveCachedMetadata(WebKit::WebURLLoader*, const char* data, 
                                        int dataLength)
  {
    NOTREACHED();
  }

  // Called when the load completes successfully.
  virtual void didFinishLoading(WebKit::WebURLLoader*, double finishTime)
  {
    REQUIRE_UIT();
    if(!context_)
      return;

    CefRefPtr<CefWebURLRequestImpl> client = context_->client();
    if (client.get())
      client->DoStateChange(WUR_STATE_DONE);

    complete();
  }

  // Called when the load completes with an error.
  virtual void didFail(WebKit::WebURLLoader*, const WebKit::WebURLError& error)
  {
    REQUIRE_UIT();
    if(!context_)
      return;

    CefRefPtr<CefWebURLRequestImpl> client = context_->client();
    if (client.get() && client->GetState() != WUR_STATE_ABORT) {
      client->DoStateChange(WUR_STATE_ERROR);
      CefRefPtr<CefWebURLRequestClient> handler = client->GetHandler();
      if (handler.get()) {
        handler->OnError(client.get(), 
            static_cast<CefWebURLRequestClient::ErrorCode>(error.reason));
      }
    }
    
    complete();
  }

  void complete()
  {
    context_->destroy();
    context_ = NULL;
  }

protected:
   scoped_refptr<CefWebURLRequestImpl::Context> context_;
};

} // namespace


// CefWebURLManager

void CefWebURLRequestImpl::Context::initialize(
    CefRefPtr<CefRequest> request)
{
  REQUIRE_UIT();

  url_loader_.reset(new webkit_glue::WebURLLoaderImpl());
  url_client_.reset(new CefWebURLLoaderClientImpl(this));

  WebURLRequest urlRequest;
  static_cast<CefRequestImpl*>(request.get())->Get(urlRequest);
  url_loader_->loadAsynchronously(urlRequest, url_client_.get());
}

void CefWebURLRequestImpl::Context::destroy()
{
  REQUIRE_UIT();
  client_ = NULL;
}

void CefWebURLRequestImpl::Context::cancel()
{
  REQUIRE_UIT();
  url_loader_->cancel();
  url_client_->complete();
}


// CefWebURLRequest

// static
CefRefPtr<CefWebURLRequest>
CefWebURLRequest::CreateWebURLRequest(
    CefRefPtr<CefRequest> request, CefRefPtr<CefWebURLRequestClient> client)
{
  CefRefPtr<CefWebURLRequestImpl> requester = new CefWebURLRequestImpl(client);

  // Send the request from the UI thread.
  CefThread::PostTask(CefThread::UI, FROM_HERE,
      NewRunnableMethod(requester.get(), &CefWebURLRequestImpl::DoSend,
                        request));

  return requester.get();
}


// CefWebURLRequestImpl

CefWebURLRequestImpl::CefWebURLRequestImpl(
    CefRefPtr<CefWebURLRequestClient> handler)
    : handler_(handler),
      state_(WUR_STATE_UNSENT)
{
}

CefWebURLRequestImpl::~CefWebURLRequestImpl()
{
}

CefWebURLRequestImpl::RequestState CefWebURLRequestImpl::GetState()
{
  AutoLock lock_scope(this);
  return state_;
}

void CefWebURLRequestImpl::Cancel()
{
  CefThread::PostTask(CefThread::UI, FROM_HERE,
      NewRunnableMethod(this, &CefWebURLRequestImpl::DoCancel));
}

void CefWebURLRequestImpl::DoSend(CefRefPtr<CefRequest> request)
{
  REQUIRE_UIT();
  DCHECK(state_ == WUR_STATE_UNSENT);

  context_ = new CefWebURLRequestImpl::Context(this);
  context_->initialize(request);

  DoStateChange(WUR_STATE_STARTED);
}

void CefWebURLRequestImpl::DoCancel()
{
  REQUIRE_UIT();

  if (state_ < WUR_STATE_DONE) {
    DoStateChange(WUR_STATE_ABORT);
    context_->cancel();
  }
}

void CefWebURLRequestImpl::DoStateChange(RequestState newState)
{
  REQUIRE_UIT();

  if (state_ == newState)
    return;

  {
    AutoLock lock_scope(this);
    state_ = newState;
  }

  if (handler_.get())
    handler_->OnStateChange(this, newState);
}
