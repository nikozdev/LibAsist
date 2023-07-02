#ifndef LIBASIST_MEMO_TAKER_HXX
#define LIBASIST_MEMO_TAKER_HXX 1

#include "../head.hxx"

/* headers */

/* content */

namespace libasist { namespace memo { /* typedef */

/* memory taker abstract type */
class taker_t
{
public: /* typedef */
    using this_t = taker_t;
public: /* codetor */
    taker_t() = default;
    taker_t(const this_t&copy) = delete;
    taker_t(this_t&&copy) = delete;
    virtual ~taker_t() = default;
public: /* extern abstract take */
    virtual
    v1bit_t take(mdata_t&mdata, msize_t msize, msize_t malig)
    = 0;
public: /* static abstract take */
    template<typename taker_t_t>
    [[]] static constexpr
    v1bit_t take_static(mdata_t&mdata, msize_t msize, msize_t malig)
    { return taker_t_t::get()->take(mdata, msize, malig); }
public: /* inline template take */
    template<typename vdata_t>
    [[]] inline constexpr
    v1bit_t take(vdata_t*&vdata, msize_t msize, msize_t malig)
    { return this->take(
        reinterpret_cast<mdata_t&>(vdata), msize, malig
    ); } 
    template<typename vdata_t>
    [[]] inline constexpr
    v1bit_t take(vdata_t*&vdata, count_t count)
    { return this->take(
        reinterpret_cast<mdata_t&>(vdata),
        count * sizeof(vdata_t),
        alignof(vdata_t)
    ); } 
public: /* static template take */
    template<typename taker_t_t, typename vdata_t>
    [[]] static constexpr
    v1bit_t take_static(vdata_t*&vdata, count_t count)
    { return taker_t_t::get()->take(vdata, count); } 
public: /* inline template del */
    template<typename vdata_t>
    [[]] inline constexpr
    v1bit_t del_one(vdata_t*&vdata)
    {
        vdata->~vdata_t();
        this->take<vdata_t>(vdata, 1);
        return TRUTH;
    }
    template <typename vdata_t>
    [[]] inline constexpr
    v1bit_t del_mul(vdata_t*&vdata, count_t count)
    {
        for (vdata_t*iter = vdata,*tail = iter + count; iter < tail; iter++)
        { iter->~vdata_t(); }
        this->take<vdata_t>(vdata, count);
        return TRUTH;
    }
public: /* static template del */
    template<typename taker_t_t, typename vdata_t>
    [[]] static constexpr
    v1bit_t del_one_static(vdata_t*&vdata)
    { return taker_t_t::get()->del_one(vdata); }
    template <typename taker_t_t, typename vdata_t>
    [[]] static constexpr
    v1bit_t del_mul(vdata_t*&vdata, count_t count)
    { return taker_t_t::get()->del_mul(vdata, count); }
public: /* operats */
    auto operator=(const this_t& copy) = delete;
    auto operator=(this_t&& copy) = delete;
}; /* taker_t */

} } /* typedef */

#endif/*LIBASIST_MEMO_TAKER_HXX*/
