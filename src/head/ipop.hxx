#pragma once

/* headers */

#include "conf.hxx"
#include "osys.hxx"
#include "tool.hxx"
#include "stdl.hxx"
#include "defn.hxx"
#include "type.hxx"
#include "meta.hxx"
#include "nums.hxx"
#include "memo.hxx"
#include "text.hxx"

/** standard **/

#include <cstdio>

#include <iostream>
#include <fstream>

#ifndef _TOOL
#error "_TOOL is undefined"
#elif(defined(_TOOL_CLANG) || defined(_TOOL_MSVCC))
#include <filesystem>
#elif(defined(_TOOL_GNUCC))
#include <experimental/bits/fs_fwd.h>
#include <experimental/bits/fs_path.h>
#include <experimental/bits/fs_dir.h>
#include <experimental/bits/fs_ops.h>
#endif/*ifd(_TOOL_GNUCC)*/

/* defines */

#ifndef _OPUT
#define _OPUT( args... ) fprintf( stdout, ##args );
#endif/*_OPUT*/
#ifndef _OLOG
#define _OLOG( mesg, args... ) { \
    _OPUT( \
        "[from]%s" \
        "[file]%s" \
        "[func]%s" \
        "[line]%d" \
        "[mesg]%c%d%c", \
        \
        "olog", \
        _FILE_NAME, \
        _FUNC_NAME, \
        _FILE_LINE, \
        text::endl, mesg, ##args, text::endl ) \
}
#endif/*_OLOG*/

#ifndef _EPUT
#define _EPUT( args... ) fprintf( stderr, ##args );
#endif/*_EPUT*/
#ifndef _ELOG
#define _ELOG( mesg, args... ) { \
    _EPUT( \
        "[from]%s" \
        "[file]%s" \
        "[func]%s" \
        "[line]%d" \
        "[mesg]%c%d%c", \
        \
        "elog", \
        _FILE_NAME, \
        _FUNC_NAME, \
        _FILE_LINE, \
        text::endl, mesg, ##args, text::endl ) \
}
#endif/*_ELOG*/

/* content */

namespace libasist { /* typedef */

    /* input-only-memory-data-stream */
    using mdata_writer_t = std::istream;
    using mdata_writer_iter_t = std::istream_iterator<scstr_t>;
    /* output-only-memory-data-stream */
    using mdata_reader_t = std::ostream;
    using mdata_reader_iter_t = std::ostream_iterator<scstr_t>;
    /* input-output-memory-data-stream */
    using mdata_editor_t = std::iostream;


    /* input-only-file-data-stream */
    using fdata_writer_t = std::istream;
    /* output-only-file-data-stream */
    using fdata_reader_t = std::ostream;
    /* input-output-file-data-stream */
    using fdata_editor_t = std::iostream;

} /* typedef */
