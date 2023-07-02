#ifndef LIBASIST_MEMO_HXX
#define LIBASIST_MEMO_HXX 1

#include "head.hxx"

/* headers */

#include "memo/giver.hxx"
#include "memo/taker.hxx"
#include "memo/owner.hxx"
#include "memo/stack.hxx"
#include "memo/arena.hxx"
#include "memo/pager.hxx"
#include "memo/refer.hxx"

/* content */

namespace libasist { namespace memo { /* actions */

[[maybe_unused]] inline
bool_t init()
{
    if (heapy_t::basic) { return FALSE; }
    else
    {
        heapy_t::basic = new(
            std::malloc(nums::get_aligned<heapy_t>())
        )heapy_t();
    }
    if (stack_t::basic) { return FALSE; }
    else
    {
        stack_t::basic = new(
            std::malloc(nums::get_aligned<stack_t>())
        )stack_t(stack_t::MSIZE, heapy_t::basic);
    }
    if (arena_t::basic) { return FALSE; }
    else
    {
        arena_t::basic = new(
            std::malloc(nums::get_aligned<arena_t>())
        )arena_t(arena_t::MSIZE, heapy_t::basic);
    }
    if (pager_t::basic) { return FALSE; }
    else
    {
        pager_t::basic = new(
            std::malloc(nums::get_aligned<pager_t>())
        )pager_t(pager_t::MSIZE, heapy_t::basic);
    }
    return TRUTH;
}
[[maybe_unused]] inline
bool_t quit()
{
    if (pager_t::basic)
    {
        pager_t::basic->~pager_t();
        std::free(pager_t::basic);
        pager_t::basic = NULL;
    }
    else { return FALSE; }
    if (arena_t::basic)
    {
        arena_t::basic->~arena_t();
        std::free(arena_t::basic);
        arena_t::basic = NULL;
    }
    else { return FALSE; }
    if (stack_t::basic)
    {
        stack_t::basic->~stack_t();
        std::free(stack_t::basic);
        stack_t::basic = NULL;
    }
    else { return FALSE; }
    if (heapy_t::basic)
    {
        heapy_t::basic->~heapy_t();
        std::free(heapy_t::basic);
        heapy_t::basic = NULL;
    }
    else { return FALSE; }
    return TRUTH;
}

} } /* actions */

#endif/*LIBASIST_MEMO_HXX*/
