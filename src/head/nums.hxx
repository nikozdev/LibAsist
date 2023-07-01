#pragma once

/* headers */

#include "conf.hxx"
#include "osys.hxx"
#include "tool.hxx"
#include "defn.hxx"
#include "type.hxx"
#include "meta.hxx"
#include "bool.hxx"
#include "memo.hxx"

/** standard **/

#include <cmath>
#include <numeric>
#include <cstdint>

/* content */

namespace libasist { /* typedef */

using v1u08_t = uint8_t;
using v1u16_t = uint16_t;
using v1u32_t = uint32_t;
using v1u64_t = uint64_t;
using v1u_t = unsigned;

using v1s08_t = int8_t;
using v1s16_t = int16_t;
using v1s32_t = int32_t;
using v1s64_t = int64_t;
using v1s_t = signed;

using v1f32_t = float;
using v1f64_t = float;
using v1f_t = float;

using index_t = v1s64_t;
using count_t = v1u64_t;

} /* typedef */

namespace libasist { /* consdef */

constexpr auto ZERO = 0;
constexpr auto UNIT = 1;

/* default values to use as placeholders */

const count_t COUNT_ZERO = 0;
const count_t COUNT_UNIT = 1;
const index_t INDEX_ZERO = 0;
const index_t INDEX_UNIT = 1;

} /* consdef */

namespace libasist { namespace nums { /* getters */

/* get -1 or +1 from a number */
template<typename value_t = v1s_t>
[[nodiscard]] constexpr inline
auto get_sign(value_t value)
{
    static_assert(
        std::is_signed<value_t>().value,
        "cannot get sign of unsigned numbers"
    );
    return value < 0 ? -1 : +1;
}

/* get a number multiplied by itself <power> times */
template<typename value_t = v1s_t>
[[nodiscard]] constexpr inline
auto get_power(value_t value, value_t power)
{ return std::pow(value, power); }

/* get an amount of digits in the given numeric system */
template<typename value_t = v1s_t, count_t numsys = 10>
[[nodiscard]] constexpr inline
auto get_count(value_t numval)
{
    static_assert(
        (numsys > 1),
        "no support for a numeric system with less than 1 digit"
    );
    count_t count = ZERO;
    while(numval > 0)
    {
        numval /= numsys;
        count += 1;
    }
    return count;
}

/* get a digit from the left side of a number by the given position */
template<typename value_t = v1s_t, count_t numsys = 10>
[[nodiscard]] constexpr inline
value_t get_lside
(value_t numval, index_t digpos)
{
    static_assert(
        (numsys > 1),
        "no support for a numeric system with less than 1 digit"
    );
    return numval
    % get_power<value_t>(numsys, digpos + 1)
    / get_power<value_t>(numsys, digpos - 1);
} /* get_froml */
/* get a digit from the right side of a number by the given position */
template<typename value_t = v1s_t, count_t numsys = 10>
[[nodiscard]] constexpr inline
value_t get_rside
(value_t numval, index_t digpos)
{
    static_assert(
        (numsys > 1),
        "no support for a numeric system with less than 1 digit"
    );
    return numval
    / get_power<value_t>(numsys, digpos - 1) % numsys;
} /* get_fromr */

/* reverse a number from right to left */
template<typename value_t, count_t numsys = 10>
[[nodiscard]] constexpr inline
value_t get_reversed
(value_t numval)
{
    static_assert(
        (numsys > 1),
        "no support for a numeric system with less than 1 digit"
    );
    auto numrev = 0;
    while(numval > numsys)
    {
        numrev += numval % numsys;
        numrev *= numsys;
        numval /= numsys;
    }
    numrev += numval % numsys;
    numval /= numsys;
    return numrev;
} /* get_reversed */

template<typename value_t>
[[nodiscard]] inline constexpr
value_t get_min(value_t ln, value_t lr)
{ return std::min(static_cast<v1s_t>(ln), static_cast<v1s_t>(lr)); }
template<typename value_t>
[[nodiscard]] inline constexpr
value_t get_max(value_t ln, value_t lr)
{ return std::max(static_cast<v1s_t>(ln), static_cast<v1s_t>(lr)); }

/* check if a number is inside of l,r boundaries */
template<typename value_t>
[[nodiscard]] inline constexpr
bool_t vet_iside(value_t v, value_t l, value_t, value_t r)
{ return v >= l && v <= r; }
/* check if a number is outside of l,r boundaries */
template<typename value_t>
[[nodiscard]] inline constexpr
bool_t vet_oside(value_t v, value_t l, value_t, value_t r)
{ return v < l || v > r; }

/* binary numeric alignment
 * let's break it down into all ops
 * > (msize_t) is a typecast to operate on pointers and lesser types
 * > > so let's ignore it
 * > a-1 gives us all bits that we need to ignore
 * > > ~(a-1) gives us the number without all those bits
 * > > > &~(a-1) removes all those unnecessary bits
 * > m+a is required for upper alignment
 * > m+a-1, or a-1 in the 1st case
 * > > done to prevent excessful addition for already aligned numbers
*/
template<typename value_t = msize_t, count_t numsys = 2>
[[nodiscard]] constexpr
value_t get_aligned(value_t value, value_t align);
template<>
[[nodiscard]] constexpr
msize_t get_aligned<msize_t, 2>(msize_t value, msize_t align)
{
    return ((value)+((align)-1))&~((align)-1);
}
template<typename mtype_t, typename value_t = msize_t, count_t numsys = 2>
[[nodiscard]] constexpr inline
value_t get_aligned()
{ return get_aligned<value_t, numsys>(sizeof(mtype_t), alignof(mtype_t)); }


} } /* getters */
