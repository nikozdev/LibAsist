#pragma once

/* headers */

#include "head.hxx"

/* content */

namespace libasist { namespace work { /* typedef */

/* darray_t_t
 * dynamic array templated class
 */
template<typename vdata_t>
class darray_t_t
{
public:     /* typedef */
    using this_t = darray_t_t< vdata_t >;
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
    darray_t_t()
    {
    }
    darray_t_t(count_t count)
    {
    }
    ~darray_t_t()
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
