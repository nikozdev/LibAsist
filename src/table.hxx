#pragma once

#include <unordered_map>

#include "prefix.hxx"

template< typename value_t >
using table_t = unordered_map< value_t >;

#include "suffix.hxx"
