#include "../head.hxx"

/* headers */

#include "stack.hxx"
#include "heapy.hxx"

/* content */

namespace libasist { namespace memo { /* codetor */

stack_t::stack_t(msize_t msize, owner_t*owner) :
    owner_t(),
    owner(owner ? owner : heapy_t::basic),
    mdata_head(NULL), mdata_tail(NULL), mdata_back(NULL),
    msize_full(msize), msize_umax(ZERO), msize_used(ZERO),
    malig(MALIG)
{
    this->msize_full = nums::get_aligned(this->msize_full, this->malig);
    static_cast<giver_t*>(this->owner)
    ->give(this->mdata_head, this->msize_full, this->malig);
    this->mdata_back = this->mdata_head;
    this->mdata_tail = this->mdata_head + this->msize_full;
}
stack_t::~stack_t()
{
    static_cast<taker_t*>(this->owner)
    ->take(this->mdata_head, this->msize_full, this->malig);
}

} } /* codetor */

namespace libasist { namespace memo { /* actions */

v1bit_t stack_t::give(mdata_t&mdata, msize_t msize, msize_t malig)
{
#if defined(LIBASIST_MEMO_MSIZE_VET)
    _EFNOT(msize > ZERO, return FALSE, "cannot give 0 bytes!");
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
    mdata = this->mdata_back;
    this->mdata_back += msize;
#if defined(LIBASIST_MEMO_MSIZE_SET)
    this->msize_umax += msize;
    this->msize_used += msize;
#endif/*ifd(LIBASIST_MEMO_MSIZE_SET)*/
    return TRUTH;
} /* give */

v1bit_t stack_t::take(mdata_t&mdata, msize_t msize, msize_t malig)
{
#if defined(LIBASIST_MEMO_MSIZE_VET)
    _EFNOT(mdata != NULL, return FALSE, "cannot deallocate by null!");
    _EFNOT(msize != ZERO, return FALSE, "cannot deallocate 0 bytes!");
#endif/*ifd(LIBASIST_MEMO_MSIZE_VET)*/
#if defined(LIBASIST_MEMO_MDATA_VET)
    _EFNOT(this->vet_mdata(mdata), return FALSE, "mdata does not belong this arena!");
#endif/*ifd(LIBASIST_MEMO_MDATA_VET)*/
    malig = nums::get_aligned(malig, this->malig);
    msize = nums::get_aligned(msize, malig);
#if defined(LIBASIST_MEMO_MSIZE_VET)
    _EFNOT(this->vet_msize_used(msize), return FALSE, "too many bytes to delete!");
#endif/*ifd(LIBASIST_MEMO_MSIZE_VET)*/
#if defined(LIBASIST_MEMO_MDATA_VET)
    _EFNOT(
        this->vet_mdata(mdata, msize),
        return FALSE,
        "mdata has to be at the top of the stack!"
    );
#endif/*ifd(LIBASIST_MEMO_MDATA_VET)*/
    this->mdata_back -= msize;
#if defined(LIBASIST_MEMO_MSIZE_SET)
	this->msize_used -= msize;
#endif/*ifd(LIBASIST_MEMO_MSIZE_SET)*/
    return TRUTH;
} /* take */

} } /* actions */

namespace libasist { namespace memo { /* datadef */

stack_t*stack_t::basic = NULL;

} } /* datadef */
