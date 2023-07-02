#ifndef LIBASIST_META_VNUM_CXX
#define LIBASIST_META_VNUM_CXX 1

#include "../head.hxx"

/* headers */

#include "vnum.hxx"

/* content */

namespace libasist { namespace meta { /* typedef */

/* codetor */

vnum_t::vnum_t(value_t whole) : vdata {
    .micro = get_micro(whole),
    .minor = get_minor(whole),
    .major = get_major(whole),
    .whole = whole,
} { }

vnum_t::vnum_t(value_t major, value_t minor, value_t micro) : vdata {
    .micro = micro,
    .minor = minor,
    .major = major,
    .whole = get_whole(major, minor, micro),
} { }

/* getters */

vnum_t::value_t vnum_t::get_major(vnum_t::value_t whole)
{
    return get_vdata(whole).major;
}
vnum_t::value_t vnum_t::get_minor(vnum_t::value_t whole)
{
    return get_vdata(whole).minor;
}
vnum_t::value_t vnum_t::get_micro(vnum_t::value_t whole)
{
    return get_vdata(whole).micro;
}

vnum_t::value_t
vnum_t::get_whole(value_t major, value_t minor, value_t micro)
{
    value_t whole = 0;
    value_t part_list[3] = {
        nums::get_reversed(major),
        nums::get_reversed(minor),
        nums::get_reversed(micro),
    };
    value_t part = 0;
    for (index_t part_iter = 0; part_iter < 3; part_iter++)
    { /* micro */
        part = part_list[part_iter];
        whole *= 16;
        whole += 0xa;
        while ( part )
        {
            whole *= 16;
            whole += (part % 10);
            part /= 10;
        }
    } /* micro */
    return whole;
}

vnum_t::vdata_t
vnum_t::get_vdata(value_t major, value_t minor, value_t micro)
{
    return vdata_t {
        .micro = micro,
        .minor = minor,
        .major = major,
        .whole = get_whole(major, minor, micro),
    };
}
vnum_t::vdata_t vnum_t::get_vdata(value_t whole)
{
    value_t step = 1; /* the digit offset */
    value_t part_iter = 0;
    value_t part_list[3] = { 0, 0, 0 };
    value_t part = 0;
    value_t temp = whole;
    while ( temp && part_iter < 4 )
    {
        auto digit = temp % 16;
        if (digit == 10)
        {
            part_list[part_iter++] = part;
            part = 0;
            step = 1;
        }
        else
        {
            part += step * digit;
            step *= 10;
        }
        temp /= 16;
    }
    return vdata_t {
        .micro = part_list[0],
        .minor = part_list[1],
        .major = part_list[2],
        .whole = whole,
    };
}

} } /* typedef */

#endif/*LIBASIST_META_VNUM_CXX*/
