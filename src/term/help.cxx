#ifndef LIBASIST_TERM_HELP_CXX
#define LIBASIST_TERM_HELP_CXX 1

#include "../head.hxx"

/* headers */

#include "args.hxx"
#include "opts.hxx"
#include "envi.hxx"

/* content */

namespace libasist { namespace term { /* actions */

error_enum help(error_enum error)
{
    if ( error == error_none ) { return error; }
    std::cerr << "[" LIBASIST_NAME_STR "]" << "[help]" << text::ENDL_CHAR;
    {
        std::cerr << "- usage" << text::ENDL_CHAR;
        {
            std::cerr << "> " << LIBASIST_NAME_STR << " [-o|--option]..." << text::ENDL_CHAR;
        }
        std::cerr << "- options" << text::ENDL_CHAR;
        {
        }
        std::cerr << "- error" << text::ENDL_CHAR;
        {
            std::cerr << "> code=" << static_cast< int >( error ) << text::ENDL_CHAR;
            std::cerr << "> text=" << error_text[ error ] << text::ENDL_CHAR;
        }
    }
    return error;
}

} } /* actions */

#endif/*LIBASIST_TERM_HELP_CXX*/
