#pragma once

/* configs */

/* headers */

#include <ctime>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

#include <algorithm>
#include <vector>

#include <string>
#include <string_view>
#include <sstream>

#include <iostream>
#include <iomanip>
#include <filesystem>
#include <fstream>

#include <unistd.h>

/* defines */

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

#undef FALSE

#define _NAMESPACE_START namespace _NAME {
#define _NAMESPACE_CLOSE }

_NAMESPACE_START

/* constants */

constexpr auto FALSE = false;
constexpr auto TRUTH = true;

constexpr auto ZERO = 0;
constexpr auto UNIT = 1;

constexpr auto TIME_FORMAT = "y%ym%md%d-h%Hm%Ms%S";

/* typedefs */

#define _ENUM_ACT_NUM( key, num, str ) key = num,
#define _ENUM_ACT_STR( key, num, str ) [ key ] = str,
#define _ENUM_DEF( ename, _FOR_ ) \
\
enum ename##_enum: int \
{ \
    ename##_none = 0, \
    _FOR_( _ENUM_ACT_NUM ) \
    ename##_last, \
}; \
\
constexpr const char* ename##_text[] = \
{ \
    [ ename##_none ] = "none", \
    _FOR_( _ENUM_ACT_STR ) \
    [ ename##_last ] = "last", \
}; \
/* _DEF_ENUM */
#define _ENUM_FOR_ERROR( _ACT_ ) \
    \
    _ACT_( error_argc, 1, "invalid argument count" ) \
    _ACT_( error_argv, 2, "invalid argument value" ) \
    _ACT_( error_comd, 3, "invalid command" ) \
    _ACT_( error_opts, 4, "invalid options" ) \
    _ACT_( error_conf, 5, "invalid configuration" ) \
    _ACT_( error_evar, 6, "invalid environment variable" ) \
    _ACT_( error_proc, 7, "run-time error in the process" ) \
/* _ENUM_FOR_ERROR */
_ENUM_DEF( error, _ENUM_FOR_ERROR )
#define _ENUM_FOR_TIMEZ( _ACT_ ) \
    \
    _ACT_( timez_loc, 1, "local time" ) \
    _ACT_( timez_gmt, 2, "global time" ) \
/* _ENUM_FOR_TIMEZ */
_ENUM_DEF( timez, _ENUM_FOR_TIMEZ )
#define _ENUM_FOR_FILEF( _ACT_ ) \
    \
    _ACT_( filef_nikodimage, 1, "nikodimage" ) \
/* _ENUM_FOR_FILEF */
_ENUM_DEF( filef, _ENUM_FOR_FILEF )
#define _ENUM_FOR_ASCII( _ACT_ ) \
    /* control */ \
    _ACT_( ascii_nul, 0x00, "zero terminator" ) \
    _ACT_( ascii_soh, 0x01, "" ) \
    _ACT_( ascii_stx, 0x02, "" ) \
    _ACT_( ascii_etx, 0x03, "" ) \
    _ACT_( ascii_eot, 0x04, "" ) \
    _ACT_( ascii_enq, 0x05, "" ) \
    _ACT_( ascii_ack, 0x06, "" ) \
    _ACT_( ascii_bel, 0x07, "bell sound" ) \
    _ACT_( ascii_bs,  0x08, "backspace" ) \
    _ACT_( ascii_ht,  0x09, "horizontal tab" ) \
    _ACT_( ascii_nl,  0x0a, "new line" ) \
    _ACT_( ascii_vt,  0x0b, "vertical tab" ) \
    _ACT_( ascii_np,  0x0c, "" ) \
    _ACT_( ascii_cr,  0x0d, "cariage return" ) \
    _ACT_( ascii_so,  0x0e, "" ) \
    _ACT_( ascii_si,  0x0f, "" ) \
    _ACT_( ascii_dle, 0x10, "" ) \
    _ACT_( ascii_dc1, 0x11, "" ) \
    _ACT_( ascii_dc2, 0x12, "" ) \
    _ACT_( ascii_dc3, 0x13, "" ) \
    _ACT_( ascii_dc4, 0x14, "" ) \
    _ACT_( ascii_nak, 0x15, "" ) \
    _ACT_( ascii_syn, 0x16, "" ) \
    _ACT_( ascii_etb, 0x17, "" ) \
    _ACT_( ascii_can, 0x18, "" ) \
    _ACT_( ascii_em,  0x19, "" ) \
    _ACT_( ascii_sub, 0x1a, "" ) \
    _ACT_( ascii_esc, 0x1b, "" ) \
    _ACT_( ascii_fs,  0x1c, "" ) \
    _ACT_( ascii_gs,  0x1d, "" ) \
    _ACT_( ascii_rs,  0x1e, "" ) \
    _ACT_( ascii_us,  0x1f, "" ) \
    /* visible */ \
    _ACT_( ascii_sp,  0x20, "space" ) \
    _ACT_( ascii_exs, 0x21, "exclamation-sign" ) \
    _ACT_( ascii_qt2, 0x22, "double-quote" ) \
    _ACT_( ascii_hash,0x23, "hash-symbol" ) \
    _ACT_( ascii_cash,0x24, "dollar-sign" ) \
    _ACT_( ascii_perc,0x25, "percent-sign" ) \
    _ACT_( ascii_ands,0x26, "and-sign or ampersand" ) \
    _ACT_( ascii_qt1, 0x27, "single-quote" ) \
    _ACT_( ascii_lrb, 0x28, "left-round-bracket" ) \
    _ACT_( ascii_rrb, 0x29, "right-roud-bracket" ) \
    _ACT_( ascii_star,0x2a, "asterisk" ) \
    _ACT_( ascii_add, 0x2b, "plus" ) \
    _ACT_( ascii_com, 0x2c, "comma" ) \
    _ACT_( ascii_min, 0x2d, "minus" ) \
    _ACT_( ascii_dot, 0x2e, "dot" ) \
    _ACT_( ascii_fsl, 0x2f, "forward-slash" ) \
    _ACT_( ascii_n0,  0x30, "number-zero" ) \
    _ACT_( ascii_n1,  0x31, "number-one" ) \
    _ACT_( ascii_n2,  0x32, "number-two" ) \
    _ACT_( ascii_n3,  0x33, "number-three" ) \
    _ACT_( ascii_n4,  0x34, "number-four" ) \
    _ACT_( ascii_n5,  0x35, "number-five" ) \
    _ACT_( ascii_n6,  0x36, "number-six" ) \
    _ACT_( ascii_n7,  0x37, "number-seven" ) \
    _ACT_( ascii_n8,  0x38, "number-eight" ) \
    _ACT_( ascii_n9,  0x39, "number-nine" ) \
    _ACT_( ascii_col, 0x3a, "colon" ) \
    _ACT_( ascii_scol,0x3b, "semi-colon" ) \
    _ACT_( ascii_lts, 0x3c, "less-than-sign" ) \
    _ACT_( ascii_ets, 0x3d, "equal-to-sign" ) \
    _ACT_( ascii_mts, 0x3e, "more-than-sign" ) \
    _ACT_( ascii_qus, 0x3f, "question-sign" ) \
    _ACT_( ascii_at,  0x40, "at-sign" ) \
    _ACT_( ascii_A,   0x41, "capital-letter-a" ) \
    _ACT_( ascii_B,   0x42, "capital-letter-b" ) \
    _ACT_( ascii_C,   0x43, "capital-letter-c" ) \
    _ACT_( ascii_D,   0x44, "capital-letter-d" ) \
    _ACT_( ascii_E,   0x45, "capital-letter-e" ) \
    _ACT_( ascii_F,   0x46, "capital-letter-f" ) \
    _ACT_( ascii_G,   0x47, "capital-letter-g" ) \
    _ACT_( ascii_H,   0x48, "capital-letter-h" ) \
    _ACT_( ascii_I,   0x49, "capital-letter-i" ) \
    _ACT_( ascii_J,   0x4a, "capital-letter-j" ) \
    _ACT_( ascii_K,   0x4b, "capital-letter-k" ) \
    _ACT_( ascii_L,   0x4c, "capital-letter-l" ) \
    _ACT_( ascii_M,   0x4d, "capital-letter-m" ) \
    _ACT_( ascii_N,   0x4e, "capital-letter-n" ) \
    _ACT_( ascii_O,   0x4f, "capital-letter-o" ) \
    _ACT_( ascii_P,   0x50, "capital-letter-p" ) \
    _ACT_( ascii_Q,   0x51, "capital-letter-q" ) \
    _ACT_( ascii_R,   0x52, "capital-letter-r" ) \
    _ACT_( ascii_S,   0x53, "capital-letter-s" ) \
    _ACT_( ascii_T,   0x54, "capital-letter-t" ) \
    _ACT_( ascii_U,   0x55, "capital-letter-u" ) \
    _ACT_( ascii_V,   0x56, "capital-letter-v" ) \
    _ACT_( ascii_W,   0x57, "capital-letter-w" ) \
    _ACT_( ascii_X,   0x58, "capital-letter-x" ) \
    _ACT_( ascii_Y,   0x59, "capital-letter-y" ) \
    _ACT_( ascii_Z,   0x5a, "capital-letter-z" ) \
    _ACT_( ascii_lsb, 0x5b, "left-square-bracket" ) \
    _ACT_( ascii_bsl, 0x5c, "backward-slash" ) \
    _ACT_( ascii_rsb, 0x5d, "right-square-bracket" ) \
    _ACT_( ascii_car, 0x5e, "carret" ) \
    _ACT_( ascii_unds,0x5f, "underscore" ) \
    _ACT_( ascii_apos,0x60, "apostrophe" ) \
    _ACT_( ascii_a,   0x61, "letter-a" ) \
    _ACT_( ascii_b,   0x62, "letter-b" ) \
    _ACT_( ascii_c,   0x63, "letter-c" ) \
    _ACT_( ascii_d,   0x64, "letter-d" ) \
    _ACT_( ascii_e,   0x65, "letter-e" ) \
    _ACT_( ascii_f,   0x66, "letter-f" ) \
    _ACT_( ascii_g,   0x67, "letter-g" ) \
    _ACT_( ascii_h,   0x68, "letter-h" ) \
    _ACT_( ascii_i,   0x69, "letter-i" ) \
    _ACT_( ascii_j,   0x6a, "letter-j" ) \
    _ACT_( ascii_k,   0x6b, "letter-k" ) \
    _ACT_( ascii_l,   0x6c, "letter-l" ) \
    _ACT_( ascii_m,   0x6d, "letter-m" ) \
    _ACT_( ascii_n,   0x6e, "letter-n" ) \
    _ACT_( ascii_o,   0x6f, "letter-o" ) \
    _ACT_( ascii_p,   0x70, "letter-p" ) \
    _ACT_( ascii_q,   0x71, "letter-q" ) \
    _ACT_( ascii_r,   0x72, "letter-r" ) \
    _ACT_( ascii_s,   0x73, "letter-s" ) \
    _ACT_( ascii_t,   0x74, "letter-t" ) \
    _ACT_( ascii_u,   0x75, "letter-u" ) \
    _ACT_( ascii_v,   0x76, "letter-v" ) \
    _ACT_( ascii_w,   0x77, "letter-w" ) \
    _ACT_( ascii_x,   0x78, "letter-x" ) \
    _ACT_( ascii_y,   0x79, "letter-y" ) \
    _ACT_( ascii_z,   0x7a, "letter-z" ) \
    _ACT_( ascii_lcb, 0x7b, "left-curly-bracket" ) \
    _ACT_( ascii_bar, 0x7c, "vertical-bar" ) \
    _ACT_( ascii_rcb, 0x7d, "right-curly-bracket" ) \
    _ACT_( ascii_tld, 0x7e, "tilde" ) \
    _ACT_( ascii_del, 0x7f, "delete" ) \
/* _ENUM_FOR_ASCII */
_ENUM_DEF( ascii, _ENUM_FOR_ASCII )

using v1c_t = char;
using v1s_t = long;
using v1u_t = unsigned long;

using msize_t = size_t;
using count_t = v1u_t;
using index_t = v1u_t;

template < typename value_t, count_t count >
class vec_t_t
{
    /* typedefs */

    using this_t = vec_t_t< value_t, count >;

    using vdata_t = value_t[ count ];

public:

    /* codetor */

    vec_t_t():
        vdata{ ZERO }
    {
    }
    vec_t_t( std::initializer_list< value_t > ilist ):
        vdata{ ZERO }
    {
        auto iter = ilist.begin();
        for ( auto index = 0; index < ilist.size(); index++ )
        {
            this->vdata[ index ] = *(iter++);
        }
    }
    vec_t_t( value_t value ):
        this_t()
    {
        for ( auto index = 0; index < count; index++ )
        {
            this->vdata[ index ] = value;
        }
    }
    vec_t_t( const vec_t_t& copy ):
        this_t()
    {
        std::memcpy( this, &copy, get_msize() );
    }
    vec_t_t( vec_t_t&& copy ):
        this_t()
    {
        std::memmove( this, &copy, get_msize() );
    }

    /* getters */

    static count_t get_count()
    {
        return count;
    }
    static msize_t get_msize()
    {
        return count * sizeof( value_t );
    }

    /* operators */

    this_t& operator= ( value_t value )
    {
        for ( auto index = 0; index < count; index++ )
        {
            this->vdata[ index ] = value;
        }
        return *this;
    }
    this_t& operator= ( const this_t& copy )
    {
        std::memcpy( this, &copy, get_msize() );
        return *this;
    }
    this_t& operator= ( this_t&& copy )
    {
        std::memmove( this, &copy, get_msize() );
        return *this;
    }

    template< typename stream_t = std::ostream >
    stream_t& operator<<( stream_t& stream ) const
    {
        for ( auto index = 0; index < count; index++ )
        {
            stream << this->vdata[ index ] << " ";
        }
        return stream;
    }
    template< typename stream_t = std::istream >
    const stream_t& operator>>( const stream_t& stream )
    {
        for ( auto index = 0; index < count; index++ )
        {
            stream >> this->vdata[ index ];
        }
        return stream;
    }

#define _VEC_DEF_ARITH( sign ) \
    \
this_t& operator sign##=( value_t value ) \
{ \
    for ( auto index = 0; index < count; index++ ) \
    { \
        this->vdata[ index ] = this->vdata[ index ] sign value; \
    } \
    return *this; \
} \
this_t operator sign ( value_t value ) const \
{ \
    this_t result; \
    for ( auto index = 0; index < count; index++ ) \
    { \
        result.vdata[ index ] = this->vdata[ index ] sign value; \
    } \
    return result; \
} \
this_t& operator sign##=( const this_t& vector ) \
{ \
    for ( auto index = 0; index < count; index++ ) \
    { \
        this->vdata[ index ] = this->vdata[ index ] sign vector.vdata[ index ]; \
    } \
    return *this; \
} \
this_t operator sign ( const this_t& vector ) const \
{ \
    this_t result; \
    for ( auto index = 0; index < count; index++ ) \
    { \
        result.vdata[ index ] = this->vdata[ index ] sign vector.vdata[ index ]; \
    } \
    return result; \
} \
/* _VEC_DEF_ARITH */
_VEC_DEF_ARITH( + )
_VEC_DEF_ARITH( - )
_VEC_DEF_ARITH( / )
_VEC_DEF_ARITH( * )

    value_t&operator[]( index_t index )
    {
        return this->vdata[ index ];
    }
    value_t operator[]( index_t index ) const
    {
        return this->vdata[ index ];
    }

private:

    /* variables */

    vdata_t vdata;
};
template< typename stream_t, typename value_t, count_t count >
stream_t& operator<<( stream_t& stream, const vec_t_t< value_t, count >& vector )
{
    for ( auto index = 0; index < count; index++ )
    {
        stream << vector[ index ] << " ";
    }
    return stream;
}
template< typename stream_t, typename value_t, count_t count >
const stream_t& operator>>( const stream_t& stream, vec_t_t< value_t, count >& vector )
{
    for ( auto index = 0; index < count; index++ )
    {
        stream >> vector[ index ];
    }
    return stream;
}
#define _PRIM_FOR( _ACT_ ) \
    \
    _ACT_( c, 2 ) \
    _ACT_( c, 3 ) \
    _ACT_( c, 4 ) \
    _ACT_( u, 2 ) \
    _ACT_( u, 3 ) \
    _ACT_( u, 4 ) \
    _ACT_( s, 2 ) \
    _ACT_( s, 3 ) \
    _ACT_( s, 4 ) \
/* _PRIM_FOR */
#define _PRIM_DEF_ACT( tchar, count ) \
    typedef vec_t_t< v1##tchar##_t, count > v##count##tchar##_t;
_PRIM_FOR( _PRIM_DEF_ACT )

using coord_t = v2s_t;
using sizes_t = v2u_t;

struct version_t
{
    union
    {
        const index_t parts[ 3 ];
        struct
        {
            const index_t major;
            const index_t minor;
            const index_t micro;
        };
    };
    const index_t whole;
};
template< typename stream_t = std::ostream >
stream_t& operator<<( stream_t& stream, const version_t& version )
{
    auto flags = stream.flags();
    stream << "[major]=" << version.major << ";";
    stream << "[minor]=" << version.minor << ";";
    stream << "[micro]=" << version.micro << ";";
    stream << std::hex;
    stream << "[whole]=" << version.whole << ";";
    stream.flags( flags );
    return stream;
}

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
    const auto head = cli.args.begin() + 1;
    const auto tail = cli.args.end() - 1;
    const auto last = cli.args.end();
    if ( opt[ 0 ] == '-' )
    {
        if ( opt[ 1 ] == '-' )
        {
            for ( auto iter = head; iter != last; iter++ )
            {
                auto offset = (*iter).find( '=' );
                if ( offset == -1 )
                {
                    if ( *iter == opt )
                    {
                        if ( iter == tail )
                        {
                            help( error_argv );
                            return "";
                        }
                        return std::string( *( ++iter ) );
                    }
                }
                else if ( ( *iter ).find( opt ) != -1 )
                {
                    return std::string( *iter ).substr( offset + 1 );
                }
            }
        }
        else
        {
            for ( auto iter = head; iter < last; iter++ )
            {
                if ( *iter == opt )
                {
                    return std::string( *( ++iter ) );
                }
            }
        }
    }
    return "";
}
inline bool vet_opt( const std::string_view& opt )
{
    const auto head = cli.args.begin() + 1;
    const auto last = cli.args.end();
    for ( auto iter = head; iter < last; iter++ )
    {
        if ( ( *iter ).find( opt ) != -1 )
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

    template < typename num_t >
inline count_t get_digit_count( num_t numval, count_t numsys )
{
    count_t count = ZERO;
    if ( numsys < 2 )
    {
        return -1;
    }
    while( numval > 0 )
    {
        numval /= numsys;
        count += 1;
    }
    return count;
}
    template < typename num_t >
num_t get_digit_l( num_t numval, index_t digpos, index_t numsys = 10 )
{
    return numval % std::pow( numsys, digpos + 1 ) / std::pow( numsys, digpos - 1 );
}
    template < typename num_t >
num_t get_digit_r( num_t numval, index_t digpos, index_t numsys = 10 )
{
    return numval / std::pow( numsys, digpos - 1 ) % numsys;
}

    template < typename num_t >
num_t get_reversed( num_t numval, count_t numsys = 10 )
{
    auto numrev = numval - numval;
    while( numval > 0 )
    {
        numrev += numval % numsys;
        numrev *= numsys;
        numval /= numsys;
    }
    return numrev;
}

inline
version_t get_version( index_t whole = _VNUM )
{
    index_t scale = UNIT;
    index_t part_index = ZERO;
    index_t part_list[ 3 ] = { ZERO, ZERO, ZERO };
    index_t part = ZERO;
    index_t temp = whole;
    while( temp > ZERO )
    {
        auto digit = temp % 16;
        if ( digit == 0xa )
        {
            part_list[ part_index ] = part;
            part_index += UNIT;
            if ( part_index >= 3 )
            {
                /* error */
                break;
            }
            part = ZERO;
            scale = UNIT;
        }
        else
        {
            part += scale * digit;
            scale *= 10;
        }
        temp = temp / 16;
    }
    return {
        .parts = { part_list[ 2 ], part_list[ 1 ], part_list[ 0 ] },
        .whole = whole
    };
}

int main( int argc, const char* argv[] )
{
    cli.args = std::vector< const std::string_view >( argv, argv + argc );
    std::clog << std::endl;
    if ( TRUTH )
    {
        std::clog << "(" << "[" << _NAME_STR << "]" << "[args]" << std::endl;
        std::copy( argv, argv + argc, std::ostream_iterator< const char* >( std::clog, "\n" ) );
        std::clog << "[" << _NAME_STR << "]" << "[args]" << ")" << std::endl;
        std::clog << std::endl;
    }
    if ( FALSE )
    {
        v2s_t v2s1 = { 0, 1 };
        v2s_t v2s2 = v2s1 + 1;
        v2s_t v2s3 = v2s1 + v2s2;
        std::clog << v2s1 << v2s2 << v2s3 << std::endl;
        std::clog << std::endl;
    }
    if ( FALSE )
    {
        std::clog << "get -t = " << get_opt( "-t" ) << std::endl;
        std::clog << "get --test = " << get_opt( "--test" ) << std::endl;
        std::clog << "vet --test = " << vet_opt( "--test" ) << std::endl;
        std::clog << "get --arg = " << get_opt( "--arg" ) << std::endl;
        std::clog << "vet --arg = " << vet_opt( "--arg" ) << std::endl;
        std::clog << std::endl;
    }
    if ( FALSE )
    {
        std::clog << "the value is ";
        std::clog << get_nodefault_string(
            get_opt( "-c" ),
            get_opt( "--config" ),
            get_env( "config" ),
            std::string( "not found" )
            ) << std::endl;
        std::clog << std::endl;
    }
    if ( FALSE )
    {
#define _ENUM_ACT_PRINT( key, num, str ) \
        std::clog << _TO_STR( key ) << " = " << num << std::endl;
        _ENUM_FOR_ASCII( _ENUM_ACT_PRINT )
        std::clog << std::endl;
    }
    if ( TRUTH )
    {
        std::clog << "version parsing" << std::endl;
        std::clog << get_version( _VNUM ) << std::endl;
        std::clog << get_version( 0xa0a0a0 ) << std::endl;
        std::clog << get_version( 0xa0a0a1 ) << std::endl;
        std::clog << get_version( 0xa1a0a1 ) << std::endl;
        std::clog << get_version( 0xa1a2a1 ) << std::endl;
        std::clog << get_version( 0xa0a0a10 ) << std::endl;
        std::clog << get_version( 0xa1a0a10 ) << std::endl;
        std::clog << get_version( 0xa87a5a10 ) << std::endl;
        std::clog << get_version( 0xa987a654a321 ) << std::endl;
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
