#ifndef LIBASIST_META_VNUM_HXX
#define LIBASIST_META_VNUM_HXX 1

#include "../head.hxx"

/* headers */

/* content */

namespace libasist { namespace meta { /* typedef */

/* version number type */
typedef class vnum_t
{
public: /* typedef */
    using this_t = vnum_t;
    using value_t = v1u64_t;
    typedef struct vdata_t {
        union
        {
            const value_t parts[3];
            struct
            {
                const value_t micro;
                const value_t minor;
                const value_t major;
            };
        };
        const value_t whole;
    } vdata_t;
public: /* codetor */
    vnum_t(value_t major, value_t minor, value_t micro);
    vnum_t(value_t whole);
public: /* getters */
    inline value_t get_major() const { return this->vdata.major; }
    inline value_t get_minor() const { return this->vdata.minor; }
    inline value_t get_micro() const { return this->vdata.micro; }
    inline value_t get_whole() const { return this->vdata.whole; }
    static value_t get_major(value_t whole);
    static value_t get_minor(value_t whole);
    static value_t get_micro(value_t whole);
    static value_t get_whole(value_t major, value_t minor, value_t micro);
    static vdata_t get_vdata(value_t major, value_t minor, value_t micro);
    static vdata_t get_vdata(value_t whole);
public: /* operats */
    template<typename stream_t = mdata_reader_t>
    stream_t&operator<<(stream_t&stream) const
    {
        auto flags = stream.flags();
        stream << std::dec;
        stream << "[major]=" << this->get_major();
        stream << "[minor]=" << this->get_minor();
        stream << "[micro]=" << this->get_micro();
        stream << std::hex;
        stream << "[whole]=" << this->get_whole();
        stream.flags(flags);
        return stream;
    }
    template<typename stream_t = mdata_reader_t>
    stream_t&operator>>(stream_t&stream) const
    {
        auto flags = stream.flags();
        stream.flags(flags);
        return stream;
    }
private: /* datadef */
    const vdata_t vdata;
} vnum_t;

} } /* typedef */

namespace libasist { namespace meta { /* operats */

template<typename stream_t = mdata_reader_t>
stream_t&operator<<(stream_t&stream, const vnum_t&vnum)
{ return vnum.operator<<(stream); }
template<typename stream_t = mdata_reader_t>
stream_t&operator>>(stream_t&stream, const vnum_t&vnum)
{ return vnum.operator>>(stream); }

} } /* symbols */

namespace libasist { namespace meta { /* getters */

} } /* actions */

#endif/*LIBASIST_META_VNUM_HXX*/
