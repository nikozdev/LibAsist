#pragma once

#define _TO_STR( text ) ( #text )

#include <string>
#include <string_view>
#include <sstream>

namespace libasist
{
    using char_t = char;

    using cstr_t = std::string_view;
    using dstr_t = std::string;

    template< typename type_t > const type_t& get_nodefault
    ( const type_t& def, const type_t& arg )
    {
        return arg;
    }
    template< typename type_t, typename ... args_t > const type_t& get_nodefault
    ( const type_t& def, const type_t& arg, args_t&& ... args )
    {
        return arg == def ? get_nodefault( def, std::forward< args_t >( args )... ) : arg;
    }
    template< typename ... args_t > const dstr_t& get_nodefault_string
    ( args_t&& ... args )
    {
        dstr_t def;
        return get_nodefault( def, std::forward< args_t >( args )... );
    }
}
