#pragma once

#include "../head.hxx"

/* headers */

/* content */

namespace libasist { namespace memo { /* typedef */

/* memory giver abstract type */
class giver_t
{
public: /* typedef */
    using this_t = giver_t;
public: /* codetor */
    giver_t() = default;
    giver_t(const this_t&copy) = delete;
    giver_t(this_t&&copy) = delete;
    virtual ~giver_t() = default;
public: /* extern abstract give */
    [[]] virtual
    v1bit_t give(mdata_t&mdata, msize_t msize, msize_t malig)
    = 0;
public: /* static abstract give */
    template<typename giver_t_t>
    [[]] static constexpr
    v1bit_t give_static(mdata_t&mdata, msize_t msize, msize_t malig)
    { return giver_t_t::get()->give(mdata, msize, malig); }
public: /* inline template give */
    template<typename vdata_t>
    [[]] inline constexpr
    v1bit_t give(vdata_t*&vdata, msize_t msize, msize_t malig)
    { return this->give(
        reinterpret_cast<mdata_t&>(vdata), msize, malig
    ); }
    template<typename vdata_t>
    [[]] inline constexpr
    v1bit_t give(vdata_t*&vdata, count_t count)
    { return this->give(
        reinterpret_cast<mdata_t&>(vdata),
        count * sizeof(vdata_t),
        alignof(vdata_t)
    ); }
public: /* static template give */
    template<typename giver_t_t, typename vdata_t>
    [[]] static constexpr
    v1bit_t give_static(vdata_t*&vdata, count_t count)
    { return giver_t_t::get()->give(vdata, count); }
public: /* inline template new */
    template<typename vdata_t, typename...vargs_t>
    [[]] inline constexpr
    v1bit_t new_one(vdata_t*&vdata, vargs_t&&...vargs)
    {
        this->give<vdata_t>(vdata, 1);
        new(vdata)vdata_t(std::forward<vargs_t>(vargs)...);
        return TRUTH;
    }
    template<typename vdata_t, typename ... vargs_t>
    [[]] inline constexpr
    v1bit_t new_mul(vdata_t*&vdata, count_t count, vargs_t&&...vargs)
    {
        this->give<vdata_t>(vdata, count);
        for (vdata_t*iter = vdata,*tail = iter + count; iter < tail; iter++)
        { new(iter)vdata_t(std::forward<vargs_t>(vargs)...); }
        return TRUTH;
    }
public: /* static template new */
    template<typename giver_t_t, typename vdata_t, typename...vargs_t>
    [[]] static constexpr
    v1bit_t new_one_static(vdata_t*&vdata, vargs_t&&...vargs)
    { return giver_t_t::get()->new_one(
        vdata,
        std::forward<vargs_t>(vargs)...
    ); }
    template<typename giver_t_t, typename vdata_t, typename ... vargs_t>
    [[]] static constexpr
    v1bit_t new_mul_static(vdata_t*&vdata, count_t count, vargs_t&&...vargs)
    { return giver_t_t::get()->new_mul(
        vdata,
        count,
        std::forward<vargs_t>(vargs)...
    ); }
public: /* operats */
    auto operator=(const this_t& copy) = delete;
    auto operator=(this_t&& copy) = delete;
}; /* giver_t */

} } /* typedef */
