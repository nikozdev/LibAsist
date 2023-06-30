#pragma once

/* headers */

#include "head.hxx"

/* content */

namespace libasist { namespace term { /* datadef */

extern darray_t_t<svstr_t> args;

} } /* datadef */

namespace libasist { namespace term { /* getters */

sdstr_t get_opt(const svstr_t&name);

sdstr_t get_env(const svstr_t&name);

} } /* getters */

namespace libasist { namespace term { /* vetters */

bool_t vet_opt(const svstr_t& opt);

} } /* vetters */

namespace libasist { namespace term { /* actions */

error_enum help(error_enum error);

int main(count_t argc, scstr_t argv[]);

} } /* actions */
