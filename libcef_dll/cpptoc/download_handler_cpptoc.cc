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

#include "libcef_dll/cpptoc/download_handler_cpptoc.h"


// MEMBER FUNCTIONS - Body may be edited by hand.

int CEF_CALLBACK download_handler_received_data(
    struct _cef_download_handler_t* self, void* data, int data_size)
{
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return 0;
  // Verify param: data; type: simple_byaddr
  DCHECK(data);
  if (!data)
    return 0;

  // Execute
  bool _retval = CefDownloadHandlerCppToC::Get(self)->ReceivedData(
      data,
      data_size);

  // Return type: bool
  return _retval;
}


void CEF_CALLBACK download_handler_complete(
    struct _cef_download_handler_t* self)
{
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return;

  // Execute
  CefDownloadHandlerCppToC::Get(self)->Complete();
}



// CONSTRUCTOR - Do not edit by hand.

CefDownloadHandlerCppToC::CefDownloadHandlerCppToC(CefDownloadHandler* cls)
    : CefCppToC<CefDownloadHandlerCppToC, CefDownloadHandler,
        cef_download_handler_t>(cls)
{
  struct_.struct_.received_data = download_handler_received_data;
  struct_.struct_.complete = download_handler_complete;
}

#ifndef NDEBUG
template<> long CefCppToC<CefDownloadHandlerCppToC, CefDownloadHandler,
    cef_download_handler_t>::DebugObjCt = 0;
#endif

