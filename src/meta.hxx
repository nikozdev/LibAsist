#pragma once

/* headers */

#include "head.hxx"

/* content */

namespace libasist { namespace meta { /* typedef */

typedef struct vnum_t
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
} vnum_t;

} } /* typedef */

namespace libasist { namespace meta { /* operats */

template<typename stream_t = mdata_reader_t>
stream_t&operator<<(stream_t&stream, const vnum_t&vnum)
{
    auto flags = stream.flags();
    stream << "[major]=" << vnum.major << ";";
    stream << "[minor]=" << vnum.minor << ";";
    stream << "[micro]=" << vnum.micro << ";";
    stream << std::hex;
    stream << "[whole]=" << vnum.whole << ";";
    stream.flags( flags );
    return stream;
}

} } /* symbols */

namespace libasist { namespace meta { /* getters */

vnum_t get_vnum( index_t whole = LIBASIST_VNUM );

} } /* actions */
