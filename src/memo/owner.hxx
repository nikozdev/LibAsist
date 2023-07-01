#pragma once

#include "../head.hxx"

/* headers */

#include "giver.hxx"
#include "taker.hxx"

/* content */

namespace libasist { namespace memo { /* typedef */

/* memory owner abstract type */
class owner_t : public giver_t, public taker_t
{
public: /* typedef */
    using this_t = owner_t;
public: /* codetor */
    owner_t() = default;
    owner_t(const this_t&copy) = delete;
    owner_t(this_t&&copy) = delete;
    virtual ~owner_t() = default;
public: /* extern abstract give-take */
    virtual
    v1bit_t give(mdata_t&mdata, msize_t msize, msize_t malig)
    = 0;
    virtual
    v1bit_t take(mdata_t&mdata, msize_t msize, msize_t malig)
    = 0;
public: /* inline abstract edit */
    inline constexpr
    v1bit_t edit(mdata_t&mdata, msize_t s_old, msize_t s_new, msize_t malig)
    {
        mdata_t older = mdata;
        mdata = NULL;
        if (s_new > 0) { this->give(mdata, s_new, malig); }
        if (s_old > 0)
        {
            if (mdata)
            {
                s_old = nums::get_aligned(s_old, malig);
                s_new = nums::get_aligned(s_new, malig);
                malig = nums::get_min(s_old, s_new);
                std::memcpy(mdata, older, s_new);
            }
            this->take(older, s_old, malig);
        }
        return TRUTH;
    }
public: /* static abstract edit */
    template<typename owner_t_t>
    static constexpr
    v1bit_t edit(mdata_t&mdata, msize_t s_old, msize_t s_new, msize_t malig)
    { return owner_t_t::get()->edit(mdata, s_old, s_new, malig); }
public: /* inline template edit */
    template<typename mdata_t>
    inline constexpr
    v1bit_t edit(mdata_t&mdata, msize_t s_old, msize_t s_new, msize_t malig)
    { return this->edit(
        reinterpret_cast<mdata_t&>(mdata),
        s_old, s_new,
        malig
    ); }
    template<typename vdata_t>
    inline constexpr
    v1bit_t edit(vdata_t*&vdata, count_t c_old, count_t c_new)
    { return this->edit(
        vdata,
        c_old * sizeof(vdata_t), c_new * sizeof(vdata_t),
        alignof(vdata_t)
    ); }
public: /* static template edit */
    template<typename owner_t_t, typename mdata_t>
    static constexpr
    v1bit_t edit(mdata_t&mdata, msize_t s_old, msize_t s_new, msize_t malig)
    { return owner_t_t::get()->template edit<mdata_t>(
        mdata, s_old, s_new, malig
    ); }
    template<typename owner_t_t, typename vdata_t>
    static constexpr
    v1bit_t edit(vdata_t*&vdata, msize_t s_old, msize_t s_new, msize_t malig)
    { return owner_t_t::get()->template edit<vdata_t>(
        vdata, s_old, s_new, malig
    ); }
public: /* operats */
    auto operator=(const this_t& copy) = delete;
    auto operator=(this_t&& copy) = delete;
}; /* owner_t */

} } /* typedef */
