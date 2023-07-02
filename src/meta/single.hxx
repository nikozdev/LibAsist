#ifndef LIBASIST_META_SINGLE_HXX
#define LIBASIST_META_SINGLE_HXX 1

#include "../head.hxx"

/* headers */

/* content */

namespace libasist { namespace meta { /* typedef */

/* template singleton type */
template<typename instance_t>
class single_t
{
public: /* typedef */
    using this_t = single_t<instance_t>;
protected:
    inline single_t() = default;
public: /* codetor */
    inline single_t(const this_t& copy) = delete;
    inline single_t(this_t&& copy) = delete;
public: /* getters */
    static inline instance_t& get()
    { static instance_t single; return single; }
public: /* symbols */
    instance_t&operator=(const instance_t& copy) = delete;
    instance_t&operator=(instance_t&& copy) = delete;
    this_t&operator=(const this_t& copy) = delete;
    this_t&operator=(this_t&& copy) = delete;
}; /* single_t */

} } /* typedef */

#endif/*LIBASIST_META_SINGLE_HXX*/
