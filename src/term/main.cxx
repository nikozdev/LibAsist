#ifndef LIBASIST_TERM_MAIN_CXX
#define LIBASIST_TERM_MAIN_CXX 1

#include "../head.hxx"

/* headers */

#include "args.hxx"
#include "opts.hxx"
#include "envi.hxx"
#include "help.hxx"

#include "../main.hxx"

/* content */

namespace libasist { namespace term { /* actions */

int main(count_t argc, scstr_t argv[])
{
    args = darray_t<svstr_t>(argv, argv + argc);
    std::clog << text::endl;
    if constexpr (TRUTH)
    {
        std::clog << "(" << "[" << LIBASIST_NAME_STR << "]" << "[args]" << text::endl;
        std::copy(argv, argv + argc, std::ostream_iterator<scstr_t>(std::clog, text::endl));
        std::clog << "[" << LIBASIST_NAME_STR << "]" << "[args]" << ")" << text::endl;
        std::clog << text::endl;
    } /* title */
    if constexpr (FALSE)
    {
        nums::v2s_t v2s1 = { 0, 1 };
        nums::v2s_t v2s2 = v2s1 + 1;
        nums::v2s_t v2s3 = v2s1 + v2s2;
        std::clog << v2s1 << v2s2 << v2s3 << text::endl;
        std::clog << text::endl;
    } /* numeric vectors test */
    if constexpr (FALSE)
    {
        std::clog << "get -t = " << get_opt( "-t" ) << text::endl;
        std::clog << "get --test = " << get_opt( "--test" ) << text::endl;
        std::clog << "vet --test = " << vet_opt( "--test" ) << text::endl;
        std::clog << "get --arg = " << get_opt( "--arg" ) << text::endl;
        std::clog << "vet --arg = " << vet_opt( "--arg" ) << text::endl;
        std::clog << text::endl;
    } /* command line options test */
    if constexpr (FALSE)
    {
        std::clog << "the value is ";
        std::clog << get_nodefault<sdstr_t>(
            get_opt("-c"),
            get_opt("--config"),
            get_env("config"),
            "not found"_sdstr
        ) << text::endl;
        std::clog << text::endl;
    } /* command line arguments and environment test */
    if constexpr (FALSE)
    {
#       define _ENUM_ACT_PRINT(key, num, str) \
        std::clog << _GET_STR(key) << " = " << num << text::endl;
        _ENUM_FOR_ASCII(_ENUM_ACT_PRINT);
#       undef _ENUM_ACT_PRINT
        std::clog << text::endl;
    } /* enum macro test */
    if constexpr (TRUTH)
    {
        std::clog << "version parsing" << text::ENDL_CHAR;
        std::clog << meta::vnum_t( LIBASIST_VNUM ) << text::endl;
        std::clog << meta::vnum_t( 0xa0a0a0 ) << text::endl;
        std::clog << meta::vnum_t( 0xa0a0a1 ) << text::endl;
        std::clog << meta::vnum_t( 0xa1a0a1 ) << text::endl;
        std::clog << meta::vnum_t( 0xa1a2a1 ) << text::endl;
        std::clog << meta::vnum_t( 0xa0a0a10 ) << text::endl;
        std::clog << meta::vnum_t( 0xa1a0a10 ) << text::endl;
        std::clog << meta::vnum_t( 0xa87a5a10 ) << text::endl;
        std::clog << meta::vnum_t( 0xa987a654a321 ) << text::endl;
        std::clog << meta::vnum_t( 1, 1, 1 ) << text::endl;
        std::clog << meta::vnum_t( 987, 654, 321 ) << text::endl;
        std::clog << text::endl;
    } /* vnum test */
    if constexpr (FALSE)
    {
        auto inlist = inlist_t<int>{ -1, 1, 12345, 'a' };
        std::copy(
            inlist.begin(), inlist.end(),
            std::ostream_iterator<int>(std::clog, text::endl)
        );
    } /* inlist test */
    if constexpr (TRUTH)
    {
        constexpr v1u_t FIRST = 0x20;
        constexpr v1u_t RANGE = 0x5f;
        constexpr v1u_t SSIZE = 0x02;
        constexpr v1u_t TSIZE = SSIZE*SSIZE*RANGE*16;
        schar_t buffer[SSIZE];
        std::memset(buffer, text::ENDS_CHAR, sizeof(buffer));
        bool_t lookup[TSIZE];
        std::memset(lookup, FALSE, sizeof(lookup));
        for (auto iter = 0; iter < TSIZE; iter++) { lookup[iter] = FALSE; }
        std::clog << text::endl;
        for (msize_t ic = 0; ic < SSIZE; ic++)
        {
            for (msize_t iv = 0; iv < RANGE; iv++)
            {
                buffer[ic] = FIRST + iv;
                auto hash = shstr_t(buffer);
                auto lkey = hash.hash%TSIZE;
                if (lookup[lkey] == TRUTH)
                {
                    _OLOG("[%u]=(%u,%s)",
                        lkey,
                        hash.hash,
                        hash.orig
                    );
                }
                else
                {
                    lookup[lkey] = TRUTH;
                }
            }
        }
        std::clog << text::endl;
    } /* hash test */
    if constexpr (TRUTH)
    {
        memo::init();
        using pager_t = memo::refer_t<
        memo::pager_t,
        &memo::giver_t::give_static<memo::heapy_t>,
        &memo::taker_t::take_static<memo::heapy_t>,
        count_t
        >;
        {
            pager_t pager0{memo::pager_t::MSIZE, memo::heapy_t::get()};
            {
                pager_t pager1{pager0};
                pager_t pager2{pager0};
            }
            {
                pager_t pager1{pager0};
                pager_t pager2{pager1};
            }
        }
        memo::quit();
    } /* memory test */
    if constexpr (TRUTH)
    {
        class system_t { };
        exec::system_t<system_t>system;
        class engine_t { };
        exec::engine_t<engine_t>engine;
    } /* singleton test */
    return error_none;
}

} } /* actions */

#ifdef _TYPE_EXE
#   undef _TYPE_EXE
int main(int argc, const char**argv)
{
    return libasist::term::main(argc, argv);
}
#endif

#endif/*LIBASIST_TERM_MAIN_CXX*/
