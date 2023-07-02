#ifndef LIBASIST_MEMO_PAGER_HXX
#define LIBASIST_MEMO_PAGER_HXX 1

#include "../head.hxx"

/* headers */

#include "owner.hxx"
#include "mlink.hxx"

/* content */

namespace libasist { namespace memo { /* typedef */

/* page based allocator */
class pager_t : public owner_t
{
public: /* typedef */
    using this_t = pager_t;
    /* memory page */
    typedef struct mpage_t {
        mbyte_t*hdata = NULL; /* data head */
        mbyte_t*bdata = NULL; /* data back */
        mbyte_t*tdata = NULL; /* data back */
        mpage_t*npage = NULL; /* next page */
    } mpage_t; /* mpage_t */
public: /* codetor */
    pager_t(msize_t psize = ZERO, owner_t*owner = NULL);
    pager_t(const this_t&copy) = delete;
    pager_t(this_t&&copy) = delete;
    ~pager_t();
public: /* getters */
    [[nodiscard]] static
    this_t*get() { return basic; }
public: /* vetters */
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
        _ELOG("[memo::pager->elog]=("
            "[owner]=(%p)"
            "[hpage]=(%p)[bpage]=(%p)[tpage]=(%p)"
            "[malig]=(%zu)"
            ")%c",
            this->hpage, this->bpage, this->tpage,
            this->owner,
            this->malig,
            text::ENDL_CHAR
        );
    }
protected: /* datadef */
    owner_t*owner;
    mpage_t*hpage,*bpage,*tpage;
    mlink_t*mlink;
    msize_t malig;
public: /* datadef */
    static this_t*basic;
public: /* consdef */
    static constexpr msize_t MALIG = nums::get_aligned<mlink_t>();
    static constexpr msize_t MSIZE = 1 << 10;
}; /* pager_t */

} } /* typedef */

#endif/*LIBASIST_MEMO_PAGER_HXX*/
