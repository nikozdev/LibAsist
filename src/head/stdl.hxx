#ifndef LIBASIST_HEAD_STDL_HXX
#define LIBASIST_HEAD_STDL_HXX 1

/* headers */

#include "conf.hxx"
#include "osys.hxx"
#include "tool.hxx"
#include "defn.hxx"

/** standard **/

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

/* content */

namespace libasist { /* typedef */

/* initializer list template type
*/
template <typename t_val_t>
using inlist_t = std::initializer_list<t_val_t>;

/* 2-linked list template type
*/
template <typename t_val_t>
using l2list_t = std::list<t_val_t>;

/* static array template type
*/
template <typename t_val_t, size_t t_count>
using sarray_t = std::array<t_val_t, t_count>;

/* dynamic array template type
*/
template <typename t_val_t>
using darray_t = std::vector<t_val_t>;

/* binary table template type
*/
template <typename t_key_t, typename t_val_t>
using btable_t = std::map<t_key_t, t_val_t>;

/* hash table template type
*/
template <typename t_key_t, typename t_val_t>
using htable_t = std::unordered_map<t_key_t, t_val_t>;

} /* typedef */

#endif/*LIBASIST_HEAD_STDL_HXX*/
