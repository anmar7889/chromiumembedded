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

#include "include/cef_version.h"
#include "libcef_dll/cpptoc/app_cpptoc.h"
#include "libcef_dll/cpptoc/content_filter_cpptoc.h"
#include "libcef_dll/cpptoc/cookie_visitor_cpptoc.h"
#include "libcef_dll/cpptoc/domevent_listener_cpptoc.h"
#include "libcef_dll/cpptoc/domvisitor_cpptoc.h"
#include "libcef_dll/cpptoc/display_handler_cpptoc.h"
#include "libcef_dll/cpptoc/download_handler_cpptoc.h"
#include "libcef_dll/cpptoc/drag_handler_cpptoc.h"
#include "libcef_dll/cpptoc/find_handler_cpptoc.h"
#include "libcef_dll/cpptoc/focus_handler_cpptoc.h"
#include "libcef_dll/cpptoc/geolocation_handler_cpptoc.h"
#include "libcef_dll/cpptoc/jsdialog_handler_cpptoc.h"
#include "libcef_dll/cpptoc/keyboard_handler_cpptoc.h"
#include "libcef_dll/cpptoc/life_span_handler_cpptoc.h"
#include "libcef_dll/cpptoc/load_handler_cpptoc.h"
#include "libcef_dll/cpptoc/menu_handler_cpptoc.h"
#include "libcef_dll/cpptoc/permission_handler_cpptoc.h"
#include "libcef_dll/cpptoc/print_handler_cpptoc.h"
#include "libcef_dll/cpptoc/proxy_handler_cpptoc.h"
#include "libcef_dll/cpptoc/read_handler_cpptoc.h"
#include "libcef_dll/cpptoc/render_handler_cpptoc.h"
#include "libcef_dll/cpptoc/request_handler_cpptoc.h"
#include "libcef_dll/cpptoc/scheme_handler_cpptoc.h"
#include "libcef_dll/cpptoc/scheme_handler_factory_cpptoc.h"
#include "libcef_dll/cpptoc/storage_visitor_cpptoc.h"
#include "libcef_dll/cpptoc/task_cpptoc.h"
#include "libcef_dll/cpptoc/v8accessor_cpptoc.h"
#include "libcef_dll/cpptoc/v8context_handler_cpptoc.h"
#include "libcef_dll/cpptoc/v8handler_cpptoc.h"
#include "libcef_dll/cpptoc/web_urlrequest_client_cpptoc.h"
#include "libcef_dll/cpptoc/write_handler_cpptoc.h"
#include "libcef_dll/ctocpp/browser_ctocpp.h"
#include "libcef_dll/ctocpp/cookie_manager_ctocpp.h"
#include "libcef_dll/ctocpp/domdocument_ctocpp.h"
#include "libcef_dll/ctocpp/domevent_ctocpp.h"
#include "libcef_dll/ctocpp/domnode_ctocpp.h"
#include "libcef_dll/ctocpp/drag_data_ctocpp.h"
#include "libcef_dll/ctocpp/frame_ctocpp.h"
#include "libcef_dll/ctocpp/geolocation_callback_ctocpp.h"
#include "libcef_dll/ctocpp/post_data_ctocpp.h"
#include "libcef_dll/ctocpp/post_data_element_ctocpp.h"
#include "libcef_dll/ctocpp/request_ctocpp.h"
#include "libcef_dll/ctocpp/response_ctocpp.h"
#include "libcef_dll/ctocpp/scheme_handler_callback_ctocpp.h"
#include "libcef_dll/ctocpp/stream_reader_ctocpp.h"
#include "libcef_dll/ctocpp/stream_writer_ctocpp.h"
#include "libcef_dll/ctocpp/v8context_ctocpp.h"
#include "libcef_dll/ctocpp/v8exception_ctocpp.h"
#include "libcef_dll/ctocpp/v8stack_frame_ctocpp.h"
#include "libcef_dll/ctocpp/v8stack_trace_ctocpp.h"
#include "libcef_dll/ctocpp/v8value_ctocpp.h"
#include "libcef_dll/ctocpp/web_plugin_info_ctocpp.h"
#include "libcef_dll/ctocpp/web_urlrequest_ctocpp.h"
#include "libcef_dll/ctocpp/xml_reader_ctocpp.h"
#include "libcef_dll/ctocpp/zip_reader_ctocpp.h"

// Define used to facilitate parsing.
#define CEF_GLOBAL


// GLOBAL METHODS - Body may be edited by hand.

