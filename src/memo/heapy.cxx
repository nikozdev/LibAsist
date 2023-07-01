#include "../head.hxx"

/* headers */

#include "heapy.hxx"

/* content */

namespace libasist { namespace memo { /* codetor */

heapy_t::heapy_t() :
    msize_used(ZERO), msize_umax(ZERO),
    malig(MALIG)
{}

heapy_t::~heapy_t()
{}

} } /* codetor */

namespace libasist { namespace memo { /* actions */

v1bit_t heapy_t::give(mdata_t&mdata, msize_t msize, msize_t malig)
{
#if defined(LIBASIST_MEMO_MSIZE_VET)
    _EFNOT(msize > ZERO, return FALSE, "cannot give %zu bytes!", msize);
#endif/*LIBASIST_MEMO_MSIZE_VET*/
    malig = nums::get_aligned(malig, this->malig);
    msize = nums::get_aligned(msize, malig);
#if _NEWDELDEF
    mdata = std::malloc(msize);
#else
    mdata = new mbyte_t[msize];
#endif
#if defined(LIBASIST_MEMO_MSIZE_SET)
    this->msize_used += msize;
    this->msize_umax = nums::get_max(this->msize_umax, this->msize_used);
#endif/*ifd(LIBASIST_MEMO_MSIZE_SET)*/
    return TRUTH;
}

v1bit_t heapy_t::take(mdata_t&mdata, msize_t msize, msize_t malig)
{
#if defined(LIBASIST_MEMO_MSIZE_VET)
    _EFNOT(msize > ZERO, return FALSE,  "cannot give %zu bytes!", msize);
#endif/*ifd(LIBASIST_MEMO_MSIZE_VET)*/
    malig = nums::get_aligned(malig, this->malig);
    msize = nums::get_aligned(msize, malig);
#if _NEWDELDEF
    std::free(mdata);
#else
    delete[]static_cast<mbyte_t*>(mdata);
#endif
#if defined(LIBASIST_MEMO_MSIZE_SET)
    this->msize_used -= msize;
#endif/*ifd(LIBASIST_MEMO_MSIZE_SET)*/
    return TRUTH;
}

} } /* actions */

namespace libasist { namespace memo { /* datadef */

heapy_t*heapy_t::basic = NULL;

} } /* datadef */
