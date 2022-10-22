#pragma once

/* configs */

/* headers */

#include <ctime>
#include <cstdio>
#include <cstring>
#include <cstdlib>

#include <algorithm>
#include <vector>
#include <string>
#include <string_view>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>

#include <unistd.h>

/* defines */

#ifndef _NAME
#    define _NAME       nameless
#    define _NAME_STR   "nameless"
#endif /* _NAME */
#ifndef _VERS
#    define _VERS       0a0a0
#    define _VERS_STR   "0a0a0"
#endif /* _VERS */

#define _TO_STR( text ) ( #text )

#undef FALSE

#define _NAMESPACE_START namespace _NAME {
#define _NAMESPACE_CLOSE }

_NAMESPACE_START

/* constants */

constexpr auto FALSE = false;
constexpr auto TRUTH = true;

constexpr auto ZERO = 0;
constexpr auto UNIT = 1;

std::string TIME_FORMAT = "y%ym%md%d-h%Hm%Ms%S";

/* typedefs */

#define _ENUM_DEF( name, _FOR_, _ACT_ENUM_, _ACT_TEXT_ ) \
    \
enum name##_enum: int \
{ \
    name##_none, \
    _FOR_( _ACT_ENUM_ ) \
    name##_last,\
}; \
const char* name##_text[] = \
{ \
    [ name##_none ] = _TO_STR( name##_none ), \
    _FOR_( _ACT_TEXT_ ) \
    [ name##_last ] = _TO_STR( name##_last ), \
}; \
/* ENUM_DEF */
#define _ACT_ENUM( ename, iname ) ename##_##iname,
#define _ACT_TEXT( ename, iname ) [ ename##_##iname ] = _TO_STR( ename##_##iname ),

#define _FOR_ERROR( _ACT_ ) \
    \
    _ACT_( argc ) /* argument count */ \
    _ACT_( argv ) /* argument value */ \
    _ACT_( comd ) /* command */ \
    _ACT_( opts ) /* options */ \
    _ACT_( conf ) /* configuration */ \
    _ACT_( evar ) /* environment variable */ \
    _ACT_( proc ) /* process error */ \
/* _FOR_ERROR */
#define _ACT_ENUM_ERROR( name ) _ACT_ENUM( error, name )
#define _ACT_TEXT_ERROR( name ) _ACT_TEXT( error, name )
_ENUM_DEF( error, _FOR_ERROR, _ACT_ENUM_ERROR, _ACT_TEXT_ERROR )

#define _FOR_TIMEZ( _ACT ) \
    \
    _ACT( loc ) /* local time */ \
    _ACT( gmt ) /* global time */ \
/* _FOR_TIMEZ */
#define _ACT_ENUM_TIMEZ( name ) _ACT_ENUM( timez, name )
#define _ACT_TEXT_TIMEZ( name ) _ACT_TEXT( timez, name )
_ENUM_DEF( timez, _FOR_TIMEZ, _ACT_ENUM_TIMEZ, _ACT_TEXT_TIMEZ )

using v1s_t = int;
struct v2s_t
{
    v1s_t x;
    v1s_t y;
};
using v1u_t = unsigned int;
struct v2u_t
{
    v1u_t x;
    v1u_t y;
};

using coord_t = v2s_t;
using sizes_t = v2u_t;

/* variables */

struct
{
    std::vector< const std::string_view > args;
} cli;

/* functions */

inline error_enum help( error_enum error )
{
    if ( error == error_none ) { return error; }

    std::cerr << "[" _NAME_STR "]" << "[help]" << std::endl;
    {
        std::cerr << "- usage" << std::endl;
        {
            std::cerr << "> " << _NAME_STR << " [-o|--option]..." << std::endl;
        }
        std::cerr << "- options" << std::endl;
        {
        }
        std::cerr << "- error" << std::endl;
        {
            std::cerr << "> code=" << static_cast< int >( error ) << std::endl;
            std::cerr << "> text=" << error_text[ error ] << std::endl;
        }
    }
    return error;
}

inline std::string get_opt( const std::string_view& opt )
{
    if ( cli.args.size() == 1 || opt.size() < 2 )
    {
        return "";
    }
    if ( opt[ 0 ] == '-' )
    {
        if ( opt[ 1 ] == '-' )
        {
            for ( auto iter = cli.args.begin() + 1; iter != ( cli.args.end() - 1 ); iter++ )
            {
                if ( *iter == opt )
                {
                    auto offset = (*iter).find( '=' );
                    if ( offset == -1 )
                    {
                        return "";
                    }
                    std::string value( (*iter).substr( offset ) );
                    return value;
                }
            }
        }
        else
        {
            for ( auto iter = cli.args.begin() + 1; iter != ( cli.args.end() - 1 ); iter++ )
            {
                if ( *iter == opt )
                {
                    std::string value( *(++iter) );
                    return value;
                }
            }
        }
    }
    else
    {
        return "";
    }
    return "";
}
inline bool vet_opt( const std::string_view& opt )
{
    for ( auto iter = cli.args.begin() + 1; iter != ( cli.args.end() - 1 ); iter++ )
    {
        if ( *iter == opt )
        {
            return TRUTH;
        }
    }
    return FALSE;
}

inline std::string get_env( const std::string_view& name )
{
    const char* nstr = &name[0];
    auto estr =  std::getenv( nstr );

    return estr == NULL ? std::string() : std::string( estr );
}

    template< typename type_t >
inline const type_t& get_nodefault( const type_t& def, const type_t& arg )
{
    return arg;
}
    template< typename type_t, typename ... args_t >
inline const type_t& get_nodefault( const type_t& def, const type_t& arg, args_t&& ... args )
{
    return arg == def ? get_nodefault( def, std::forward< args_t >( args )... ) : arg;
}
    template< typename ... args_t >
inline const std::string& get_nodefault_string( args_t&& ... args )
{
    std::string def;
    return get_nodefault( def, std::forward< args_t >( args )... );
}

int main( int argc, const char* argv[] )
{
    cli.args = std::vector< const std::string_view >( argv, argv + argc );
    {
        std::clog << std::endl;
        std::clog << "(" << "[" << _NAME_STR << "]" << "[args]" << std::endl;
        std::copy( argv, argv + argc, std::ostream_iterator< const char* >( std::clog, "\n" ) );
        std::clog << "[" << _NAME_STR << "]" << "[args]" << ")" << std::endl;
        std::clog << std::endl;
    }
    return error_none;
}

_NAMESPACE_CLOSE

#ifdef _TYPE_RUN
#undef _TYPE_RUN
int main( int argc, const char** argv )
{
    return _NAME::main( argc, argv );
}
#endif/*TYPE_RUN*/
/* license: none

*/
