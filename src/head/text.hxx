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

/** standard **/

#include <string>
#include <cstring>

#include <string_view>

#include <sstream>

/* defines */

#ifndef _GET_STR
#define _GET_STR(str) #str
#endif/*_GET_STR*/

/* content */

namespace libasist { /* typedef */

using schar_t = char; /* standard character */
using uchar_t = unsigned char; /* unsigned character */

using scstr_t = const schar_t*; /* standard constant string */
using ucstr_t = const uchar_t*; /* unsigned constant string */

using svstr_t = std::basic_string_view<schar_t>; /* standard view string */
using uvstr_t = std::basic_string_view<uchar_t>; /* unsigned view string */

using sdstr_t = std::basic_string<schar_t>; /* standard dynamic string */
using udstr_t = std::basic_string<uchar_t>; /* unsgined dynamic string */

/* template hash string template type */
template< typename t_char_t>
class thstr_t
{
public: /* typedef */

    using this_t = thstr_t<t_char_t>;

    using data_t = t_char_t;
    using hash_t = v1u_t;

    typedef struct const_wrap_t
    {
    public: /* codetor */
        constexpr
        const_wrap_t(data_t*data) noexcept
        : data{data} {}
    public: /* datadef */
        data_t*data;
    } const_wrap_t;

public: /* consdef */

    static constexpr hash_t MOVED = 0xff'ff'ff'ff;
    static constexpr hash_t PRIME = 0x00'ff'ff'ff;

public: /* codetor */

    constexpr
    thstr_t() noexcept {}

    constexpr
    thstr_t(const data_t*data, size_t size, hash_t hash) noexcept
    : orig{ data }, size{ size }, hash{ hash } {}

    constexpr
    thstr_t(const data_t*data, size_t size) noexcept
    : this_t{ make_hstr(data, size) } {}

    template<size_t t_size>
    constexpr
    thstr_t(const data_t*(&data)[t_size]) noexcept
    : this_t{ make_hstr(data, t_size) } {}

    explicit constexpr thstr_t(const_wrap_t wrap) noexcept
    : this_t{ make_hstr(wrap.data) } {}

public: /* actions */

    [[nodiscard]] static constexpr
    auto make_hstr(const data_t*data) noexcept
    {
        hash_t hash = this_t::MOVED;
        size_t size = 0;

        for(; data[size]; ++size)
        { hash = (hash ^ static_cast<hash_t>(data[size])) * PRIME; }

        return this_t{ data, size, hash };
    }
    [[nodiscard]] static constexpr
    auto make_hstr(const data_t*data, size_t size) noexcept
    {
        hash_t hash = this_t::MOVED;

        for(size_t step{}; step < size; ++step)
        { hash = (hash ^ static_cast<hash_t>(data[step])) * PRIME; }

        return this_t{ data, size, hash };
    }

    [[nodiscard]] static constexpr
    hash_t make_hash(const data_t*data, const size_t size) noexcept
    { return make_hstr(data, size); }
    template<size_t t_size>
    [[nodiscard]] static constexpr
    hash_t make_hash(const data_t*(&data)[t_size]) noexcept
    { return make_hstr(data, t_size); }
    [[nodiscard]] static constexpr
    hash_t make_hash(const_wrap_t wrap) noexcept
    { return make_hstr(wrap); }

public: /* symbols */

    [[nodiscard]] constexpr
    operator hash_t()const noexcept
    { return this->hash; }

    [[nodiscard]] constexpr
    explicit operator data_t()const noexcept
    { return this->orig; }

public: /* datadef */

    const data_t*orig;
    const size_t size;
    const hash_t hash;

}; /* template hash string template type */

/* standard hashed string type */
using shstr_t = thstr_t<schar_t>;

/* deduction guide for a dynamic character array */
template<typename t_char_t>
thstr_t(const t_char_t*data, const size_t size) -> thstr_t<t_char_t>;
/* deduction guide for a static character array */
template<typename t_char_t, size_t t_size>
thstr_t(const t_char_t(&data)[t_size]) -> thstr_t<t_char_t>;

namespace text { /* special chars */

struct endl_t {
    constexpr explicit operator schar_t() { return '\n'; }
    constexpr operator scstr_t() { return "\n"; }
} static inline endl;
struct ends_t {
    constexpr explicit operator schar_t() { return '\0'; }
    constexpr operator scstr_t() { return "\0"; }
} static inline ends;
struct bell_t {
    constexpr explicit operator schar_t() { return '\a'; }
    constexpr operator scstr_t() { return "\a"; }
} static inline bell;

} /** special chars **/

} /* typedef */

namespace libasist { namespace text { /* consdef */

constexpr scstr_t BELL_CSTR = "\a";
constexpr schar_t BELL_CHAR = '\a';
constexpr scstr_t ENDL_CSTR = "\n";
constexpr schar_t ENDL_CHAR = '\n';
constexpr scstr_t ENDS_CSTR = "\0";
constexpr schar_t ENDS_CHAR = '\0';

} } /* constdef */

namespace libasist { /* operats */

template<typename t_char_t>
[[nodiscard]] constexpr inline
bool operator==(const thstr_t<t_char_t>&lhs, const thstr_t<t_char_t>&rhs)
{ return lhs.hash == rhs.hash; }
template<typename t_char_t>
[[nodiscard]] constexpr inline
bool operator!=(const thstr_t<t_char_t>&lhs, const thstr_t<t_char_t>&rhs)
{ return !(lhs == rhs); }

template<typename t_char_t>
[[nodiscard]] constexpr inline
bool operator< (const thstr_t<t_char_t>&lhs, const thstr_t<t_char_t>&rhs)
{ return lhs.hash < rhs.hash; }
template<typename t_char_t>
[[nodiscard]] constexpr inline
bool operator<=(const thstr_t<t_char_t>&lhs, const thstr_t<t_char_t>&rhs)
{ return !(rhs < lhs); }

template<typename t_char_t>
[[nodiscard]] constexpr inline
bool operator> (const thstr_t<t_char_t>&lhs, const thstr_t<t_char_t>&rhs)
{ return rhs < lhs; }
template<typename t_char_t>
[[nodiscard]] constexpr inline
bool operator>=(const thstr_t<t_char_t>&lhs, const thstr_t<t_char_t>&rhs)
{ return !(lhs < rhs); }

[[nodiscard]] constexpr inline
scstr_t operator""_scstr(const char*mdata, std::size_t msize) noexcept
{ return mdata; }

[[nodiscard]] constexpr inline
sdstr_t operator""_sdstr(const char*mdata, std::size_t msize) noexcept
{ return sdstr_t(mdata, msize); }

[[nodiscard]] constexpr inline
shstr_t operator""_shstr(const char*mdata, std::size_t msize) noexcept
{ return shstr_t::make_hstr(mdata, msize); }

} /* operats */
