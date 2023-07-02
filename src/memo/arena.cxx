#ifndef LIBASIST_MEMO_ARENA_CXX
#define LIBASIST_MEMO_ARENA_CXX 1

#include "../head.hxx"

/* headers */

#include "arena.hxx"
#include "heapy.hxx"

/* content */

namespace libasist { namespace memo { /* codetor */

arena_t::arena_t(msize_t msize, owner_t*owner) :
    owner_t(),
    owner(owner ? owner : heapy_t::basic),
    mdata_head(NULL), mdata_tail(NULL), mdata_back(NULL),
    msize_full(msize), msize_umax(ZERO), msize_used(ZERO),
    malig(MALIG),
    mlink(NULL)
{
    this->msize_full = nums::get_aligned(this->msize_full, this->malig);
    static_cast<giver_t*>(this->owner)
    ->give(this->mdata_head, this->msize_full, this->malig);
    this->mdata_back = this->mdata_head;
    this->mdata_tail = this->mdata_head + this->msize_full;
}
arena_t::~arena_t()
{
    static_cast<taker_t*>(this->owner)
    ->take(this->mdata_head, this->msize_full, this->malig);
}

} } /* codetor */

namespace libasist { namespace memo { /* actions */

v1bit_t arena_t::give(mdata_t&mdata, msize_t msize, msize_t malig)
{
#if defined(LIBASIST_MEMO_MSIZE_VET)
    _EFNOT(msize > ZERO, return FALSE,  "cannot give %zu bytes!", msize);
#endif/*ifd(LIBASIST_MEMO_MSIZE_VET)*/
    mdata = NULL;
    malig = nums::get_aligned(malig, this->malig);
    msize = nums::get_aligned(msize, malig);
#if defined(LIBASIST_MEMO_MSIZE_VET)
    _EFNOT(this->vet_msize_free(msize), {
        this->elog();
        return FALSE;
    }, "vet_msize_free error!");
#endif/*ifd(LIBASIST_MEMO_MSIZE_VET)*/
    mlink_t*plink = NULL;
    mlink_t*nlink = this->mlink;
    while (nlink)
    {
        if (nlink->has_msize(msize))
        {
            if (plink) { plink->nlink = nlink->nlink; }
            else { this->mlink = nlink->nlink; }
            mdata = nlink;
#if defined(LIBASIST_MEMO_MSIZE_SET)
            this->msize_used += msize;
#endif/*ifd(LIBASIST_MEMO_MSIZE_SET)*/
            return TRUTH;
        }
        plink = nlink;
        nlink = nlink->nlink;
    }
    /* failed to get a free-list block, advance the back */
    mdata = this->mdata_back;
    this->mdata_back += msize;
#if defined(LIBASIST_MEMO_MSIZE_SET)
    this->msize_umax += msize;
    this->msize_used += msize;
#endif/*ifd(LIBASIST_MEMO_MSIZE_SET)*/
    return TRUTH;
}

v1bit_t arena_t::take(mdata_t&mdata, msize_t msize, msize_t malig)
{
#if defined(LIBASIST_MEMO_MSIZE_VET)
    _EFNOT(mdata != NULL, return FALSE, "cannot deallocate by null!");
    _EFNOT(msize != ZERO, return FALSE, "cannot deallocate %zu bytes!", msize);
#endif/*ifd(LIBASIST_MEMO_MSIZE_VET)*/
#if defined(LIBASIST_MEMO_MDATA_VET)
    _EFNOT(this->vet_mdata(mdata), return FALSE, "mdata does not belong this arena!");
#endif/*ifd(LIBASIST_MEMO_MDATA_VET)*/
    malig = nums::get_aligned(malig, this->malig);
    msize = nums::get_aligned(msize, malig);
#if defined(LIBASIST_MEMO_MSIZE_VET)
    _EFNOT(this->vet_msize_used(msize), return FALSE, "too many bytes to delete!");
#endif/*ifd(LIBASIST_MEMO_MSIZE_VET)*/
    mlink_t*mlink = new(mdata)mlink_t();
    mlink->nlink = this->mlink;
    mlink->msize = msize;
    this->mlink = mlink;
	/* mdata_back and msize_umax should not be changed back! */
#if defined(LIBASIST_MEMO_MSIZE_SET)
	this->msize_used -= msize;
#endif/*ifd(LIBASIST_MEMO_MSIZE_SET)*/
    return TRUTH;
}

} } /* actions */

namespace libasist { namespace memo { /* datadef */

arena_t*arena_t::basic = NULL;;

} } /* datadef */

#endif/*LIBASIST_MEMO_ARENA_CXX*/
