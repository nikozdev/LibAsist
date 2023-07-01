#pragma once

#include "../head.hxx"

/* headers */

/* content */

namespace libasist { namespace term { /* datadef */

} } /* datadef */

namespace libasist { namespace term { /* getters */

sdstr_t get_env(const svstr_t&name);

} } /* getters */

namespace libasist { namespace term { /* vetters */

bool_t vet_env(const svstr_t&name);

} } /* vetters */

namespace libasist { namespace term { /* actions */

int main(count_t argc, scstr_t argv[]);

error_enum help(error_enum error);

} } /* actions */
