#pragma once

#include "./enum.hxx"
#include "./logic.hxx"

#include "./str.hxx"
#include "./num.hxx"

namespace libasist { namespace cli {

    array_t< const cstr_t > args;

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

    inline dstr_t get_opt
    ( const cstr_t& opt )
    {
        if ( args.size() == 1 || opt.size() < 2 )
        {
            return "";
        }
        const auto head = args.begin() + 1;
        const auto tail = args.end() - 1;
        const auto last = args.end();
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
                            return dstr_t( *( ++iter ) );
                        }
                    }
                    else if ( ( *iter ).find( opt ) != -1 )
                    {
                        return dstr_t( *iter ).substr( offset + 1 );
                    }
                }
            }
            else
            {
                for ( auto iter = head; iter < last; iter++ )
                {
                    if ( *iter == opt )
                    {
                        return dstr_t( *( ++iter ) );
                    }
                }
            }
        }
        return "";
    }
    inline bool_t vet_opt
    ( const cstr_t& opt )
    {
        const auto head = args.begin() + 1;
        const auto last = args.end();
        for ( auto iter = head; iter < last; iter++ )
        {
            if ( ( *iter ).find( opt ) != -1 )
            {
                return TRUTH;
            }
        }
        return FALSE;
    }

    inline dstr_t get_env( const cstr_t& name )
    {
        const char* nstr = &name[0];
        auto estr =  std::getenv( nstr );

        return estr == NULL ? dstr_t() : dstr_t( estr );
    }

    int main( int argc, const char* argv[] )
    {
        args = array_t< const cstr_t >( argv, argv + argc );
        std::clog << std::endl;
        if ( TRUTH )
        {
            std::clog << "(" << "[" << _NAME_STR << "]" << "[args]" << std::endl;
            std::copy( argv, argv + argc, std::ostream_iterator< const char* >( std::clog, "\n" ) );
            std::clog << "[" << _NAME_STR << "]" << "[args]" << ")" << std::endl;
            std::clog << std::endl;
        }
        if ( FALSE )
        {
            v2s_t v2s1 = { 0, 1 };
            v2s_t v2s2 = v2s1 + 1;
            v2s_t v2s3 = v2s1 + v2s2;
            std::clog << v2s1 << v2s2 << v2s3 << std::endl;
            std::clog << std::endl;
        }
        if ( FALSE )
        {
            std::clog << "get -t = " << get_opt( "-t" ) << std::endl;
            std::clog << "get --test = " << get_opt( "--test" ) << std::endl;
            std::clog << "vet --test = " << vet_opt( "--test" ) << std::endl;
            std::clog << "get --arg = " << get_opt( "--arg" ) << std::endl;
            std::clog << "vet --arg = " << vet_opt( "--arg" ) << std::endl;
            std::clog << std::endl;
        }
        if ( FALSE )
        {
            std::clog << "the value is ";
            std::clog << get_nodefault_string(
                    get_opt( "-c" ),
                    get_opt( "--config" ),
                    get_env( "config" ),
                    dstr_t( "not found" )
                    ) << std::endl;
            std::clog << std::endl;
        }
        if ( FALSE )
        {
#       define _ENUM_ACT_PRINT( key, num, str ) \
            std::clog << _TO_STR( key ) << " = " << num << std::endl;
            _ENUM_FOR_ASCII( _ENUM_ACT_PRINT );
#       undef _ENUM_ACT_PRINT
            std::clog << std::endl;
        }
        if ( TRUTH )
        {
            std::clog << "version parsing" << std::endl;
            std::clog << get_ver( _VNUM ) << std::endl;
            std::clog << get_ver( 0xa0a0a0 ) << std::endl;
            std::clog << get_ver( 0xa0a0a1 ) << std::endl;
            std::clog << get_ver( 0xa1a0a1 ) << std::endl;
            std::clog << get_ver( 0xa1a2a1 ) << std::endl;
            std::clog << get_ver( 0xa0a0a10 ) << std::endl;
            std::clog << get_ver( 0xa1a0a10 ) << std::endl;
            std::clog << get_ver( 0xa87a5a10 ) << std::endl;
            std::clog << get_ver( 0xa987a654a321 ) << std::endl;
            std::clog << std::endl;
        }
        return error_none;
    }

} }
