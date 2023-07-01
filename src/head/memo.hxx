#pragma once

/* headers */

#include "conf.hxx"
#include "osys.hxx"
#include "tool.hxx"
#include "exec.hxx"
#include "stdl.hxx"
#include "defn.hxx"
#include "type.hxx"
#include "meta.hxx"

/** standard **/

#include <new>
#include <memory>

/* defines */

#if defined(_CONF_WORK) || 1
/* 5-10% performance difference for me */
#   define LIBASIST_MEMO_MSIZE_SET
/* 10-20% performance difference for me */
#   define LIBASIST_MEMO_MSIZE_VET
#   define LIBASIST_MEMO_MDATA_VET
/* most of the times this is gonna break memory allocations */
#   define LIBASIST_MEMO_NEWDELDEF
#   define LIBASIST_MEMO_NEWDELDEF_ELOG
#endif/*ifd(_CONF_WORK)*/

/* content */

namespace libasist { /* typedef */

    using msize_t = size_t;

    using sbyte_t = signed char;
    using ubyte_t = unsigned char;
    using mbyte_t = char;
    using sdata_t = sbyte_t*;
    using udata_t = ubyte_t*;
    using mdata_t = void*;
    using msize_t = size_t;
    using mstep_t = msize_t;

} /* typedef */
