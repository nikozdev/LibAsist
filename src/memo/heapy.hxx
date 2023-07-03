#ifndef LIBASIST_MEMO_HEAPY_HXX
#define LIBASIST_MEMO_HEAPY_HXX 1

#include "../head.hxx"

/* headers */

#include "owner.hxx"

/* content */

namespace libasist { namespace memo { /* typedef */

/* heap allocator */
class heapy_t : public owner_t
{
public: /* typedef */
    using this_t = heapy_t;
public: /* codetor */
    heapy_t();
    heapy_t(const this_t&copy) = delete;
    heapy_t(this_t&&copy) = delete;
    ~heapy_t();
public: /* getters */
    [[nodiscard]] static
    this_t*get() { return basic; }
    [[nodiscard]] inline
    msize_t get_msize_umax() const { return this->msize_umax; }
    [[nodiscard]] inline
    msize_t get_msize_used() const { return this->msize_used; }
public: /* vetters */
    [[nodiscard]] inline
    v1bit_t vet_msize_used() const
    { return this->msize_used > 0; }
    [[nodiscard]] inline
    v1bit_t vet_msize_used(msize_t msize) const
    { return this->msize_used >= msize; }
    [[nodiscard]] inline
    v1bit_t vet_msize_umax() const
    { return this->msize_umax > 0; }
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
        _ELOG("[memo::heapy->elog]=("
            "[msize_used]=({:d})[msize_umax]=({:d})"
            "[malig]=({:d}))",
            this->msize_used, this->msize_umax,
            this->malig
        );
    }
public: /* symbols */
    [[nodiscard]] inline
    operator owner_t&()
    { return static_cast<owner_t&>(*this); }
    [[nodiscard]] inline
    operator owner_t*()
    { return static_cast<owner_t*>(this); }
protected: /* datadef */
    msize_t msize_used; /* currently used space */
    msize_t msize_umax; /* maximally used space */
    msize_t malig;
public: /* datadef */
    static this_t*basic;
public: /* consdef */
    static constexpr msize_t MALIG = nums::get_aligned<mdata_t>();
}; /* heapy_t */

} } /* typedef */

#endif/*LIBASIST_MEMO_HEAPY_HXX*/
