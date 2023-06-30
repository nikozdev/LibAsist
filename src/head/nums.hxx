#pragma once

/* headers */

#include "conf.hxx"
#include "osys.hxx"
#include "tool.hxx"
#include "defn.hxx"
#include "type.hxx"
#include "meta.hxx"

/** standard **/

#include <cmath>
#include <numeric>
#include <cstdint>

/* content */

namespace libasist { /* consdef */

    constexpr auto ZERO = 0;
    constexpr auto UNIT = 1;

} /* consdef */

namespace libasist { /* typedef */

    using v1u08_t = uint8_t;
    using v1u16_t = uint16_t;
    using v1u32_t = uint32_t;
    using v1u64_t = uint64_t;
    using v1u_t = unsigned;
    /*
    using v2u_t = v2v_t<v1u_t>;
    using v3u_t = v3v_t<v1u_t>;
    */

    using v1s08_t = int8_t;
    using v1s16_t = int16_t;
    using v1s32_t = int32_t;
    using v1s64_t = int64_t;
    using v1s_t = signed;
    /*
    using v2s_t = v2v_t<v1s_t>;
    using v3s_t = v3v_t<v1s_t>;
    */

    using v1f32_t = float;
    using v1f64_t = float;
    using v1f_t = float;
    /*
    using v2f_t = v2v_t<v1f_t>;
    using v3f_t = v3v_t<v1f_t>;
    */

    using index_t = v1s64_t;
    using count_t = v1u64_t;

} /* typedef */

namespace libasist { /* getters */

    template <typename t_num_t>
    [[nodiscard]] constexpr inline
    auto get_num_sign(t_num_t n)
    { return n < 0 ? -1 : +1; }

    template < typename num_t > count_t get_digit_count
    ( num_t numval, count_t numsys )
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
    template<typename t_num_t>
    t_num_t get_digit_froml
    (t_num_t numval, index_t digpos, index_t numsys = 10 )
    {
        return numval % std::pow( numsys, digpos + 1 ) / std::pow( numsys, digpos - 1 );
    }
    template < typename num_t > num_t get_digit_r
    ( num_t numval, index_t digpos, index_t numsys = 10 )
    {
        return numval / std::pow( numsys, digpos - 1 ) % numsys;
    }

    template < typename num_t > num_t get_reversed
    ( num_t numval, count_t numsys = 10 )
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

} /* getters */