CEF_GLOBAL bool CefInitialize(const CefSettings& settings,
    CefRefPtr<CefApp> application)
{
  int build_revision = cef_build_revision();
  if (build_revision != CEF_REVISION) {
    // The libcef build revision does not match the CEF API revision.
    DCHECK(false);
    return false;
  }

  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Unverified params: application

  // Execute
  int _retval = cef_initialize(
      &settings,
      CefAppCppToC::Wrap(application));

  // Return type: bool
  return _retval?true:false;
}


CEF_GLOBAL void CefShutdown()
{
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  cef_shutdown();

#ifndef NDEBUG
  // Check that all wrapper objects have been destroyed
  DCHECK(CefBrowserCToCpp::DebugObjCt == 0);
  DCHECK(CefContentFilterCppToC::DebugObjCt == 0);
  DCHECK(CefCookieManagerCToCpp::DebugObjCt == 0);
  DCHECK(CefCookieVisitorCppToC::DebugObjCt == 0);
  DCHECK(CefDOMDocumentCToCpp::DebugObjCt == 0);
  DCHECK(CefDOMEventCToCpp::DebugObjCt == 0);
  DCHECK(CefDOMEventListenerCppToC::DebugObjCt == 0);
  DCHECK(CefDOMNodeCToCpp::DebugObjCt == 0);
  DCHECK(CefDOMVisitorCppToC::DebugObjCt == 0);
  DCHECK(CefDisplayHandlerCppToC::DebugObjCt == 0);
  DCHECK(CefDownloadHandlerCppToC::DebugObjCt == 0);
  DCHECK(CefDragDataCToCpp::DebugObjCt == 0);
  DCHECK(CefDragHandlerCppToC::DebugObjCt == 0);
  DCHECK(CefFindHandlerCppToC::DebugObjCt == 0);
  DCHECK(CefFocusHandlerCppToC::DebugObjCt == 0);
  DCHECK(CefFrameCToCpp::DebugObjCt == 0);
  DCHECK(CefGeolocationCallbackCToCpp::DebugObjCt == 0);
  DCHECK(CefGeolocationHandlerCppToC::DebugObjCt == 0);
  DCHECK(CefJSDialogHandlerCppToC::DebugObjCt == 0);
  DCHECK(CefKeyboardHandlerCppToC::DebugObjCt == 0);
  DCHECK(CefLifeSpanHandlerCppToC::DebugObjCt == 0);
  DCHECK(CefLoadHandlerCppToC::DebugObjCt == 0);
  DCHECK(CefMenuHandlerCppToC::DebugObjCt == 0);
  DCHECK(CefPermissionHandlerCppToC::DebugObjCt == 0);
  DCHECK(CefPostDataCToCpp::DebugObjCt == 0);
  DCHECK(CefPostDataElementCToCpp::DebugObjCt == 0);
  DCHECK(CefPrintHandlerCppToC::DebugObjCt == 0);
  DCHECK(CefProxyHandlerCppToC::DebugObjCt == 0);
  DCHECK(CefReadHandlerCppToC::DebugObjCt == 0);
  DCHECK(CefRenderHandlerCppToC::DebugObjCt == 0);
  DCHECK(CefRequestCToCpp::DebugObjCt == 0);
  DCHECK(CefRequestHandlerCppToC::DebugObjCt == 0);
  DCHECK(CefResponseCToCpp::DebugObjCt == 0);
  DCHECK(CefSchemeHandlerCallbackCToCpp::DebugObjCt == 0);
  DCHECK(CefSchemeHandlerCppToC::DebugObjCt == 0);
  DCHECK(CefSchemeHandlerFactoryCppToC::DebugObjCt == 0);
  DCHECK(CefStorageVisitorCppToC::DebugObjCt == 0);
  DCHECK(CefStreamReaderCToCpp::DebugObjCt == 0);
  DCHECK(CefStreamWriterCToCpp::DebugObjCt == 0);
  DCHECK(CefTaskCppToC::DebugObjCt == 0);
  DCHECK(CefV8AccessorCppToC::DebugObjCt == 0);
  DCHECK(CefV8ContextCToCpp::DebugObjCt == 0);
  DCHECK(CefV8ContextHandlerCppToC::DebugObjCt == 0);
  DCHECK(CefV8ExceptionCToCpp::DebugObjCt == 0);
  DCHECK(CefV8HandlerCppToC::DebugObjCt == 0);
  DCHECK(CefV8StackFrameCToCpp::DebugObjCt == 0);
  DCHECK(CefV8StackTraceCToCpp::DebugObjCt == 0);
  DCHECK(CefV8ValueCToCpp::DebugObjCt == 0);
  DCHECK(CefWebPluginInfoCToCpp::DebugObjCt == 0);
  DCHECK(CefWebURLRequestCToCpp::DebugObjCt == 0);
  DCHECK(CefWebURLRequestClientCppToC::DebugObjCt == 0);
  DCHECK(CefWriteHandlerCppToC::DebugObjCt == 0);
  DCHECK(CefXmlReaderCToCpp::DebugObjCt == 0);
  DCHECK(CefZipReaderCToCpp::DebugObjCt == 0);
#endif // !NDEBUG
}


