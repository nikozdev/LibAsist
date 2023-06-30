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
#include "nums.hxx"

/** standard **/

#include <new>
#include <memory>

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
