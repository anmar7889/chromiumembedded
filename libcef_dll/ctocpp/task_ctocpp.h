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

#ifndef _TASK_CTOCPP_H
#define _TASK_CTOCPP_H

#ifndef BUILDING_CEF_SHARED
#pragma message("Warning: "__FILE__" may be accessed DLL-side only")
#else // BUILDING_CEF_SHARED

#include "include/cef.h"
#include "include/cef_capi.h"
#include "libcef_dll/ctocpp/ctocpp.h"

// Wrap a C structure with a C++ class.
// This class may be instantiated and accessed DLL-side only.
class CefTaskCToCpp
    : public CefCToCpp<CefTaskCToCpp, CefTask, cef_task_t>
{
public:
  CefTaskCToCpp(cef_task_t* str)
      : CefCToCpp<CefTaskCToCpp, CefTask, cef_task_t>(str) {}
  virtual ~CefTaskCToCpp() {}

  // CefTask methods
  virtual void Execute(CefThreadId threadId) OVERRIDE;
};

#endif // BUILDING_CEF_SHARED
#endif // _TASK_CTOCPP_H

