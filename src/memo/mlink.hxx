#ifndef LIBASIST_MEMO_MLINK_HXX
#define LIBASIST_MEMO_MLINK_HXX 1

#include "../head.hxx"

/* headers */

/* content */

namespace libasist { namespace memo { /* typedef */

/* memory link type */
typedef struct mlink_t {
public: /* codetor */
    constexpr inline mlink_t() : nlink(NULL), msize(ZERO) { }
public: /* getters */
    inline mdata_t give(msize_t msize)
    {
        mlink_t*plink = NULL;
        mlink_t*nlink = this;
        while (nlink)
        { /* try the following links */
            if (nlink->has_msize(msize))
            {
                if (plink) { plink->nlink = nlink->nlink; }
                nlink->msize = ZERO;
                return nlink;
            }
            plink = nlink;
            nlink = nlink->nlink;
        }
        return NULL;
    }
public: /* vetters */
    inline v1bit_t has_msize(msize_t msize) const
    { return this->msize == msize; }
    inline v1bit_t has_nlink(msize_t msize) const
    {
        if (this->nlink) { return this->nlink->has_nlink(msize); }
        else { return this->has_msize(msize); }
    }
    inline v1bit_t has_nlink() const
    { return this->nlink; }
public: /* symbols */
    template <typename t_vdata_t>
    operator t_vdata_t* ()
    { return reinterpret_cast<t_vdata_t*>(this); }
    template <typename t_vdata_t>
    operator const t_vdata_t* () const
    { return reinterpret_cast<const t_vdata_t*>(this); }
    template <typename t_vdata_t>
    operator t_vdata_t& ()
    { return *reinterpret_cast<t_vdata_t*>(this); }
    template <typename t_vdata_t>
    operator const t_vdata_t& () const
    { return *reinterpret_cast<const t_vdata_t*>(this); }
public: /* datadef */
    mlink_t*nlink;
    msize_t msize;
} mlink_t;

} } /* typedef */

#endif/*LIBASIST_MEMO_MLINK_HXX*/
