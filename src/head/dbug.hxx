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
#include "ipop.hxx"

/* defines */

/** consdef **/

#ifndef _FILE_NAME
#define _FILE_NAME __FILE__
#endif/*_FILE_NAME*/
#ifndef _FILE_LINE
#define _FILE_LINE __LINE__
#endif/*_FILE_LINE*/

#ifndef _FUNC_NAME
#define _FUNC_NAME __FUNCTION__
#endif/*_FUNC_NAME*/
#ifndef _FUNC_SIGN
#define _FUNC_SIGN __PRETTY_FUNCTION__
#endif/*_FUNC_SIGN*/

/** actions **/

#ifndef _ERROR
#define _ERROR( code, actn, args... ) ({ \
    _ELOG( args ); \
    ::libasist::breakpoint(); \
    bugecode = code; \
    actn; \
})
#endif/*_ERROR - raise an error signal */

#ifndef _EFNOT
#define _EFNOT( expr, actn, args... ) ({ \
    if ( (expr) == FALSE ) \
    { \
        _ERROR( 1, actn, args ); \
    } \
})
#endif/*_EFNOT - error if not */

#ifndef _PCALL
#define _PCALL( exec, actn, ... ) ({ \
    exec; \
    _EFNOT( \
        ::libasist::bugecode == ZERO, \
        { \
            actn; \
            ::libasist::bugecode = ZERO; \
        }, \
        __VA_ARGS__ ); \
})
#endif/*_PCALL - protected call */

/* content */

namespace libasist { /* datadef */

    static inline size_t bugecode = 0;

} /* datadef */

namespace libasist { /* actions */

#ifdef _CONF_WORK
#   ifdef SIGINT
    inline auto breakpoint()
    {  std::raise(SIGINT); }
#   elif(defined(_OSYS_WINOS))
    inline auto breakpoint()
    { _EPUT(text::BELL_CSTR); system("pause"); }
#   else
#   endif/*SIGINT*/
#else
    inline auto breakpoint() {}
#endif/*_CONF_WORK*/

} /* actions */
