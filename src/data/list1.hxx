#ifndef LIBASIST_DATA_LIST1_HXX 
#define LIBASIST_DATA_LIST1_HXX

#include "../head.hxx"

namespace libasist { namespace data {

// typedef

#if 1
#else
template<typename data_t>
class list1_t
{
public: // typedef
    using this_t = list1_t< data_t >;
    typedef struct iter_t
    {
        data_t* data;
        iter_t* next;
    } iter_t;
public: // codetor
    list1_t():
        head{ nullptr, nullptr }
    {
    }
    ~list1_t()
    {
        this->remove( this->get_head() );
    }
public: // opertor
public: // getters
    iter_t&get_head()
    {
        return this->head;
    }
    iter_t&get_tail()
    {
        const iter_t& tail = this->head;
        while ( tail.data )
        {
            tail = tail.next;
        }
        return tail;
    }
    const iter_t&get_last() const
    {
        const iter_t& last = this->head;
        while ( last.next )
        {
            last = last.next;
        }
        return this->head;
    }
public: // vetters
    bool_t vet_iter( const iter_t& iter ) const
    {
        return false;
    }
public: // setters
    bool_t insert(const data_t& data)
    {
        return false;
    }
    bool_t remove(const iter_t& iter)
    {
        return false;
    }
    bool_t assign(const iter_t& iter, const data_t& data)
    {
        return false;
    }
private: // content
    iter_t head;
}; // 1-linked list templated type
#endif

} } // namespace libasist { namespace data {

#endif//LIBASIST_DATA_LIST1_HXX
