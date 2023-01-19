#pragma once

#include "./enum.hxx"
#include "./const.hxx"
#include "./string.hxx"
#include "./number.hxx"

#include "./prefix.hxx"

struct
{
    std::vector< const std::string_view > args;
} cli;

inline error_enum help
( error_enum error )
{
    if ( error == error_none ) { return error; }

    std::cerr << "[" _NAME_STR "]" << "[help]" << std::endl;
    {
        std::cerr << "- usage" << std::endl;
        {
            std::cerr << "> " << _NAME_STR << " [-o|--option]..." << std::endl;
        }
        std::cerr << "- options" << std::endl;
        {
        }
        std::cerr << "- error" << std::endl;
        {
            std::cerr << "> code=" << static_cast< int >( error ) << std::endl;
            std::cerr << "> text=" << error_text[ error ] << std::endl;
        }
    }
    return error;
}

inline std::string get_opt( const std::string_view& opt )
{
    if ( cli.args.size() == 1 || opt.size() < 2 )
    {
        return "";
    }
    const auto head = cli.args.begin() + 1;
    const auto tail = cli.args.end() - 1;
    const auto last = cli.args.end();
    if ( opt[ 0 ] == '-' )
    {
        if ( opt[ 1 ] == '-' )
        {
            for ( auto iter = head; iter != last; iter++ )
            {
                auto offset = (*iter).find( '=' );
                if ( offset == -1 )
                {
                    if ( *iter == opt )
                    {
                        if ( iter == tail )
                        {
                            help( error_argv );
                            return "";
                        }
                        return std::string( *( ++iter ) );
                    }
                }
                else if ( ( *iter ).find( opt ) != -1 )
                {
                    return std::string( *iter ).substr( offset + 1 );
                }
            }
        }
        else
        {
            for ( auto iter = head; iter < last; iter++ )
            {
                if ( *iter == opt )
                {
                    return std::string( *( ++iter ) );
                }
            }
        }
    }
    return "";
}
inline bool vet_opt( const std::string_view& opt )
{
    const auto head = cli.args.begin() + 1;
    const auto last = cli.args.end();
    for ( auto iter = head; iter < last; iter++ )
    {
        if ( ( *iter ).find( opt ) != -1 )
        {
            return TRUTH;
        }
    }
    return FALSE;
}

inline std::string get_env( const std::string_view& name )
{
    const char* nstr = &name[0];
    auto estr =  std::getenv( nstr );

    return estr == NULL ? std::string() : std::string( estr );
}

#include "./suffix.hxx"
