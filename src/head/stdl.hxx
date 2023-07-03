#ifndef LIBASIST_HEAD_STDL_HXX
#define LIBASIST_HEAD_STDL_HXX

#include "conf.hxx"
#include "osys.hxx"
#include "tool.hxx"
#include "defn.hxx"

// standard

#include <cstdlib>
#include <cstddef>

#include <functional>
#include <algorithm>
#include <iterator>

#include <initializer_list>
#include <list>
#include <array>
#include <vector>
#include <map>
#include <unordered_map>

namespace libasist {

// typedef

// initializer list template type
template <typename t_val_t>
using ilist_t = std::initializer_list<t_val_t>;

} // typedef

#endif//LIBASIST_HEAD_STDL_HXX
