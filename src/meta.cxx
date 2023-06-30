#include "head.hxx"

/* headers */

#include "meta.hxx"

/* content */

namespace libasist { namespace meta { /* getters */

vnum_t get_vnum(index_t whole)
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
        .major = part_list[2],
        .minor = part_list[1],
        .micro = part_list[0],
        .whole = whole
    };
} /* get_vnum */

} } /* getters */
