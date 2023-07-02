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

} } /* actions */

#endif/*LIBASIST_TERM_HELP_CXX*/
