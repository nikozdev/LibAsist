#include "../head.hxx"

/* headers */

#include "owner.hxx"

/* content */

#if _LIBASIST_NEWDELDEF
/** new **/
void* operator new(size_t msize)
{
    void*mdata = _NULL;
    size_t malig = alignof(void*);
    if (_NAMESPACE::memo::arena)
    { _NAMESPACE::memo::arena->give(mdata, msize, malig); }
    else { mdata = std::malloc(nums::get_aligned(msize, malig)); }
    auto func_name = _FUNC_NAME, func_sign = _FUNC_SIGN;
#if _LIBASIST_NEWDELDEF_ELOG
    _ELOG("[func_name]=%s;[func_sign]=%s;[msize]=%zu;[malig]=%zu;"
        "%c",
        func_name, func_sign,
        msize, malig,
        _ENDL_SYM
    );
#endif /* _LIBASIST_NEWDELDEF_ELOG */
    return mdata;
}
void* operator new(size_t msize, size_t malig)
{
    void*mdata = _NULL;
    if (_NAMESPACE::memo::arena)
    { _NAMESPACE::memo::arena->give(mdata, msize, malig); }
    else { mdata = std::malloc(nums::get_aligned(msize, malig)); }
    auto func_name = _FUNC_NAME, func_sign = _FUNC_SIGN;
#if _LIBASIST_NEWDELDEF_ELOG
    _ELOG("[func_name]=%s;[func_sign]=%s;[msize]=%zu;[malig]=%zu;"
        "%c",
        func_name, func_sign,
        msize, malig,
        _ENDL_SYM
    );
#endif /* _LIBASIST_NEWDELDEF_ELOG */
    return mdata;
}
void* operator new[](size_t msize)
{
    void*mdata = _NULL;
    size_t malig = alignof(void*);
    if (_NAMESPACE::memo::arena)
    { _NAMESPACE::memo::arena->give(mdata, msize, malig); }
    else
    { mdata = std::malloc(nums::get_aligned(msize, malig)); }
    auto func_name = _FUNC_NAME, func_sign = _FUNC_SIGN;
#if _LIBASIST_NEWDELDEF_ELOG
    _ELOG("[func_name]=%s;[func_sign]=%s;[msize]=%zu;[malig]=%zu;"
        "%c",
        func_name, func_sign,
        msize, malig,
        _ENDL_SYM
    );
#endif /* _LIBASIST_NEWDELDEF_ELOG */
    return mdata;
}
void* operator new[](size_t msize, size_t malig)
{
    void*mdata = _NULL;
    if (_NAMESPACE::memo::arena)
    { _NAMESPACE::memo::arena->give(mdata, msize, malig); }
    else
    { mdata = std::malloc(nums::get_aligned(msize, malig)); }
    auto func_name = _FUNC_NAME, func_sign = _FUNC_SIGN;
#if _LIBASIST_NEWDELDEF_ELOG
    _ELOG("[func_name]=%s;[func_sign]=%s;[msize]=%zu;[malig]=%zu;"
        "%c",
        func_name, func_sign,
        msize, malig,
        _ENDL_SYM
    );
#endif /* _LIBASIST_NEWDELDEF_ELOG */
    return mdata;
}
/** delete **/
void operator delete(void*mdata, size_t msize) noexcept
{
    size_t malig = alignof(void*);
    if (_NAMESPACE::memo::arena)
    { _NAMESPACE::memo::arena->take(mdata, msize, malig); }
    else { std::free(mdata); }
    auto func_name = _FUNC_NAME, func_sign = _FUNC_SIGN;
#if _LIBASIST_NEWDELDEF_ELOG
    _ELOG("[func_name]=%s;[func_sign]=%s;[msize]=%zu;[malig]=%zu;"
        "%c",
        func_name, func_sign,
        msize, malig,
        _ENDL_SYM
    );
#endif /* _LIBASIST_NEWDELDEF_ELOG */
}
void operator delete(void*mdata, size_t msize, size_t malig) noexcept
{
    if (_NAMESPACE::memo::arena)
    { _NAMESPACE::memo::arena->take(mdata, msize, malig); }
    else
    { std::free(mdata); }
    auto func_name = _FUNC_NAME, func_sign = _FUNC_SIGN;
#if _LIBASIST_NEWDELDEF_ELOG
    _ELOG("[func_name]=%s;[func_sign]=%s;[msize]=%zu;[malig]=%zu;"
        "%c",
        func_name, func_sign,
        msize, malig,
        _ENDL_SYM
    );
#endif /* _LIBASIST_NEWDELDEF_ELOG */
}
void operator delete[](void*mdata, size_t msize) noexcept
{
    size_t malig = alignof(void*);
    if (_NAMESPACE::memo::arena)
    { _NAMESPACE::memo::arena->take(mdata, msize, malig); }
    else
    { std::free(mdata); }
    auto func_name = _FUNC_NAME, func_sign = _FUNC_SIGN;
#if _LIBASIST_NEWDELDEF_ELOG
    _ELOG("[func_name]=%s;[func_sign]=%s;[msize]=%zu;[malig]=%zu;"
        "%c",
        func_name, func_sign,
        msize, malig,
        _ENDL_SYM
    );
#endif /* _LIBASIST_NEWDELDEF_ELOG */
}
void operator delete[](void*mdata, size_t msize, size_t malig) noexcept
{
    if (_NAMESPACE::memo::arena)
    { _NAMESPACE::memo::arena->take(mdata, msize, malig); }
    else
    { std::free(mdata); }
    auto func_name = _FUNC_NAME, func_sign = _FUNC_SIGN;
#if _LIBASIST_NEWDELDEF_ELOG
    _ELOG("[func_name]=%s;[func_sign]=%s;[msize]=%zu;[malig]=%zu;"
        "%c",
        func_name, func_sign,
        msize, malig,
        _ENDL_SYM
    );
#endif /* _LIBASIST_NEWDELDEF_ELOG */
}
#endif /* _LIBASIST_NEWDELDEF */
