#pragma once

#include "./prefix.hxx"

template < typename num_t > inline count_t get_digit_count
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
template < typename num_t > num_t get_digit_l
( num_t numval, index_t digpos, index_t numsys = 10 )
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

#include "./suffix.hxx"