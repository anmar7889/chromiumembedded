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

#include "libcef_dll/cpptoc/browser_process_handler_cpptoc.h"
#include "libcef_dll/cpptoc/print_handler_cpptoc.h"
#include "libcef_dll/ctocpp/command_line_ctocpp.h"
#include "libcef_dll/ctocpp/list_value_ctocpp.h"


// MEMBER FUNCTIONS - Body may be edited by hand.

void CEF_CALLBACK browser_process_handler_on_context_initialized(
    struct _cef_browser_process_handler_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return;

  // Execute
  CefBrowserProcessHandlerCppToC::Get(self)->OnContextInitialized();
}

void CEF_CALLBACK browser_process_handler_on_before_child_process_launch(
    struct _cef_browser_process_handler_t* self,
    struct _cef_command_line_t* command_line) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return;
  // Verify param: command_line; type: refptr_diff
  DCHECK(command_line);
  if (!command_line)
    return;

  // Execute
  CefBrowserProcessHandlerCppToC::Get(self)->OnBeforeChildProcessLaunch(
      CefCommandLineCToCpp::Wrap(command_line));
}

void CEF_CALLBACK browser_process_handler_on_render_process_thread_created(
    struct _cef_browser_process_handler_t* self,
    struct _cef_list_value_t* extra_info) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return;
  // Verify param: extra_info; type: refptr_diff
  DCHECK(extra_info);
  if (!extra_info)
    return;

  // Execute
  CefBrowserProcessHandlerCppToC::Get(self)->OnRenderProcessThreadCreated(
      CefListValueCToCpp::Wrap(extra_info));
}

struct _cef_print_handler_t* CEF_CALLBACK browser_process_handler_get_print_handler(
    struct _cef_browser_process_handler_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return NULL;

  // Execute
  CefRefPtr<CefPrintHandler> _retval = CefBrowserProcessHandlerCppToC::Get(
      self)->GetPrintHandler();

  // Return type: refptr_same
  return CefPrintHandlerCppToC::Wrap(_retval);
}


// CONSTRUCTOR - Do not edit by hand.

CefBrowserProcessHandlerCppToC::CefBrowserProcessHandlerCppToC(
    CefBrowserProcessHandler* cls)
    : CefCppToC<CefBrowserProcessHandlerCppToC, CefBrowserProcessHandler,
        cef_browser_process_handler_t>(cls) {
  struct_.struct_.on_context_initialized =
      browser_process_handler_on_context_initialized;
  struct_.struct_.on_before_child_process_launch =
      browser_process_handler_on_before_child_process_launch;
  struct_.struct_.on_render_process_thread_created =
      browser_process_handler_on_render_process_thread_created;
  struct_.struct_.get_print_handler = browser_process_handler_get_print_handler;
}

#ifndef NDEBUG
template<> base::AtomicRefCount CefCppToC<CefBrowserProcessHandlerCppToC,
    CefBrowserProcessHandler, cef_browser_process_handler_t>::DebugObjCt = 0;
#endif

