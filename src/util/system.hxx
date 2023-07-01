#pragma once

/* headers */

#include "../head.hxx"

#include "single.hxx"

/* content */

namespace libasist { namespace util { /* typedef */

/* template system type */
template<class t_type_t>
class system_t : public single_t<t_type_t>
{
public: /* typedef */
	using type_t = t_type_t;
    using this_t = system_t<type_t>;
public: /* actions */
	inline v1bit_t init() { return TRUTH; }
	inline v1bit_t quit() { return TRUTH; }
	inline v1bit_t work() { return TRUTH; }
}; /* t_system_t */

} } /* typedef */
