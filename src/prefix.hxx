#pragma once

#ifndef _NAME
#    define _NAME       nameless
#endif /* _NAME */
#ifndef _NAME_STR
#    define _NAME_STR   "nameless"
#endif /* _NAME_STR */

#ifndef _VNUM
#    define _VNUM       0xa0a0a0
#endif /* _VNUM */
#ifndef _VNUM_STR
#    define _VNUM_STR   #_VNUM
#endif /* _VNUM_STR */

#define _TO_STR( text ) ( #text )

#ifndef FALSE
constexpr auto FALSE = false;
#endif
constexpr auto TRUTH = true;

constexpr auto ZERO = 0;
constexpr auto UNIT = 1;

constexpr auto TIME_FORMAT = "y%ym%md%d-h%Hm%Ms%S";

using v1c_t = char;
using v1s_t = long;
using v1u_t = unsigned long;

using msize_t = size_t;
using count_t = v1u_t;
using index_t = v1u_t;

template< typename type_t > inline const type_t& get_nodefault
( const type_t& def, const type_t& arg )
{
    return arg;
}
template< typename type_t, typename ... args_t > inline const type_t& get_nodefault
( const type_t& def, const type_t& arg, args_t&& ... args )
{
    return arg == def ? get_nodefault( def, std::forward< args_t >( args )... ) : arg;
}
template< typename ... args_t > inline const std::string& get_nodefault_string
( args_t&& ... args )
{
    std::string def;
    return get_nodefault( def, std::forward< args_t >( args )... );
}
