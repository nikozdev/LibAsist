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
#define _OPUT( ... ) { \
    std::format_to( \
        std::ostream_iterator< \
        decltype(std::cout)::char_type \
        >(std::cout), \
        __VA_ARGS__ \
    ); \
}
#endif/*_OPUT*/
#ifndef _OLOG
#define _OLOG( ... ) { \
    _OPUT( \
        "[from]{:s}" \
        "[file]{:s}" \
        "[func]{:s}" \
        "[line]{:d}" \
        "[mesg]{:c}{:s}{:c}", \
        \
        "olog", \
        _FILE_NAME, \
        _FUNC_NAME, \
        _FILE_LINE, \
        text::ENDL_CHAR, \
        std::format( __VA_ARGS__ ), \
        text::ENDL_CHAR \
    ); \
}
#endif/*_OLOG*/

#ifndef _EPUT
#define _EPUT( ... ) { \
    std::format_to( \
        std::ostream_iterator< \
        decltype(std::cerr)::char_type \
        >(std::cout), \
        __VA_ARGS__ \
    ); \
}
#endif/*_EPUT*/
#ifndef _ELOG
#define _ELOG( ... ) { \
    _EPUT( \
        "[from]{:s}" \
        "[file]{:s}" \
        "[func]{:s}" \
        "[line]{:d}" \
        "[mesg]{:c}{:s}{:c}", \
        \
        "elog", \
        _FILE_NAME, \
        _FUNC_NAME, \
        _FILE_LINE, \
        text::ENDL_CHAR, \
        std::format( __VA_ARGS__ ), \
        text::ENDL_CHAR \
    ); \
}
#endif/*_ELOG*/

/* content */

namespace libasist { /* typedef */

using fpaf_t = fstd::path;
using fdir_info_t = fstd::directory_entry;
using fdir_iter_t = fstd::directory_iterator;
using size_info_t = fstd::space_info;

} /* typedef */

#endif/*LIBASIST_HEAD_IPOP_HXX*/
