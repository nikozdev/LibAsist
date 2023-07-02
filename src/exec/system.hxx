#ifndef LIBASIST_EXEC_SYSTEM_HXX
#define LIBASIST_EXEC_SYSTEM_HXX 1

#include "../head.hxx"

/* headers */

#include "../meta/single.hxx"

/* content */

namespace libasist { namespace exec { /* typedef */

/* template system type */
template<class instance_t>
class system_t : public meta::single_t<instance_t>
{
public: /* typedef */
    using this_t = system_t<instance_t>;
public: /* actions */
    inline virtual
    v1bit_t init() { return TRUTH; }
    inline virtual
    v1bit_t quit() { return TRUTH; }
    inline virtual
    v1bit_t work() { return TRUTH; }
}; /* t_system_t */

} } /* typedef */

#endif/*LIBASIST_EXEC_SYSTEM_HXX*/
