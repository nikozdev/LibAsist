#pragma once

/* headers */

#include "../head.hxx"

/* content */

namespace libasist { namespace work { /* typedef */

/* sarray_t
 * static array templated class
 */
template<typename vdata_t>
class sarray_t
{
public:     /* typedef */
    using this_t = sarray_t< vdata_t >;
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
    sarray_t()
    {
    }
    sarray_t(count_t count)
    {
    }
    ~sarray_t()
    {
    }
public:     /* opertor */
public:     /* getters */
public:     /* vetters */
public:     /* setters */
public:     /* actions */
private:    /* content */
    iter_t head;
};

} } /* typedef */
