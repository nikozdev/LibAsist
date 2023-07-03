#ifndef LIBASIST_DATA_TABLE_HXX
#define LIBASIST_DATA_TABLE_HXX

#include "../head.hxx"

namespace libasist { namespace data {

// typedef

#if 1
// binary tree template type
template <typename t_key_t, typename t_val_t>
using btree_t = std::map<t_key_t, t_val_t>;
#else
template<typename index_t, typename value_t>
class bree_t
{
public: // typedef
    using this_t = bree_t<index_t, value_t>;
public: // codetor
    bree_t()
    {
    }
    ~bree_t()
    {
    }
public: // opertor
public: // getters
public: // vetters
public: // setters
public: // actions
}; // binary tree templated type
#endif

} } // namespace libasist { namespace data {

#endif//LIBASIST_UTIL_TABLE_HXX
