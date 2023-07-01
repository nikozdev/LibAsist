#pragma once

#include "../head.hxx"

/* headers */

/* content */

namespace libasist { namespace term { /* datadef */

extern darray_t<svstr_t> args;

} } /* datadef */

namespace libasist { namespace term { /* vetters */

bool_t vet_opt(const svstr_t& opt);

} } /* vetters */

namespace libasist { namespace term { /* actions */

int main(count_t argc, scstr_t argv[]);

error_enum help(error_enum error);

} } /* actions */
