#ifndef LIBASIST_HEAD_TYPE_HXX
#define LIBASIST_HEAD_TYPE_HXX 1

/* headers */

#include "conf.hxx"
#include "osys.hxx"
#include "tool.hxx"
#include "defn.hxx"

/** standard **/

#include <type_traits>

/* content */

namespace libasist { /* typedef */

using void_t = void;

template<typename val_t, int uuid = 0> struct v2v_t
{ val_t x = 0, y = 0; };
template<typename val_t, int uuid = 0> struct v3v_t
{ val_t x = 0, y = 0, z = 0; };
template<typename val_t, int uuid = 0> struct v4v_t
{ val_t x = 0, y = 0, z = 0, w = 0; };

} /* typedef */

#endif/*LIBASIST_HEAD_TYPE_HXX*/
