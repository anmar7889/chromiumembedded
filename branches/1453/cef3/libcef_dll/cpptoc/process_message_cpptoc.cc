// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
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

#include "libcef_dll/cpptoc/list_value_cpptoc.h"
#include "libcef_dll/cpptoc/process_message_cpptoc.h"


// GLOBAL FUNCTIONS - Body may be edited by hand.

CEF_EXPORT cef_process_message_t* cef_process_message_create(
    const cef_string_t* name) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: name; type: string_byref_const
  DCHECK(name);
  if (!name)
    return NULL;

  // Execute
  CefRefPtr<CefProcessMessage> _retval = CefProcessMessage::Create(
      CefString(name));

  // Return type: refptr_same
  return CefProcessMessageCppToC::Wrap(_retval);
}


// MEMBER FUNCTIONS - Body may be edited by hand.

int CEF_CALLBACK process_message_is_valid(struct _cef_process_message_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return 0;

  // Execute
  bool _retval = CefProcessMessageCppToC::Get(self)->IsValid();

  // Return type: bool
  return _retval;
}

int CEF_CALLBACK process_message_is_read_only(
    struct _cef_process_message_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return 0;

  // Execute
  bool _retval = CefProcessMessageCppToC::Get(self)->IsReadOnly();

  // Return type: bool
  return _retval;
}

struct _cef_process_message_t* CEF_CALLBACK process_message_copy(
    struct _cef_process_message_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return NULL;

  // Execute
  CefRefPtr<CefProcessMessage> _retval = CefProcessMessageCppToC::Get(
      self)->Copy();

  // Return type: refptr_same
  return CefProcessMessageCppToC::Wrap(_retval);
}

cef_string_userfree_t CEF_CALLBACK process_message_get_name(
    struct _cef_process_message_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return NULL;

  // Execute
  CefString _retval = CefProcessMessageCppToC::Get(self)->GetName();

  // Return type: string
  return _retval.DetachToUserFree();
}

struct _cef_list_value_t* CEF_CALLBACK process_message_get_argument_list(
    struct _cef_process_message_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return NULL;

  // Execute
  CefRefPtr<CefListValue> _retval = CefProcessMessageCppToC::Get(
      self)->GetArgumentList();

  // Return type: refptr_same
  return CefListValueCppToC::Wrap(_retval);
}


// CONSTRUCTOR - Do not edit by hand.

CefProcessMessageCppToC::CefProcessMessageCppToC(CefProcessMessage* cls)
    : CefCppToC<CefProcessMessageCppToC, CefProcessMessage,
        cef_process_message_t>(cls) {
  struct_.struct_.is_valid = process_message_is_valid;
  struct_.struct_.is_read_only = process_message_is_read_only;
  struct_.struct_.copy = process_message_copy;
  struct_.struct_.get_name = process_message_get_name;
  struct_.struct_.get_argument_list = process_message_get_argument_list;
}

#ifndef NDEBUG
template<> long CefCppToC<CefProcessMessageCppToC, CefProcessMessage,
    cef_process_message_t>::DebugObjCt = 0;
#endif

