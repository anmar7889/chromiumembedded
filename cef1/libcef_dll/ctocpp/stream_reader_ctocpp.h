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

#ifndef CEF_LIBCEF_DLL_CTOCPP_STREAM_READER_CTOCPP_H_
#define CEF_LIBCEF_DLL_CTOCPP_STREAM_READER_CTOCPP_H_
#pragma once

#ifndef USING_CEF_SHARED
#pragma message("Warning: "__FILE__" may be accessed wrapper-side only")
#else  // USING_CEF_SHARED

#include "include/cef_stream.h"
#include "include/capi/cef_stream_capi.h"
#include "libcef_dll/ctocpp/ctocpp.h"

// Wrap a C structure with a C++ class.
// This class may be instantiated and accessed wrapper-side only.
class CefStreamReaderCToCpp
    : public CefCToCpp<CefStreamReaderCToCpp, CefStreamReader,
        cef_stream_reader_t> {
 public:
  explicit CefStreamReaderCToCpp(cef_stream_reader_t* str)
      : CefCToCpp<CefStreamReaderCToCpp, CefStreamReader, cef_stream_reader_t>(
          str) {}
  virtual ~CefStreamReaderCToCpp() {}

  // CefStreamReader methods
  virtual size_t Read(void* ptr, size_t size, size_t n) OVERRIDE;
  virtual int Seek(int64 offset, int whence) OVERRIDE;
  virtual int64 Tell() OVERRIDE;
  virtual int Eof() OVERRIDE;
};

#endif  // USING_CEF_SHARED
#endif  // CEF_LIBCEF_DLL_CTOCPP_STREAM_READER_CTOCPP_H_

