#pragma once

/* headers */

#include "../head.hxx"

/* content */

namespace libasist { namespace util { /* typedef */

/* template singleton type */
template<typename t_type_t>
class single_t
{
    static_assert(
        !std::is_copy_constructible<t_type_t>::value,
        "singleton cannot be constructed by a copy"
    );
    static_assert(
        !std::is_final<t_type_t>::value,
        "singleton must be the final in it's own class"
    );
public: /* typedef */
    using type_t = t_type_t;
    using this_t = single_t<type_t>;
public: /* codetor */
    inline single_t(const type_t& copy) = delete;
    inline single_t(type_t&& copy) = delete;
    inline single_t(const this_t& copy) = delete;
    inline single_t(this_t&& copy) = delete;
public: /* getters */
    static inline type_t& get()
    { static type_t single; return single; }
public: /* symbols */
    type_t&operator=(const type_t& copy) = delete;
    type_t&operator=(type_t&& copy) = delete;
    this_t&operator=(const this_t& copy) = delete;
    this_t&operator=(this_t&& copy) = delete;
}; /* single_t */

} } /* typedef */
