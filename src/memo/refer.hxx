#pragma once

/* headers */

#include "../head.hxx"

#include "giver.hxx"
#include "taker.hxx"
#include "owner.hxx"
#include "heapy.hxx"

/* content */

namespace libasist { namespace memo { /* typedef */

/* reference type
 * description:
 * smart "shared" pointer analog
 * uses the given memory giver and taker functions
 * > this is the choice how to allocate/deallocate memory
 * it's value gets deleted if there is no any other refs
 */
template <typename value_t,
auto giver_f
= &giver_t::give_static<heapy_t>,
auto taker_f
= &taker_t::take_static<heapy_t>,
typename count_t = ::libasist::count_t
> class refer_t
{
public: /* typedef */
    using this_t = refer_t<value_t, giver_f, taker_f, count_t>;
    using vdata_t = value_t*;
public: /* codetor */
    [[nodiscard]] inline
    refer_t()
    : vdata(NULL), count(&const_cast<count_t&>(COUNT_ZERO))
    { }
    /* copy */
    [[nodiscard]] inline
    refer_t(refer_t&rcopy)
    : refer_t()
    { this->setup(rcopy); }
    [[nodiscard]] inline
    refer_t(refer_t&&mcopy)
    : refer_t()
    { this->setup(mcopy); mcopy.reset(); }
    template<typename value_t_t = value_t>
    [[nodiscard]] inline
    refer_t(refer_t<value_t_t, giver_f, taker_f, count_t>&rcopy)
    : refer_t()
    { this->setup(rcopy); }
    template<typename value_t_t = value_t>
    [[nodiscard]] inline
    refer_t(refer_t<value_t_t, giver_f, taker_f, count_t>&&mcopy)
    : refer_t()
    { this->setup(mcopy); mcopy.reset(); }
    /* value constructor */
    template<typename value_t_t = value_t, typename...vargs_t>
    [[nodiscard]] inline
    refer_t(vargs_t&&...vargs)
    : refer_t()
    { this->setup<value_t_t>(std::forward<vargs_t>(vargs)...); }
    ~refer_t() { this->reset(); }
public: /* getters */
    [[nodiscard]] inline
    count_t get_count() const
    { return *this->count; }
    /** vdata **/
    template<typename value_t_t = value_t>
    [[nodiscard]] inline
    const value_t_t*get_vdata()
    { return static_cast<value_t_t*>(this->vdata); }
    template<typename value_t_t = value_t>
    [[nodiscard]] inline
    const value_t_t get_vdata() const
    { return static_cast<value_t_t*>(this->vdata); }
    /** value **/
    template<typename value_t_t = value_t>
    [[nodiscard]] inline
    value_t_t&get_value()
    { return *static_cast<value_t_t*>(this->vdata); }
    template<typename value_t_t = value_t>
    [[nodiscard]] inline
    const value_t_t&get_value() const
    { return *static_cast<value_t_t*>(this->vdata); }
public: /* setters */
    template <typename value_t_t, typename...vargs_t>
    [[]] inline
    v1bit_t setup(vargs_t&&...vargs)
    {
        this->reset();
        giver_f(
            reinterpret_cast<mdata_t&>(this->vdata),
            sizeof(value_t), alignof(value_t)
        );
        new (this->vdata)value_t(std::forward<vargs_t>(vargs)...);
        giver_f(
            reinterpret_cast<mdata_t&>(this->count),
            sizeof(count_t), alignof(count_t)
        );
        new(this->count)count_t(1);
        return TRUTH;
    }
    template<typename value_t_t = value_t>
    [[]] inline
    v1bit_t setup(refer_t<value_t_t, giver_f, taker_f, count_t>&refer)
    { /* reference sharing */
        this->reset();
        this->vdata = static_cast<value_t*>(refer.vdata);
        this->count = refer.count;
        if (this->vet_count())
        { *this->count += 1; }
        else if (this->vdata)
        {
            giver_f(
                reinterpret_cast<mdata_t&>(this->count),
                sizeof(count_t), alignof(count_t)
            );
            new(this->count)count_t(1);
        }
        return TRUTH;
    }
    [[]] inline
    v1bit_t reset()
    {
        if (this->vet_count())
        {
            if ((*this->count -= 1) == COUNT_ZERO)
            {
                this->vdata->~value_t();
                taker_f(
                    reinterpret_cast<mdata_t&>(this->vdata),
                    sizeof(value_t), alignof(value_t)
                );
                this->count->~count_t();
                taker_f(
                    reinterpret_cast<mdata_t&>(this->count),
                    sizeof(count_t), alignof(count_t)
                );
            }
        }
        this->vdata = NULL;
        this->count =&const_cast<count_t&>(COUNT_ZERO);
        return TRUTH;
    }
public: /* vetters */
    [[nodiscard]] constexpr inline
    v1bit_t vet_vdata() const
    { return this->get_vdata() != NULL; }
    [[nodiscard]] constexpr inline
    v1bit_t vet_count() const
    { return this->get_count() > ZERO; }
    [[nodiscard]] constexpr inline
    v1bit_t vet_count(count_t count) const
    { return this->get_count() >= count; }
    [[nodiscard]] constexpr inline
    v1bit_t vet() const
    { return this->vet_vdata() && this->vet_count(); }
public: /* operats */
    [[]] inline
    refer_t&operator=(const refer_t&rcopy)
    { this->setup(rcopy); return *this; }
    [[]] inline
    refer_t&operator=(refer_t&&mcopy)
    { this->setup(mcopy) && mcopy.reset(); return *this; }
    template<typename value_t_t = value_t>
    [[]] inline
    refer_t&operator=(refer_t<value_t_t, giver_f, taker_f, count_t>&rcopy)
    { this->setup(rcopy); return *this; }
    template<typename value_t_t = value_t>
    [[]] inline
    refer_t&operator=(refer_t<value_t_t, giver_f, taker_f, count_t>&&mcopy)
    { this->setup(mcopy) && mcopy.reset(); return *this; }
    /** referencing  **/
    [[nodiscard]] constexpr inline
    value_t*operator&()
    { return this->vdata; }
    [[nodiscard]] constexpr inline
    const value_t*operator&() const
    { return this->vdata; }
    [[nodiscard]] constexpr inline
    value_t&operator*()
    { return *(this->vdata); }
    [[nodiscard]] constexpr inline
    const value_t& operator*() const
    { return *(this->vdata); }
    [[nodiscard]] constexpr inline
    value_t*operator->()
    { return (this->vdata); }
    [[nodiscard]] constexpr inline
    const value_t*operator->() const
    { return (this->vdata); }
    /** convertion **/
    [[nodiscard]] constexpr inline operator
    value_t*()
    { return static_cast<value_t*>(this->vdata); }
    [[nodiscard]] constexpr inline operator
    const value_t*() const
    { return static_cast<const value_t*>(this->vdata); }
    [[nodiscard]] constexpr inline operator
    value_t&()
    { return static_cast<value_t&>(*this->vdata); }
    [[nodiscard]] constexpr inline
    operator const value_t&() const
    { return static_cast<const value_t&>(*this->vdata); }
    template<typename value_t_t>
    [[nodiscard]] constexpr inline
    operator value_t_t*()
    { return static_cast<value_t_t*>(this->vdata); }
    template<typename value_t_t>
    [[nodiscard]] constexpr inline
    operator const value_t_t*() const
    { return static_cast<const value_t_t*>(this->vdata); }
    template<typename value_t_t>
    [[nodiscard]] inline
    operator refer_t<value_t_t, giver_f, taker_f, count_t>()
    { return refer_t<value_t_t, giver_f, taker_f, count_t>(*this); }
    template<typename value_t_t>
    [[nodiscard]] inline
    operator refer_t<value_t_t, giver_f, taker_f, count_t>() const
    { return refer_t<value_t_t, giver_f, taker_f, count_t>(*this); }
    /** logic **/
    [[nodiscard]] constexpr inline
    operator v1bit_t() const
    { return this->vdata != NULL; }
    [[nodiscard]] constexpr inline
    v1bit_t operator==(const refer_t&refer) const
    { return this->vdata == refer.vdata; }
    [[nodiscard]] constexpr inline
    v1bit_t operator!=(const refer_t&refer) const
    { return this->vdata != refer.vdata; }
    [[nodiscard]] constexpr inline
    v1bit_t operator==(const mdata_t vdata) const
    { return reinterpret_cast<mdata_t>(this->vdata) == vdata; }
    [[nodiscard]] constexpr inline
    v1bit_t operator!=(const mdata_t mdata) const
    { return reinterpret_cast<mdata_t>(this->vdata) == vdata; }
private: /* datadef */
    mutable vdata_t vdata = NULL;
    mutable count_t*count =&const_cast<count_t&>(COUNT_ZERO);
}; /* refer_t */

} } /* typedef */
