#include "head.hxx"

/* headers */

#include "term.hxx"
#include "meta.hxx"
#include "nums.hxx"

/* content */

namespace libasist { namespace term { /* datadef */

darray_t_t<svstr_t> args;

} }

namespace libasist { namespace term { /* getters */

sdstr_t get_opt(const svstr_t&name)
{
    if (args.size() == 1 || name.size() < 2)
    { return ""; }
    const auto head = args.begin() + 1;
    const auto tail = args.end() - 1;
    const auto last = args.end();
    if (name[0] == '-')
    {
        if (name[1] == '-')
        {
            for (auto iter = head; iter != last; iter++)
            {
                auto offset = (*iter).find('=');
                if (offset == -1)
                {
                    if (*iter == name)
                    {
                        if (iter == tail)
                        {
                            help( error_argv );
                            return "";
                        }
                        return sdstr_t(*(++iter));
                    }
                }
                else if ((*iter).find(name) != -1)
                {
                    return sdstr_t(*iter).substr(offset + 1);
                }
            }
        }
        else
        {
            for (auto iter = head; iter < last; iter++)
            {
                if (*iter == name) { return sdstr_t(*( ++iter )); }
            }
        }
    }
    return "";
}

sdstr_t get_env(const svstr_t&name)
{
    auto estr = std::getenv(&name[0]);

    return estr == NULL ? sdstr_t() : sdstr_t(estr);
}

} } /* getters */

namespace libasist { namespace term { /* vetters */

bool_t vet_opt(const svstr_t&name)
{
    const auto head = args.begin() + 1;
    const auto last = args.end();
    for (auto iter = head; iter < last; iter++)
    {
        if ((*iter).find(name) != -1)
        { return TRUTH; }
    }
    return FALSE;
}

} } /* vetters */

namespace libasist { namespace term { /* setters */
} } /* setters */

namespace libasist { namespace term { /* actions */

error_enum help(error_enum error)
{
    if ( error == error_none ) { return error; }
    std::cerr << "[" LIBASIST_NAME_STR "]" << "[help]" << text::endl;
    {
        std::cerr << "- usage" << text::endl;
        {
            std::cerr << "> " << LIBASIST_NAME_STR << " [-o|--option]..." << text::endl;
        }
        std::cerr << "- options" << text::endl;
        {
        }
        std::cerr << "- error" << text::endl;
        {
            std::cerr << "> code=" << static_cast< int >( error ) << text::endl;
            std::cerr << "> text=" << error_text[ error ] << text::endl;
        }
    }
    return error;
}

int main(count_t argc, scstr_t argv[])
{
    args = darray_t_t<svstr_t>(argv, argv + argc);
    std::clog << text::endl;
    if constexpr (TRUTH)
    {
        std::clog << "(" << "[" << LIBASIST_NAME_STR << "]" << "[args]" << text::endl;
        std::copy(argv, argv + argc, std::ostream_iterator<scstr_t>(std::clog, text::endl));
        std::clog << "[" << LIBASIST_NAME_STR << "]" << "[args]" << ")" << text::endl;
        std::clog << text::endl;
    }
    if constexpr (TRUTH)
    {
        nums::v2s_t v2s1 = { 0, 1 };
        nums::v2s_t v2s2 = v2s1 + 1;
        nums::v2s_t v2s3 = v2s1 + v2s2;
        std::clog << v2s1 << v2s2 << v2s3 << text::endl;
        std::clog << text::endl;
    }
    if constexpr (TRUTH)
    {
        std::clog << "get -t = " << get_opt( "-t" ) << text::endl;
        std::clog << "get --test = " << get_opt( "--test" ) << text::endl;
        std::clog << "vet --test = " << vet_opt( "--test" ) << text::endl;
        std::clog << "get --arg = " << get_opt( "--arg" ) << text::endl;
        std::clog << "vet --arg = " << vet_opt( "--arg" ) << text::endl;
        std::clog << text::endl;
    }
    if constexpr (TRUTH)
    {
        std::clog << "the value is ";
        std::clog << get_nodefault<sdstr_t>(
            get_opt("-c"),
            get_opt("--config"),
            get_env("config"),
            sdstr_t("not found")
        ) << text::endl;
        std::clog << text::endl;
    }
    if constexpr (FALSE)
    {
#       define _ENUM_ACT_PRINT(key, num, str) \
        std::clog << _GET_STR(key) << " = " << num << text::endl;
        _ENUM_FOR_ASCII(_ENUM_ACT_PRINT);
#       undef _ENUM_ACT_PRINT
        std::clog << text::endl;
    }
    if constexpr (TRUTH)
    {
        std::clog << "version parsing" << text::ENDL_CHAR;
        std::clog << meta::get_vnum( LIBASIST_VNUM ) << text::endl;
        std::clog << meta::get_vnum( 0xa0a0a0 ) << text::endl;
        std::clog << meta::get_vnum( 0xa0a0a1 ) << text::endl;
        std::clog << meta::get_vnum( 0xa1a0a1 ) << text::endl;
        std::clog << meta::get_vnum( 0xa1a2a1 ) << text::endl;
        std::clog << meta::get_vnum( 0xa0a0a10 ) << text::endl;
        std::clog << meta::get_vnum( 0xa1a0a10 ) << text::endl;
        std::clog << meta::get_vnum( 0xa87a5a10 ) << text::endl;
        std::clog << meta::get_vnum( 0xa987a654a321 ) << text::endl;
        std::clog << text::endl;
    }
    if constexpr (TRUTH)
    {
        auto inlist = inlist_t_t<int>{ -1, 1, 12345, 'a' };
        std::copy(
            inlist.begin(), inlist.end(),
            std::ostream_iterator<int>(std::clog, text::endl)
        );
    }
    return error_none;
}

} } /* actions */
