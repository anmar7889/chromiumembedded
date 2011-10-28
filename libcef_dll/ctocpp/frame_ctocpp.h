// Copyright (c) 2011 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.
//
// -------------------------------------------------------------------------
//
// This file was generated by the CEF translator tool and should not edited
// by hand. See the translator.README.txt file in the tools directory for
// more information.
//

#ifndef _FRAME_CTOCPP_H
#define _FRAME_CTOCPP_H

#ifndef USING_CEF_SHARED
#pragma message("Warning: "__FILE__" may be accessed wrapper-side only")
#else // USING_CEF_SHARED

#include "include/cef.h"
#include "include/cef_capi.h"
#include "libcef_dll/ctocpp/ctocpp.h"

// Wrap a C structure with a C++ class.
// This class may be instantiated and accessed wrapper-side only.
class CefFrameCToCpp
    : public CefCToCpp<CefFrameCToCpp, CefFrame, cef_frame_t>
{
public:
  CefFrameCToCpp(cef_frame_t* str)
      : CefCToCpp<CefFrameCToCpp, CefFrame, cef_frame_t>(str) {}
  virtual ~CefFrameCToCpp() {}

  // CefFrame methods
  virtual void Undo() OVERRIDE;
  virtual void Redo() OVERRIDE;
  virtual void Cut() OVERRIDE;
  virtual void Copy() OVERRIDE;
  virtual void Paste() OVERRIDE;
  virtual void Delete() OVERRIDE;
  virtual void SelectAll() OVERRIDE;
  virtual void Print() OVERRIDE;
  virtual void ViewSource() OVERRIDE;
  virtual CefString GetSource() OVERRIDE;
  virtual CefString GetText() OVERRIDE;
  virtual void LoadRequest(CefRefPtr<CefRequest> request) OVERRIDE;
  virtual void LoadURL(const CefString& url) OVERRIDE;
  virtual void LoadString(const CefString& string,
      const CefString& url) OVERRIDE;
  virtual void LoadStream(CefRefPtr<CefStreamReader> stream,
      const CefString& url) OVERRIDE;
  virtual void ExecuteJavaScript(const CefString& jsCode,
      const CefString& scriptUrl, int startLine) OVERRIDE;
  virtual bool IsMain() OVERRIDE;
  virtual bool IsFocused() OVERRIDE;
  virtual CefString GetName() OVERRIDE;
  virtual CefString GetURL() OVERRIDE;
  virtual CefRefPtr<CefBrowser> GetBrowser() OVERRIDE;
  virtual void VisitDOM(CefRefPtr<CefDOMVisitor> visitor) OVERRIDE;
  virtual CefRefPtr<CefV8Context> GetV8Context() OVERRIDE;
};

#endif // USING_CEF_SHARED
#endif // _FRAME_CTOCPP_H

