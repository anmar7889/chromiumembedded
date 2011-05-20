// Copyright (c) 2011 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.
//
// ---------------------------------------------------------------------------
//
// A portion of this file was generated by the CEF translator tool.  When
// making changes by hand only do so within the body of existing function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//

#include "libcef_dll/cpptoc/client_cpptoc.h"
#include "libcef_dll/cpptoc/life_span_handler_cpptoc.h"
#include "libcef_dll/ctocpp/browser_ctocpp.h"


// MEMBER FUNCTIONS - Body may be edited by hand.

int CEF_CALLBACK life_span_handler_on_before_popup(
    struct _cef_life_span_handler_t* self, cef_browser_t* parentBrowser,
    const struct _cef_popup_features_t* popupFeatures,
    cef_window_info_t* windowInfo, const cef_string_t* url,
    struct _cef_client_t** client, struct _cef_browser_settings_t* settings)
{
  DCHECK(self);
  DCHECK(parentBrowser);
  DCHECK(popupFeatures);
  DCHECK(windowInfo);
  DCHECK(url);
  DCHECK(client);
  DCHECK(settings);
  if (!self || !parentBrowser || !popupFeatures || !windowInfo || !url ||
      !client || !settings)
    return 0;

  CefWindowInfo wndInfo;
  CefBrowserSettings browserSettings;
  CefPopupFeatures features;
  
  // Take ownership of the values.
  wndInfo.AttachTo(*windowInfo);
  browserSettings.AttachTo(*settings);
  
  // Reference the existing values instead of copying.
  features.Set(*popupFeatures, false);
  
  // |newHandler| will start off pointing to the current handler.
  CefRefPtr<CefClient> clientPtr;
  if (*client)
    clientPtr = CefClientCppToC::Unwrap(*client);
  CefClient* origClient = clientPtr.get();
  
  // |parentBrowser| will be NULL if this is a top-level browser window.
  CefRefPtr<CefBrowser> browserPtr(CefBrowserCToCpp::Wrap(parentBrowser));
  
  bool rv = CefLifeSpanHandlerCppToC::Get(self)->OnBeforePopup(
      browserPtr, features, wndInfo, CefString(url), clientPtr,
      browserSettings);

  if (clientPtr.get()) {
    if (clientPtr.get() != origClient) {
      // The handler has been changed.
      *client = CefClientCppToC::Wrap(clientPtr);
    }
  } else {
    *client = NULL;
  }

  // Return the values to the structures.
  wndInfo.DetachTo(*windowInfo);
  browserSettings.DetachTo(*settings);

  return rv;
}

void CEF_CALLBACK life_span_handler_on_after_created(
    struct _cef_life_span_handler_t* self, cef_browser_t* browser)
{
  DCHECK(self);
  DCHECK(browser);
  if (!self || !browser)
    return;

  CefLifeSpanHandlerCppToC::Get(self)->OnAfterCreated(
      CefBrowserCToCpp::Wrap(browser));
}

void CEF_CALLBACK life_span_handler_on_before_close(
    struct _cef_life_span_handler_t* self, cef_browser_t* browser)
{
  DCHECK(self);
  DCHECK(browser);
  if (!self || !browser)
    return;

  CefLifeSpanHandlerCppToC::Get(self)->OnBeforeClose(
      CefBrowserCToCpp::Wrap(browser));
}


// CONSTRUCTOR - Do not edit by hand.

CefLifeSpanHandlerCppToC::CefLifeSpanHandlerCppToC(CefLifeSpanHandler* cls)
    : CefCppToC<CefLifeSpanHandlerCppToC, CefLifeSpanHandler,
        cef_life_span_handler_t>(cls)
{
  struct_.struct_.on_before_popup = life_span_handler_on_before_popup;
  struct_.struct_.on_after_created = life_span_handler_on_after_created;
  struct_.struct_.on_before_close = life_span_handler_on_before_close;
}

#ifndef NDEBUG
template<> long CefCppToC<CefLifeSpanHandlerCppToC, CefLifeSpanHandler,
    cef_life_span_handler_t>::DebugObjCt = 0;
#endif

