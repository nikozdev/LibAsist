#pragma once

#include "./stdlib.hxx"

#include "./enum.hxx"

#include "./string.hxx"

#include "./number.hxx"
#include "./vector.hxx"

#include "./array.hxx"
#include "./list2.hxx"
#include "./table.hxx"

#include "./version.hxx"

#include "./cli.hxx"

#include "./prefix.hxx"

int main( int argc, const char* argv[] )
{
    cli.args = std::vector< const std::string_view >( argv, argv + argc );
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
            std::string( "not found" )
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
        std::clog << get_version( _VNUM ) << std::endl;
        std::clog << get_version( 0xa0a0a0 ) << std::endl;
        std::clog << get_version( 0xa0a0a1 ) << std::endl;
        std::clog << get_version( 0xa1a0a1 ) << std::endl;
        std::clog << get_version( 0xa1a2a1 ) << std::endl;
        std::clog << get_version( 0xa0a0a10 ) << std::endl;
        std::clog << get_version( 0xa1a0a10 ) << std::endl;
        std::clog << get_version( 0xa87a5a10 ) << std::endl;
        std::clog << get_version( 0xa987a654a321 ) << std::endl;
        std::clog << std::endl;
    }
    return error_none;
}

#include "./suffix.hxx"
