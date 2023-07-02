#ifndef LIBASIST_HEAD_IPOP_HXX
#define LIBASIST_HEAD_IPOP_HXX 1

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
namespace libasist { /* imports */
namespace fstd = std::filesystem;
} /* imports */
#elif(defined(_TOOL_GNUCC))
#include <experimental/bits/fs_fwd.h>
#include <experimental/bits/fs_path.h>
#include <experimental/bits/fs_dir.h>
#include <experimental/bits/fs_ops.h>
namespace libasist { /* imports */
namespace fstd = std::experimental::filesystem;
} /* imports */
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
        "[mesg]%c" mesg "%c", \
        \
        "olog", \
        _FILE_NAME, \
        _FUNC_NAME, \
        _FILE_LINE, \
        text::ENDL_CHAR, ##args, text::ENDL_CHAR) \
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
        "[mesg]%c" mesg "%c", \
        \
        "elog", \
        _FILE_NAME, \
        _FUNC_NAME, \
        _FILE_LINE, \
        text::ENDL_CHAR, ##args, text::ENDL_CHAR) \
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

using fpaf_t = fstd::path;
using fdir_info_t = fstd::directory_entry;
using fdir_iter_t = fstd::directory_iterator;
using size_info_t = fstd::space_info;

} /* typedef */

#endif/*LIBASIST_HEAD_IPOP_HXX*/
