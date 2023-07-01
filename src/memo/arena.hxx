#pragma once

/* headers */

#include "../head.hxx"

#include "owner.hxx"
#include "mlink.hxx"

namespace libasist { namespace memo { /* typedef */

/* arena allocator */
class arena_t : public owner_t
{
public: /* typedef */
    using this_t = arena_t;
public: /* codetor */
    arena_t(msize_t msize = ZERO, owner_t*owner = NULL);
    arena_t(const this_t&copy) = delete;
    arena_t(this_t&&copy) = delete;
    ~arena_t();
public: /* getters */
    [[nodiscard]] static
    this_t*get() { return basic; }
    [[nodiscard]] inline
    msize_t get_msize_full() const { return this->msize_full; }
    [[nodiscard]] inline
    msize_t get_msize_umax() const { return this->msize_umax; }
    [[nodiscard]] inline
    msize_t get_msize_used() const { return this->msize_used; }
    [[nodiscard]] inline
    msize_t get_msize_free() const
    { return this->msize_full - this->msize_used; }
public: /* vetters */
    [[nodiscard]] inline
    v1bit_t vet_mdata(mdata_t mdata) const
    { return (mdata >= this->mdata_head) && (mdata < this->mdata_back); }
    [[nodiscard]] inline
    v1bit_t vet_msize_used() const
    { return this->msize_used > 0; }
    [[nodiscard]] inline
    v1bit_t vet_msize_used(msize_t msize) const
    { return this->msize_used >= msize; }
    [[nodiscard]] inline
    v1bit_t vet_msize_free() const
    { return this->msize_used < this->msize_full; }
    [[nodiscard]] inline
    v1bit_t vet_msize_free(msize_t msize) const
    { return this->get_msize_free() >= msize; }
    [[nodiscard]] inline
    v1bit_t vet_msize_umax(msize_t msize) const
    { return this->msize_umax >= msize; }
public: /* actions */
    [[]] virtual
    v1bit_t give(mdata_t&mdata, msize_t msize, msize_t malig)
    override;
    [[]] virtual
    v1bit_t take(mdata_t&mdata, msize_t msize, msize_t malig)
    override;
    [[maybe_unused]] inline
    void elog(void) const
    {
        _ELOG("[memo::arena->elog]=("
            "[owner]=(%p)"
            "[mdata_head]=(%p)[mdata_tail]=(%p)[mdata_back]=(%p)"
            "[msize_full]=(%zu)[msize_used]=(%zu)[msize_umax]=(%zu)"
            "[mlink]=(%p)"
            "[malig]=(%zu))",
            this->owner,
            this->mdata_head, this->mdata_tail, this->mdata_back,
            this->msize_full, this->msize_used, this->msize_umax,
            this->mlink,
            this->malig
        );
    }
protected: /* datadef */
    owner_t*owner;
    udata_t mdata_head, mdata_tail, mdata_back;
	msize_t msize_full, msize_used, msize_umax;
    mlink_t*mlink;
    msize_t malig;
public: /* consdef */
    static constexpr msize_t MALIG = nums::get_aligned<mlink_t>();
    static constexpr msize_t MSIZE = 1 << 20;
public: /* datadef */
    static this_t*basic;
}; /* arena_t */

} } /* typedef */
