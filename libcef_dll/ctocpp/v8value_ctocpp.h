// Copyright (c) 2009 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#ifndef _V8VALUE_CTOCPP_H
#define _V8VALUE_CTOCPP_H

#ifndef USING_CEF_SHARED
#pragma message("Warning: "__FILE__" may be accessed wrapper-side only")
#else // USING_CEF_SHARED

#include "cef.h"
#include "cef_capi.h"
#include "ctocpp.h"


// Wrap a C v8value structure with a C++ v8value class.
// This class may be instantiated and accessed DLL-side only.
class CefV8ValueCToCpp
    : public CefCToCpp<CefV8ValueCToCpp, CefV8Value, cef_v8value_t>
{
public:
  CefV8ValueCToCpp(cef_v8value_t* str)
    : CefCToCpp<CefV8ValueCToCpp, CefV8Value, cef_v8value_t>(str) {}
  virtual ~CefV8ValueCToCpp() {}

  // CefV8Value methods
  virtual bool IsUndefined();
  virtual bool IsNull();
  virtual bool IsBool();
  virtual bool IsInt();
  virtual bool IsDouble();
  virtual bool IsString();
  virtual bool IsObject();
  virtual bool IsArray();
  virtual bool IsFunction();
  virtual bool GetBoolValue();
  virtual int GetIntValue();
  virtual double GetDoubleValue();
  virtual std::wstring GetStringValue();
  virtual bool HasValue(const std::wstring& key);
  virtual bool HasValue(int index);
  virtual bool DeleteValue(const std::wstring& key);
  virtual bool DeleteValue(int index);
  virtual CefRefPtr<CefV8Value> GetValue(const std::wstring& key);
  virtual CefRefPtr<CefV8Value> GetValue(int index);
  virtual bool SetValue(const std::wstring& key, CefRefPtr<CefV8Value> value);
  virtual bool SetValue(int index, CefRefPtr<CefV8Value> value);
  virtual bool GetKeys(std::vector<std::wstring>& keys);
  virtual CefRefPtr<CefBase> GetUserData();
  virtual int GetArrayLength();
  virtual std::wstring GetFunctionName();
  virtual CefRefPtr<CefV8Handler> GetFunctionHandler();
  virtual bool ExecuteFunction(CefRefPtr<CefV8Value> object,
                               CefV8ValueList& arguments,
                               CefRefPtr<CefV8Value>& retval,
                               std::wstring& exception);
};


#endif // USING_CEF_SHARED
#endif // _V8VALUE_CTOCPP_H
