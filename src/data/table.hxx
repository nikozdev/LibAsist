#ifndef LIBASIST_DATA_TABLE_HXX
#define LIBASIST_DATA_TABLE_HXX

#include "../head.hxx"

namespace libasist { namespace data {

// typedef

#if 1
// hash table template type
template <typename t_key_t, typename t_val_t>
using table_t = std::unordered_map<t_key_t, t_val_t>;
#else
template<typename index_t, typename value_t>
class table_t
{
public: // typedef
    using this_t = table_t< index_t, value_t >;
public: // codetor
    table_t()
    {
    }
    ~table_t()
    {
    }
public: // operats
public: // getters
public: // vetters
public: // setters
public: // actions
}; // hash table template type
#endif

} } // namespace libasist { namespace data {

#endif//LIBASIST_DATA_TABLE_HXX
