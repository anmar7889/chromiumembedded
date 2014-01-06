# Copyright (c) 2011 The Chromium Embedded Framework Authors. All rights
# reserved. Use of this source code is governed by a BSD-style license that
# can be found in the LICENSE file.

from cef_parser import *
from date_util import *

def make_capi_global_funcs(funcs, defined_names, translate_map, indent):
    result = ''
    first = True
    for func in funcs:
        comment = func.get_comment()
        if first or len(comment) > 0:
            result += '\n'+format_comment(comment, indent, translate_map);
        if func.get_retval().get_type().is_result_string():
            result += indent+'// The resulting string must be freed by calling cef_string_userfree_free().\n'
        result += wrap_code(indent+'CEF_EXPORT '+
                            func.get_capi_proto(defined_names)+';')
        if first:
            first = False
    return result

def make_capi_member_funcs(funcs, defined_names, translate_map, indent):
    result = ''
    first = True
    for func in funcs:
        comment = func.get_comment()
        if first or len(comment) > 0:
            result += '\n'+format_comment(comment, indent, translate_map)
        if func.get_retval().get_type().is_result_string():
            result += indent+'// The resulting string must be freed by calling cef_string_userfree_free().\n'
        parts = func.get_capi_parts()
        result += wrap_code(indent+parts['retval']+' (CEF_CALLBACK *'+
                            parts['name']+')('+
                            string.join(parts['args'], ', ')+');')
        if first:
            first = False
    return result

def make_capi_header(header, filename):
    # structure names that have already been defined
    defined_names = header.get_defined_structs()
    
    # map of strings that will be changed in C++ comments
    translate_map = header.get_capi_translations()
    
    # header string
    result = \
"""// Copyright (c) $YEAR$ Marshall A. Greenblatt. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//    * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//    * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//    * Neither the name of Google Inc. nor the name Chromium Embedded
// Framework nor the names of its contributors may be used to endorse
// or promote products derived from this software without specific prior
// written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the CEF translator tool and should not edited
// by hand. See the translator.README.txt file in the tools directory for
// more information.
//

#ifndef $GUARD$
#define $GUARD$
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

"""
    classes = header.get_classes(filename)

    # identify all includes and forward declarations
    all_includes = set([])
    all_declares = set([])
    for cls in classes:
        includes = cls.get_includes()
        for include in includes:
            all_includes.add(include)
        declares = cls.get_forward_declares()
        for declare in declares:
            all_declares.add(header.get_class(declare).get_capi_name())

    # output includes
    if len(all_includes) > 0:
        sorted_includes = sorted(all_includes)
        for include in sorted_includes:
            result += '#include "include/capi/' + include + '_capi.h"\n'
    else:
        result += '#include "include/capi/cef_base_capi.h"\n'

    result += '\n'

    # output forward declarations
    if len(all_declares) > 0:
        sorted_declares = sorted(all_declares)
        for declare in sorted_declares:
            result += 'struct _' + declare + ';\n'

    # output classes
    for cls in classes:
        # virtual functions are inside the structure
        classname = cls.get_capi_name()
        result += '\n'+format_comment(cls.get_comment(), '', translate_map);
        result += 'typedef struct _'+classname+ \
                  ' {\n  ///\n  // Base structure.\n  ///\n  cef_base_t base;\n'
        funcs = cls.get_virtual_funcs()
        result += make_capi_member_funcs(funcs, defined_names,
                                         translate_map, '  ')
        result += '} '+classname+';\n\n'
        
        defined_names.append(cls.get_capi_name())
        
        # static functions become global
        funcs = cls.get_static_funcs()
        if len(funcs) > 0:
            result += make_capi_global_funcs(funcs, defined_names,
                                             translate_map, '')+'\n'

    # output global functions
    funcs = header.get_funcs(filename)
    if len(funcs) > 0:
        result += make_capi_global_funcs(funcs, defined_names, translate_map, '')

    # footer string
    result += \
"""
#ifdef __cplusplus
}
#endif

#endif  // $GUARD$
"""
    
    # add the copyright year
    result = result.replace('$YEAR$', get_year())
    # add the guard string
    guard = 'CEF_INCLUDE_CAPI_'+string.upper(filename.replace('.', '_capi_'))+'_'
    result = result.replace('$GUARD$', guard)
    
    return result


def write_capi_header(header, filepath, backup):
    capi_path = get_capi_file_name(filepath)
    if path_exists(capi_path):
        oldcontents = read_file(capi_path)
    else:
        oldcontents = ''

    filename = os.path.split(filepath)[1]
    newcontents = make_capi_header(header, filename)
    if newcontents != oldcontents:
        if backup and oldcontents != '':
            backup_file(capi_path)
        write_file(capi_path, newcontents)
        return True
    
    return False


# test the module
if __name__ == "__main__":
    import sys
    
    # verify that the correct number of command-line arguments are provided
    if len(sys.argv) < 2:
        sys.stderr.write('Usage: '+sys.argv[0]+' <infile>')
        sys.exit()
        
    # create the header object
    header = obj_header()
    header.add_file(sys.argv[1])
    
    # dump the result to stdout
    filename = os.path.split(sys.argv[1])[1]
    sys.stdout.write(make_capi_header(header, filename))
