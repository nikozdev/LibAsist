#ifndef LIBASIST_MEMO_DUMMY_CXX
#define LIBASIST_MEMO_DUMMY_CXX 1

#include "../head.hxx"

/* headers */

#include "dummy.hxx"

/* content */

namespace libasist { namespace memo { /* codetor */

dummy_t::dummy_t() :
    msize_used(ZERO), msize_umax(ZERO),
    malig(MALIG)
{}

dummy_t::~dummy_t()
{}

} } /* codetor */

namespace libasist { namespace memo { /* actions */

v1bit_t dummy_t::give(mdata_t&mdata, msize_t msize, msize_t malig)
{
#if defined(LIBASIST_MEMO_MSIZE_VET)
    _EFNOT(msize > ZERO, return FALSE, "cannot give %zu bytes!", msize);
#endif/*LIBASIST_MEMO_MSIZE_VET*/
    malig = nums::get_aligned(malig, this->malig);
    msize = nums::get_aligned(msize, malig);
#if defined(LIBASIST_MEMO_MSIZE_SET)
    this->msize_used += msize;
    this->msize_umax = nums::get_max(this->msize_umax, this->msize_used);
#endif/*ifd(LIBASIST_MEMO_MSIZE_SET)*/
    return TRUTH;
}

v1bit_t dummy_t::take(mdata_t&mdata, msize_t msize, msize_t malig)
{
#if defined(LIBASIST_MEMO_MSIZE_VET)
    _EFNOT(msize > ZERO, return FALSE,  "cannot give %zu bytes!", msize);
#endif/*ifd(LIBASIST_MEMO_MSIZE_VET)*/
    malig = nums::get_aligned(malig, this->malig);
    msize = nums::get_aligned(msize, malig);
#if defined(LIBASIST_MEMO_MSIZE_SET)
    this->msize_used -= msize;
#endif/*ifd(LIBASIST_MEMO_MSIZE_SET)*/
    return TRUTH;
}

} } /* actions */

namespace libasist { namespace memo { /* datadef */

dummy_t*dummy_t::basic = NULL;

} } /* datadef */

#endif/*LIBASIST_MEMO_DUMMY_CXX*/
