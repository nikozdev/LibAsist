#ifndef LIBASIST_HEAD_TIME_HXX
#define LIBASIST_HEAD_TIME_HXX 1

/* headers */

#include "conf.hxx"
#include "osys.hxx"
#include "tool.hxx"
#include "defn.hxx"

/** standard **/

#include <ctime>

/* content */

namespace libasist { namespace time { /* consdef */

    constexpr auto FORMAT = "y%ym%md%d-h%Hm%Ms%S";

} } /* consdef */

#endif/*LIBASIST_HEAD_TIME_HXX*/