CEF_GLOBAL void CefDoMessageLoopWork()
{
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  cef_do_message_loop_work();
}


CEF_GLOBAL void CefRunMessageLoop()
{
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  cef_run_message_loop();
}


CEF_GLOBAL void CefQuitMessageLoop()
{
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  cef_quit_message_loop();
}


CEF_GLOBAL bool CefRegisterExtension(const CefString& extension_name,
    const CefString& javascript_code, CefRefPtr<CefV8Handler> handler)
{
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: extension_name; type: string_byref_const
  DCHECK(!extension_name.empty());
  if (extension_name.empty())
    return false;
  // Verify param: javascript_code; type: string_byref_const
  DCHECK(!javascript_code.empty());
  if (javascript_code.empty())
    return false;
  // Unverified params: handler

  // Execute
  int _retval = cef_register_extension(
      extension_name.GetStruct(),
      javascript_code.GetStruct(),
      CefV8HandlerCppToC::Wrap(handler));

  // Return type: bool
  return _retval?true:false;
}


CEF_GLOBAL bool CefRegisterCustomScheme(const CefString& scheme_name,
    bool is_standard, bool is_local, bool is_display_isolated)
{
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: scheme_name; type: string_byref_const
  DCHECK(!scheme_name.empty());
  if (scheme_name.empty())
    return false;

  // Execute
  int _retval = cef_register_custom_scheme(
      scheme_name.GetStruct(),
      is_standard,
      is_local,
      is_display_isolated);

  // Return type: bool
  return _retval?true:false;
}


CEF_GLOBAL bool CefRegisterSchemeHandlerFactory(const CefString& scheme_name,
    const CefString& domain_name, CefRefPtr<CefSchemeHandlerFactory> factory)
{
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: scheme_name; type: string_byref_const
  DCHECK(!scheme_name.empty());
  if (scheme_name.empty())
    return false;
  // Unverified params: domain_name, factory

  // Execute
  int _retval = cef_register_scheme_handler_factory(
      scheme_name.GetStruct(),
      domain_name.GetStruct(),
      CefSchemeHandlerFactoryCppToC::Wrap(factory));

  // Return type: bool
  return _retval?true:false;
}


CEF_GLOBAL bool CefClearSchemeHandlerFactories()
{
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = cef_clear_scheme_handler_factories();

  // Return type: bool
  return _retval?true:false;
}


CEF_GLOBAL bool CefAddCrossOriginWhitelistEntry(const CefString& source_origin,
    const CefString& target_protocol, const CefString& target_domain,
    bool allow_target_subdomains)
{
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: source_origin; type: string_byref_const
  DCHECK(!source_origin.empty());
  if (source_origin.empty())
    return false;
  // Verify param: target_protocol; type: string_byref_const
  DCHECK(!target_protocol.empty());
  if (target_protocol.empty())
    return false;
  // Verify param: target_domain; type: string_byref_const
  DCHECK(!target_domain.empty());
  if (target_domain.empty())
    return false;

  // Execute
  int _retval = cef_add_cross_origin_whitelist_entry(
      source_origin.GetStruct(),
      target_protocol.GetStruct(),
      target_domain.GetStruct(),
      allow_target_subdomains);

  // Return type: bool
  return _retval?true:false;
}


CEF_GLOBAL bool CefRemoveCrossOriginWhitelistEntry(
    const CefString& source_origin, const CefString& target_protocol,
    const CefString& target_domain, bool allow_target_subdomains)
{
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: source_origin; type: string_byref_const
  DCHECK(!source_origin.empty());
  if (source_origin.empty())
    return false;
  // Verify param: target_protocol; type: string_byref_const
  DCHECK(!target_protocol.empty());
  if (target_protocol.empty())
    return false;
  // Verify param: target_domain; type: string_byref_const
  DCHECK(!target_domain.empty());
  if (target_domain.empty())
    return false;

  // Execute
  int _retval = cef_remove_cross_origin_whitelist_entry(
      source_origin.GetStruct(),
      target_protocol.GetStruct(),
      target_domain.GetStruct(),
      allow_target_subdomains);

  // Return type: bool
  return _retval?true:false;
}


