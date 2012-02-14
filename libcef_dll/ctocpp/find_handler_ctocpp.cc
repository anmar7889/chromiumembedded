// Copyright (c) 2012 The Chromium Embedded Framework Authors. All rights
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

#include "libcef_dll/cpptoc/browser_cpptoc.h"
#include "libcef_dll/ctocpp/find_handler_ctocpp.h"


// VIRTUAL METHODS - Body may be edited by hand.

void CefFindHandlerCToCpp::OnFindResult(CefRefPtr<CefBrowser> browser,
    int identifier, int count, const CefRect& selectionRect,
    int activeMatchOrdinal, bool finalUpdate)
{
  if (CEF_MEMBER_MISSING(struct_, on_find_result))
    return;

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: browser; type: refptr_diff
  DCHECK(browser.get());
  if (!browser.get())
    return;

  // Execute
  struct_->on_find_result(struct_,
      CefBrowserCppToC::Wrap(browser),
      identifier,
      count,
      &selectionRect,
      activeMatchOrdinal,
      finalUpdate);
}



#ifndef NDEBUG
template<> long CefCToCpp<CefFindHandlerCToCpp, CefFindHandler,
    cef_find_handler_t>::DebugObjCt = 0;
#endif

