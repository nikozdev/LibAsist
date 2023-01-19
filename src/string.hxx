#pragma once

#define _TO_STR( text ) ( #text )
#include <string>
#include <string_view>
#include <sstream>

#include "./prefix.hxx"

template< typename type_t > inline
const type_t& get_nodefault
( const type_t& def, const type_t& arg )
{
    return arg;
}
template< typename type_t, typename ... args_t > inline
const type_t& get_nodefault
( const type_t& def, const type_t& arg, args_t&& ... args )
{
    return arg == def ? get_nodefault( def, std::forward< args_t >( args )... ) : arg;
}
template< typename ... args_t > inline
const std::string& get_nodefault_string
( args_t&& ... args )
{
    std::string def;
    return get_nodefault( def, std::forward< args_t >( args )... );
}

#include "./suffix.hxx"