CEF_GLOBAL bool CefClearCrossOriginWhitelist()
{
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = cef_clear_cross_origin_whitelist();

  // Return type: bool
  return _retval?true:false;
}


CEF_GLOBAL bool CefCurrentlyOn(CefThreadId threadId)
{
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = cef_currently_on(
      threadId);

  // Return type: bool
  return _retval?true:false;
}


CEF_GLOBAL bool CefPostTask(CefThreadId threadId, CefRefPtr<CefTask> task)
{
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: task; type: refptr_diff
  DCHECK(task.get());
  if (!task.get())
    return false;

  // Execute
  int _retval = cef_post_task(
      threadId,
      CefTaskCppToC::Wrap(task));

  // Return type: bool
  return _retval?true:false;
}


CEF_GLOBAL bool CefPostDelayedTask(CefThreadId threadId,
    CefRefPtr<CefTask> task, long delay_ms)
{
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: task; type: refptr_diff
  DCHECK(task.get());
  if (!task.get())
    return false;

  // Execute
  int _retval = cef_post_delayed_task(
      threadId,
      CefTaskCppToC::Wrap(task),
      delay_ms);

  // Return type: bool
  return _retval?true:false;
}


CEF_GLOBAL bool CefParseURL(const CefString& url, CefURLParts& parts)
{
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: url; type: string_byref_const
  DCHECK(!url.empty());
  if (url.empty())
    return false;

  // Execute
  int _retval = cef_parse_url(
      url.GetStruct(),
      &parts);

  // Return type: bool
  return _retval?true:false;
}


CEF_GLOBAL bool CefCreateURL(const CefURLParts& parts, CefString& url)
{
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  int _retval = cef_create_url(
      &parts,
      url.GetWritableStruct());

  // Return type: bool
  return _retval?true:false;
}


CEF_GLOBAL bool CefVisitStorage(CefStorageType type, const CefString& origin,
    const CefString& key, CefRefPtr<CefStorageVisitor> visitor)
{
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: visitor; type: refptr_diff
  DCHECK(visitor.get());
  if (!visitor.get())
    return false;
  // Unverified params: origin, key

  // Execute
  int _retval = cef_visit_storage(
      type,
      origin.GetStruct(),
      key.GetStruct(),
      CefStorageVisitorCppToC::Wrap(visitor));

  // Return type: bool
  return _retval?true:false;
}


CEF_GLOBAL bool CefSetStorage(CefStorageType type, const CefString& origin,
    const CefString& key, const CefString& value)
{
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: origin; type: string_byref_const
  DCHECK(!origin.empty());
  if (origin.empty())
    return false;
  // Verify param: key; type: string_byref_const
  DCHECK(!key.empty());
  if (key.empty())
    return false;
  // Verify param: value; type: string_byref_const
  DCHECK(!value.empty());
  if (value.empty())
    return false;

  // Execute
  int _retval = cef_set_storage(
      type,
      origin.GetStruct(),
      key.GetStruct(),
      value.GetStruct());

  // Return type: bool
  return _retval?true:false;
}


CEF_GLOBAL bool CefDeleteStorage(CefStorageType type, const CefString& origin,
    const CefString& key)
{
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Unverified params: origin, key

  // Execute
  int _retval = cef_delete_storage(
      type,
      origin.GetStruct(),
      key.GetStruct());

  // Return type: bool
  return _retval?true:false;
}


CEF_GLOBAL bool CefSetStoragePath(CefStorageType type, const CefString& path)
{
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Unverified params: path

  // Execute
  int _retval = cef_set_storage_path(
      type,
      path.GetStruct());

  // Return type: bool
  return _retval?true:false;
}


CEF_GLOBAL size_t CefGetWebPluginCount()
{
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  size_t _retval = cef_get_web_plugin_count();

  // Return type: simple
  return _retval;
}


CEF_GLOBAL CefRefPtr<CefWebPluginInfo> CefGetWebPluginInfo(int index)
{
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Execute
  cef_web_plugin_info_t* _retval = cef_get_web_plugin_info(
      index);

  // Return type: refptr_same
  return CefWebPluginInfoCToCpp::Wrap(_retval);
}


CEF_GLOBAL CefRefPtr<CefWebPluginInfo> CefGetWebPluginInfo(
    const CefString& name)
{
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: name; type: string_byref_const
  DCHECK(!name.empty());
  if (name.empty())
    return NULL;

  // Execute
  cef_web_plugin_info_t* _retval = cef_get_web_plugin_info_byname(
      name.GetStruct());

  // Return type: refptr_same
  return CefWebPluginInfoCToCpp::Wrap(_retval);
}


