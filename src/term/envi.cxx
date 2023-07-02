#ifndef LIBASIST_TERM_ENVI_CXX
#define LIBASIST_TERM_ENVI_CXX 1

#include "../head.hxx"

/* headers */

#include "args.hxx"
#include "help.hxx"

/* content */

namespace libasist { namespace term { /* datadef */
} }

namespace libasist { namespace term { /* getters */

sdstr_t get_env(const svstr_t&name)
{
    auto estr = std::getenv(&name[0]);

    return estr == NULL ? sdstr_t() : sdstr_t(estr);
}

} } /* getters */

namespace libasist { namespace term { /* vetters */

v1bit_t vet_env(const svstr_t&name)
{
    auto estr = std::getenv(&name[0]);

    return estr != NULL;
}

} } /* vetters */

namespace libasist { namespace term { /* setters */
} } /* setters */

namespace libasist { namespace term { /* actions */
} } /* actions */

#endif/*LIBASIST_TERM_ENVI_CXX*/
