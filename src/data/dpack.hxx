#ifndef LIBASIST_DATA_DPACK_HXX
#define LIBASIST_DATA_DPACK_HXX

#include "../head.hxx"

namespace libasist { namespace data {

// typedef

#if 1
// dynamic array template type
template <typename t_val_t>
using dpack_t = std::vector<t_val_t>;
#else
template<typename vdata_t>
class dpack_t
{
public: // typedef
    using this_t = dpack_t< vdata_t >;
    using mdata_t = vdata_t*;
    class iter_t
    {
    public:     /* typedef */
        using this_t = iter_t;
    public:     /* codetor */
        iter_t(mdata_t mdata = nullptr): mdata(mdata) {}
    public:     /* opertor */
        auto operator&()
        {
            return this->mdata;
        }
        auto operator*()
        {
            return *this->mdata;
        }
    public:     /* getters */
    public:     /* vetters */
    public:     /* setters */
    private:    /* content */
        mdata_t mdata;
    }; // iterator
public: // codetor
    dpack_t()
    {
    }
    dpack_t(count_t count)
    {
    }
    ~dpack_t()
    {
    }
public: // opertor
public: // getters
public: // vetters
public: // setters
public: // actions
private: // content
    iter_t head;
}; // dynamic pack template type
#endif

} } // typedef

#endif//LIBASIST_DATA_DPACK_HXX
