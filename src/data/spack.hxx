#ifndef LIBASIST_DATA_SPACK_HXX
#define LIBASIST_DATA_SPACK_HXX

#include "../head.hxx"

namespace libasist { namespace data {

// typedef

#if 1
// static array template type
template <typename t_val_t, size_t t_count>
using spack_t = std::array<t_val_t, t_count>;
#else
template<typename vdata_t>
class spack_t
{
public:     /* typedef */
    using this_t = spack_t< vdata_t >;
    using mdata_t = vdata_t*;
    /* iter_t
     * iterator
     */
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
    };
public:     /* codetor */
    spack_t()
    {
    }
    spack_t(count_t count)
    {
    }
    ~spack_t()
    {
    }
public:     /* opertor */
public:     /* getters */
public:     /* vetters */
public:     /* setters */
public:     /* actions */
private:    /* content */
    iter_t head;
}; // static pack template type
#endif

} } // namespace libasist { namespace data {

#endif//LIBASIST_DATA_SPACK_HXX
