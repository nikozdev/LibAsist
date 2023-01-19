#pragma once

#include "./enum.hxx"
#include "./string.hxx"
#include "./number.hxx"

#include "./prefix.hxx"

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

template< typename stream_t = std::ostream > stream_t& operator<<
( stream_t& stream, const version_t& version )
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

inline version_t get_version
( index_t whole = _VNUM )
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

#include "./suffix.hxx"
