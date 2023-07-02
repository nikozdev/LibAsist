#ifndef LIBASIST_MEMO_PAGER_CXX
#define LIBASIST_MEMO_PAGER_CXX 1

#include "../head.hxx"

/* headers */

#include "pager.hxx"
#include "heapy.hxx"

namespace libasist { namespace memo { /* codetor */

pager_t::pager_t(msize_t psize, owner_t*owner) :
    owner_t(),
    owner(owner ? owner : heapy_t::basic),
    hpage(NULL), bpage(NULL), tpage(NULL),
    mlink(NULL),
    malig(MALIG)
{
    this->owner->new_one(this->hpage),
    static_cast<giver_t*>(this->owner)
    ->give(this->hpage->hdata, psize, this->malig),
    this->hpage->npage = NULL;
    this->hpage->tdata = this->hpage->hdata + psize;
    this->hpage->bdata = this->hpage->hdata;
    this->bpage = this->hpage;
    this->tpage = this->hpage;
} /* ctor */
pager_t::~pager_t()
{
    auto ipage = this->hpage;
    while (ipage)
    {
        this->hpage = ipage->npage;
        auto psize = (ipage->tdata - ipage->hdata);
        static_cast<taker_t*>(this->owner)
        ->take(ipage->hdata, psize, this->malig),
        this->owner->del_one(ipage),
        ipage = this->hpage;
    }
    this->hpage = NULL; this->bpage = NULL; this->tpage = NULL;
} /* dtor */

} } /* codetor */

namespace libasist { namespace memo { /* actions */

v1bit_t pager_t::give(mdata_t&mdata, msize_t msize, msize_t malig)
{
    /* argument adjustment */
    mdata = NULL;
    malig = nums::get_aligned(malig, this->malig);
    msize = nums::get_aligned(msize, malig);
    /* memory link */
    mlink_t*plink = NULL;
    mlink_t*nlink = this->mlink;
    while (nlink)
    {
        if (nlink->has_msize(msize))
        {
            if (plink) { plink->nlink = nlink->nlink; }
            else { this->mlink = nlink->nlink; }
            mdata = nlink;
            return TRUTH;
        }
        plink = nlink;
        nlink = nlink->nlink;
    }
    /* the default page advancement */
    if ((this->bpage->tdata - this->bpage->bdata) < msize)
    { /* not enough at the back - move to the next page */
        this->owner->new_one(this->tpage->npage);
        this->tpage = this->tpage->npage;
        this->tpage->npage = NULL;
        auto nsize = nums::get_max(MSIZE, msize);
        static_cast<giver_t*>(this->owner)
        ->give(this->tpage->hdata, nsize, malig);
        this->tpage->bdata = this->tpage->hdata;
        this->tpage->tdata = this->tpage->hdata + nsize;
        this->bpage->npage = this->tpage;
        this->bpage = this->bpage->npage;
    }
    mdata = this->bpage->bdata;
    this->bpage->bdata += msize;
    return TRUTH;
} /* give */

v1bit_t pager_t::take(mdata_t&mdata, msize_t msize, msize_t malig)
{
    malig = nums::get_aligned(malig, this->malig);
    msize = nums::get_aligned(msize, malig);
    mlink_t*mlink = new(mdata)mlink_t();
    mlink->nlink = this->mlink;
    mlink->msize = msize;
    this->mlink = mlink;
    return TRUTH;
} /* take */

} } /* actions */

namespace libasist { namespace memo { /* datadef */

pager_t*pager_t::basic = NULL;

} } /* datadef */

#endif/*LIBASIST_MEMO_PAGER_CXX*/
