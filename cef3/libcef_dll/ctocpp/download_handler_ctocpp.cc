// Copyright (c) 2014 The Chromium Embedded Framework Authors. All rights
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

#include "libcef_dll/cpptoc/before_download_callback_cpptoc.h"
#include "libcef_dll/cpptoc/browser_cpptoc.h"
#include "libcef_dll/cpptoc/download_item_cpptoc.h"
#include "libcef_dll/cpptoc/download_item_callback_cpptoc.h"
#include "libcef_dll/ctocpp/download_handler_ctocpp.h"


// VIRTUAL METHODS - Body may be edited by hand.

void CefDownloadHandlerCToCpp::OnBeforeDownload(CefRefPtr<CefBrowser> browser,
    CefRefPtr<CefDownloadItem> download_item, const CefString& suggested_name,
    CefRefPtr<CefBeforeDownloadCallback> callback) {
  if (CEF_MEMBER_MISSING(struct_, on_before_download))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: browser; type: refptr_diff
  DCHECK(browser.get());
  if (!browser.get())
    return;
  // Verify param: download_item; type: refptr_diff
  DCHECK(download_item.get());
  if (!download_item.get())
    return;
  // Verify param: suggested_name; type: string_byref_const
  DCHECK(!suggested_name.empty());
  if (suggested_name.empty())
    return;
  // Verify param: callback; type: refptr_diff
  DCHECK(callback.get());
  if (!callback.get())
    return;

  // Execute
  struct_->on_before_download(struct_,
      CefBrowserCppToC::Wrap(browser),
      CefDownloadItemCppToC::Wrap(download_item),
      suggested_name.GetStruct(),
      CefBeforeDownloadCallbackCppToC::Wrap(callback));
}

void CefDownloadHandlerCToCpp::OnDownloadUpdated(CefRefPtr<CefBrowser> browser,
    CefRefPtr<CefDownloadItem> download_item,
    CefRefPtr<CefDownloadItemCallback> callback) {
  if (CEF_MEMBER_MISSING(struct_, on_download_updated))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: browser; type: refptr_diff
  DCHECK(browser.get());
  if (!browser.get())
    return;
  // Verify param: download_item; type: refptr_diff
  DCHECK(download_item.get());
  if (!download_item.get())
    return;
  // Verify param: callback; type: refptr_diff
  DCHECK(callback.get());
  if (!callback.get())
    return;

  // Execute
  struct_->on_download_updated(struct_,
      CefBrowserCppToC::Wrap(browser),
      CefDownloadItemCppToC::Wrap(download_item),
      CefDownloadItemCallbackCppToC::Wrap(callback));
}


#ifndef NDEBUG
template<> long CefCToCpp<CefDownloadHandlerCToCpp, CefDownloadHandler,
    cef_download_handler_t>::DebugObjCt = 0;
#endif

