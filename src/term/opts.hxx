#ifndef LIBASIST_TERM_OPTS_HXX
#define LIBASIST_TERM_OPTS_HXX 1

#include "../head.hxx"

/* headers */

/* content */

namespace libasist { namespace term { /* datadef */

} } /* datadef */

namespace libasist { namespace term { /* getters */

sdstr_t get_opt(const svstr_t&name);

} } /* getters */

namespace libasist { namespace term { /* vetters */

bool_t vet_opt(const svstr_t&name);

} } /* vetters */

namespace libasist { namespace term { /* actions */
} } /* actions */

#endif/*LIBASIST_TERM_OPTS_HXX*/
