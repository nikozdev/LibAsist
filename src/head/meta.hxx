#ifndef LIBASIST_HEAD_META_HXX
#define LIBASIST_HEAD_META_HXX 1

/* headers */

#include "conf.hxx"
#include "osys.hxx"
#include "tool.hxx"
#include "defn.hxx"
#include "type.hxx"

/** standard **/

#include <algorithm>

/* defines */

#ifndef _ENUM_ACT_NUM
#define _ENUM_ACT_NUM( key, num, str ) key = num,
#endif/*_ENUM_ACT_NUM*/

#ifndef _ENUM_ACT_STR
#define _ENUM_ACT_STR( key, num, str ) [ key ] = str,
#endif/*_ENUM_ACT_STR*/

#ifndef _ENUM_DEF
#define _ENUM_DEF( ename, _FOR_ ) \
enum ename##_enum: int \
{ \
_FOR_(_ENUM_ACT_NUM) \
ename##_last, \
}; \
constexpr const char* ename##_text[] = \
{ \
_FOR_(_ENUM_ACT_STR) \
[ ename##_last ] = "last", \
};
#endif/*_ENUM_DEF*/

/* content */

namespace libasist { /* enumdef */

#ifndef _ENUM_FOR_ERROR
#define _ENUM_FOR_ERROR( _ACT_ ) \
_ACT_( error_none, 0x00, "none error" ) \
_ACT_( error_argc, 0x01, "invalid argument count" ) \
_ACT_( error_argv, 0x02, "invalid argument value" ) \
_ACT_( error_comd, 0x03, "invalid command" ) \
_ACT_( error_opts, 0x04, "invalid options" ) \
_ACT_( error_conf, 0x05, "invalid configuration" ) \
_ACT_( error_evar, 0x06, "invalid environment variable" ) \
_ACT_( error_proc, 0x07, "run-time error in the process" ) \
/* _ENUM_FOR_ERROR */
_ENUM_DEF( error, _ENUM_FOR_ERROR )
#endif/*_ENUM_FOR_ERROR*/

#ifndef _ENUM_FOR_TIMEZ
#define _ENUM_FOR_TIMEZ( _ACT_ ) \
_ACT_( timez_non, 0x0, "none time" ) \
_ACT_( timez_loc, 0x1, "local time" ) \
_ACT_( timez_gmt, 0x2, "global time" ) \
/* _ENM_FOR_TIMEZ */
_ENUM_DEF( timez, _ENUM_FOR_TIMEZ )
#endif/*_ENUM_FOR_TIMEZ*/

#ifndef _ENUM_FOR_FILEF
#define _ENUM_FOR_FILEF( _ACT_ ) \
\
_ACT_( filef_none, 0, "none" ) \
_ACT_( filef_nikodimage, 1, "nikodimage" ) \
/* _ENUM_FOR_FILEF */
_ENUM_DEF(filef, _ENUM_FOR_FILEF)
#endif/*_ENUM_FOR_FILEF*/
#ifndef _ENUM_FOR_ASCII
#define _ENUM_FOR_ASCII(_ACT_) \
/* control */ \
_ACT_( ascii_nul, 0x00, "zero terminator" ) \
_ACT_( ascii_soh, 0x01, "soh ?" ) \
_ACT_( ascii_stx, 0x02, "stx ?" ) \
_ACT_( ascii_etx, 0x03, "etx ?" ) \
_ACT_( ascii_eot, 0x04, "eot ?" ) \
_ACT_( ascii_enq, 0x05, "enq ?" ) \
_ACT_( ascii_ack, 0x06, "ack ?" ) \
_ACT_( ascii_bel, 0x07, "bell sound" ) \
_ACT_( ascii_bs,  0x08, "backspace" ) \
_ACT_( ascii_ht,  0x09, "horizontal tab" ) \
_ACT_( ascii_nl,  0x0a, "new line" ) \
_ACT_( ascii_vt,  0x0b, "vertical tab" ) \
_ACT_( ascii_np,  0x0c, "np ?" ) \
_ACT_( ascii_cr,  0x0d, "cariage return" ) \
_ACT_( ascii_so,  0x0e, "so ?" ) \
_ACT_( ascii_si,  0x0f, "si ?" ) \
_ACT_( ascii_dle, 0x10, "dle ?" ) \
_ACT_( ascii_dc1, 0x11, "dc1 ?" ) \
_ACT_( ascii_dc2, 0x12, "dc2 ?" ) \
_ACT_( ascii_dc3, 0x13, "dc3 ?" ) \
_ACT_( ascii_dc4, 0x14, "dc4 ?" ) \
_ACT_( ascii_nak, 0x15, "nak ?" ) \
_ACT_( ascii_syn, 0x16, "syn ?" ) \
_ACT_( ascii_etb, 0x17, "etb ?" ) \
_ACT_( ascii_can, 0x18, "can ?" ) \
_ACT_( ascii_em,  0x19, "em ?" ) \
_ACT_( ascii_sub, 0x1a, "sub ?" ) \
_ACT_( ascii_esc, 0x1b, "escape" ) \
_ACT_( ascii_fs,  0x1c, "fs ?" ) \
_ACT_( ascii_gs,  0x1d, "gs ?" ) \
_ACT_( ascii_rs,  0x1e, "rs ?" ) \
_ACT_( ascii_us,  0x1f, "us ?" ) \
/* visible */ \
_ACT_( ascii_sp,  0x20, "space" ) \
_ACT_( ascii_exs, 0x21, "exclamation-sign" ) \
_ACT_( ascii_dqt, 0x22, "double-quote" ) \
_ACT_( ascii_hash,0x23, "hash-symbol" ) \
_ACT_( ascii_cash,0x24, "dollar-sign" ) \
_ACT_( ascii_perc,0x25, "percent-sign" ) \
_ACT_( ascii_ands,0x26, "and-sign or ampersand" ) \
_ACT_( ascii_sqt, 0x27, "single-quote" ) \
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
_ACT_( ascii_usco,0x5f, "underscore" ) \
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
_ACT_( ascii_lcub,0x7b, "left-curly-bracket" ) \
_ACT_( ascii_vbar,0x7c, "vertical-bar" ) \
_ACT_( ascii_rcub,0x7d, "right-curly-bracket" ) \
_ACT_( ascii_tld, 0x7e, "tilde" ) \
_ACT_( ascii_del, 0x7f, "delete" ) \
/* _ENUM_FOR_ASCII */
_ENUM_DEF( ascii, _ENUM_FOR_ASCII )
#endif/*_ENUM_FOR_ASCII*/

} /* typedef */

namespace libasist { /* actions */

template<typename t_val_t>
[[nodiscard]] constexpr inline const t_val_t&
get_nodefault(const t_val_t&def, const t_val_t&val)
{ return val; }
template<typename t_val_t, typename...t_arg_t>
[[nodiscard]] constexpr inline const t_val_t&get_nodefault
(const t_val_t&def, const t_val_t&val, t_arg_t&&...arg)
{ return val == def ? get_nodefault(def, std::forward<t_arg_t>(arg)...) : val; }

template<typename t_com_t, typename t_mem_t>
[[nodiscard]] constexpr inline
decltype(auto)get_member(t_com_t&com, t_mem_t t_com_t::*mem)
{ return com.*mem; }
/* i did not know it for a while...
 * nodiscard attribute means that you should use returned value
 * that can also include [[nodiscard("comment-why-string")]] */
template<typename t_com_t, typename t_mem_t, typename...t_rem_t>
[[nodiscard]] constexpr inline
decltype(auto)get_member(t_com_t&com, t_mem_t t_com_t::*mem, t_rem_t&&... rem)
{ return get_member(com.*mem, std::forward<t_rem_t>(rem)...); }
/* we can keep a tuple of varargs and pass it here */
template<typename t_com_t, typename t_tup_t, size_t...t_index>
[[nodiscard]] constexpr inline
decltype(auto)get_member(t_com_t&com, t_tup_t&tup, std::index_sequence<t_index...>)
{ return get_member(com, std::get<t_index>(tup)...); }

template<typename t_com_t, typename t_tup_t>
[[nodiscard]] constexpr inline
decltype(auto)get_member(t_com_t&com, t_tup_t&tup)
{ return get_member(com, tup, std::make_index_sequence<std::tuple_size<t_tup_t>::value>()); }

} /* actions */

#endif/*LIBASIST_HEAD_META_HXX*/