// Copyright (c) 2010 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.
//
// -------------------------------------------------------------------------
//
// This file was generated by the CEF translator tool and should not edited
// by hand. See the translator.README.txt file in the tools directory for
// more information.
//

#ifndef _V8CONTEXT_CTOCPP_H
#define _V8CONTEXT_CTOCPP_H

#ifndef USING_CEF_SHARED
#pragma message("Warning: "__FILE__" may be accessed wrapper-side only")
#else // USING_CEF_SHARED

#include "include/cef.h"
#include "include/cef_capi.h"
#include "libcef_dll/ctocpp/ctocpp.h"

// Wrap a C structure with a C++ class.
// This class may be instantiated and accessed wrapper-side only.
class CefV8ContextCToCpp
    : public CefCToCpp<CefV8ContextCToCpp, CefV8Context, cef_v8context_t>
{
public:
  CefV8ContextCToCpp(cef_v8context_t* str)
      : CefCToCpp<CefV8ContextCToCpp, CefV8Context, cef_v8context_t>(str) {}
  virtual ~CefV8ContextCToCpp() {}

  // CefV8Context methods
  virtual CefRefPtr<CefBrowser> GetBrowser();
  virtual CefRefPtr<CefFrame> GetFrame();
  virtual CefRefPtr<CefV8Value> GetGlobal();
};

#endif // USING_CEF_SHARED
#endif // _V8CONTEXT_CTOCPP_H

