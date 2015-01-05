// Copyright (c) 2015 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the CEF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//

#ifndef CEF_LIBCEF_DLL_CTOCPP_DOWNLOAD_ITEM_CTOCPP_H_
#define CEF_LIBCEF_DLL_CTOCPP_DOWNLOAD_ITEM_CTOCPP_H_
#pragma once

#ifndef USING_CEF_SHARED
#pragma message("Warning: "__FILE__" may be accessed wrapper-side only")
#else  // USING_CEF_SHARED

#include "include/cef_download_item.h"
#include "include/capi/cef_download_item_capi.h"
#include "libcef_dll/ctocpp/ctocpp.h"

// Wrap a C structure with a C++ class.
// This class may be instantiated and accessed wrapper-side only.
class CefDownloadItemCToCpp
    : public CefCToCpp<CefDownloadItemCToCpp, CefDownloadItem,
        cef_download_item_t> {
 public:
  explicit CefDownloadItemCToCpp(cef_download_item_t* str)
      : CefCToCpp<CefDownloadItemCToCpp, CefDownloadItem, cef_download_item_t>(
          str) {}

  // CefDownloadItem methods
  virtual bool IsValid() OVERRIDE;
  virtual bool IsInProgress() OVERRIDE;
  virtual bool IsComplete() OVERRIDE;
  virtual bool IsCanceled() OVERRIDE;
  virtual int64 GetCurrentSpeed() OVERRIDE;
  virtual int GetPercentComplete() OVERRIDE;
  virtual int64 GetTotalBytes() OVERRIDE;
  virtual int64 GetReceivedBytes() OVERRIDE;
  virtual CefTime GetStartTime() OVERRIDE;
  virtual CefTime GetEndTime() OVERRIDE;
  virtual CefString GetFullPath() OVERRIDE;
  virtual uint32 GetId() OVERRIDE;
  virtual CefString GetURL() OVERRIDE;
  virtual CefString GetSuggestedFileName() OVERRIDE;
  virtual CefString GetContentDisposition() OVERRIDE;
  virtual CefString GetMimeType() OVERRIDE;
};

#endif  // USING_CEF_SHARED
#endif  // CEF_LIBCEF_DLL_CTOCPP_DOWNLOAD_ITEM_CTOCPP_H_

