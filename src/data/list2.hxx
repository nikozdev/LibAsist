#ifndef LIBASIST_DATA_LIST2_HXX
#define LIBASIST_DATA_LIST2_HXX

#include "../head.hxx"

namespace libasist { namespace data {

// typedef

#if 1
// 2-linked list template type
template <typename t_val_t>
using list2_t = std::list<t_val_t>;
#else
template< typename value_t >
class list2_t
{
public: /* typedef */
    using this_t = list2_t< value_t >;
public: /* codetor */
    list2_t()
    {
    }
    ~list2_t()
    {
    }
public: // opertor
public: // getters
public: // vetters
public: // setters
public: // actions
}; // 2-linked list template type
#endif

} } // namespace libasist { namespace data {

#endif//LIBASIST_DATA_LIST2_HXX
