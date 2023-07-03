#ifndef LIBASIST_TERM_MAIN_CXX
#define LIBASIST_TERM_MAIN_CXX

#include "../head.hxx"
#include "../term/args.hxx"
#include "../term/opts.hxx"
#include "../term/envi.hxx"
#include "../term/help.hxx"

#include "../main.hxx"

namespace libasist { namespace term {

// actions

int main(count_t argc, scstr_t argv[])
{
    args = data::dpack_t<svstr_t>(argv, argv + argc);
    std::clog << text::ENDL_CHAR;
    if constexpr (TRUTH)
    {
        std::clog << "(" << "[" << LIBASIST_NAME_STR << "]" << "[args]" << text::ENDL_CHAR;
        std::copy(
            argv, argv + argc,
            std::ostream_iterator<scstr_t>(std::clog, text::ENDL_CSTR)
        );
        std::clog << "[" << LIBASIST_NAME_STR << "]" << "[args]" << ")" << text::ENDL_CHAR;
        std::clog << text::ENDL_CHAR;
    } /* title */
    if constexpr (FALSE)
    {
        nums::v2s_t v2s1 = { 0, 1 };
        nums::v2s_t v2s2 = v2s1 + 1;
        nums::v2s_t v2s3 = v2s1 + v2s2;
        std::clog << v2s1 << v2s2 << v2s3 << text::ENDL_CHAR;
        std::clog << text::ENDL_CHAR;
    } /* numeric vectors test */
    if constexpr (FALSE)
    {
        std::clog << "get -t = " << get_opt( "-t" ) << text::ENDL_CHAR;
        std::clog << "get --test = " << get_opt( "--test" ) << text::ENDL_CHAR;
        std::clog << "vet --test = " << vet_opt( "--test" ) << text::ENDL_CHAR;
        std::clog << "get --arg = " << get_opt( "--arg" ) << text::ENDL_CHAR;
        std::clog << "vet --arg = " << vet_opt( "--arg" ) << text::ENDL_CHAR;
        std::clog << text::ENDL_CHAR;
    } /* command line options test */
    if constexpr (FALSE)
    {
        std::clog << "the value is ";
        std::clog << get_nodefault<sdstr_t>(
            get_opt("-c"),
            get_opt("--config"),
            get_env("config"),
            "not found"_sdstr
        ) << text::ENDL_CHAR;
        std::clog << text::ENDL_CHAR;
    } /* command line arguments and environment test */
    if constexpr (FALSE)
    {
#       define _ENUM_ACT_PRINT(key, num, str) \
        std::clog << _GET_STR(key) << " = " << num << text::ENDL_CHAR;
        _ENUM_FOR_ASCII(_ENUM_ACT_PRINT);
#       undef _ENUM_ACT_PRINT
        std::clog << text::ENDL_CHAR;
    } /* enum macro test */
    if constexpr (TRUTH)
    {
        _OLOG("version parsing");
        _OLOG("{}", meta::vnum_t( LIBASIST_VNUM ));
        _OLOG("{}", meta::vnum_t( 0xa0a0a0 ));
        _OLOG("{}", meta::vnum_t( 0xa0a0a1 ));
        _OLOG("{}", meta::vnum_t( 0xa1a0a1 ));
        _OLOG("{}", meta::vnum_t( 0xa1a2a1 ));
        _OLOG("{}", meta::vnum_t( 0xa0a0a10 ));
        _OLOG("{}", meta::vnum_t( 0xa1a0a10 ));
        _OLOG("{}", meta::vnum_t( 0xa87a5a10 ));
        _OLOG("{}", meta::vnum_t( 0xa987a654a321 ));
        _OLOG("{}", meta::vnum_t( 1, 1, 1 ));
        _OLOG("{}", meta::vnum_t( 987, 654, 321 ));
    } /* vnum test */
    if constexpr (FALSE)
    {
        auto inlist = ilist_t<int>{ -1, 1, 12345, 'a' };
        std::copy(
            inlist.begin(), inlist.end(),
            std::ostream_iterator<int>(std::clog, text::ENDL_CSTR)
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
        std::clog << text::ENDL_CHAR;
        for (msize_t ic = 0; ic < SSIZE; ic++)
        {
            for (msize_t iv = 0; iv < RANGE; iv++)
            {
                buffer[ic] = FIRST + iv;
                auto hash = shstr_t(buffer);
                auto lkey = hash.hash%TSIZE;
                if (lookup[lkey] == TRUTH)
                {
                    _OLOG("[{:d}]=({:d},{:s})",
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
        std::clog << text::ENDL_CHAR;
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

} } // namespace libasist { namespace term {

#ifdef _TYPE_EXE
#   undef _TYPE_EXE
int main(int argc, const char**argv)
{
    return libasist::term::main(argc, argv);
}
#endif

#endif//LIBASIST_TERM_MAIN_CXX
