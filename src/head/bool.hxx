#pragma once

/* headers */

#include "conf.hxx"
#include "osys.hxx"
#include "tool.hxx"
#include "defn.hxx"
#include "type.hxx"

/* content */

namespace libasist { /* consdef */

constexpr auto TRUTH = true;
constexpr auto FALSE = false;

} /* consdef */

namespace libasist { /* typedef */

using bool_t = bool;
using flag_t = bool_t;

using v1bit_t = bool_t;
using v1b_t = v1bit_t;

} /* typedef */
