#ifndef LIBASIST_TERM_MAIN_HXX
#define LIBASIST_TERM_MAIN_HXX

#include "../head.hxx"
#include "../data/dpack.hxx"

namespace libasist { namespace term {

// datadef

extern data::dpack_t<svstr_t> args;

// vetters

bool_t vet_opt(const svstr_t& opt);

// actions

int main(count_t argc, scstr_t argv[]);

error_enum help(error_enum error);

} } // namespace libasist { namespace term {

#endif//LIBASIST_TERM_MAIN_HXX
