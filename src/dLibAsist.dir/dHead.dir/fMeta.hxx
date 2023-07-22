#ifndef dLibAsistHeadMetaHxx
#define dLibAsistHeadMetaHxx
//headers
#include "fBool.hxx"
#include "fNums.hxx"
//-//standard
#include <functional>
#include <algorithm>
#include <iterator>
//-//-//data
#include <initializer_list>
#include <list>
#include <array>
#include <vector>
#include <map>
#include <unordered_map>
//-//-//type
#include <type_traits>
//content
namespace nLibAsist
{
namespace nMeta
{
using tVoid = void;
template<typename tValT>
using tListI = std::initializer_list<tValT>;//list-initializer template type
//actions
template<typename tVal>
[[nodiscard("get next value not equal to the first, or get the last")]]
inline constexpr const tVal &fGetNequOrLast(const tVal &rNequ, const tVal &rNext)
{
	return rNext;
}//fGetNotEmpty
template<typename tVal, typename... tArg>
[[nodiscard("get next value not equal to the first, or get the last")]]
inline constexpr const tVal &
fGetNequOrLast(const tVal &rNequ, const tVal &rNext, tArg &&...rList)
{
	return rNext == rNequ ? fGetNeq(rNequ, std::forward<tArg>(rList)...) : rNext;
}//fGetNotLast
template<typename tVal, typename tMem>
[[nodiscard("get value member directly")]]
inline constexpr decltype(auto) fGetMember(tVal &rVal, tMem tVal::*pMem)
{
	return rVal.*pMem;
}//fGetMember
template<typename tVal, typename tMem, typename... tPaf>
[[nodiscard("get value member by path")]]
inline constexpr decltype(auto
) fGetMember(tVal &rVal, tMem tVal::*pMem, tPaf &&...rPaf)
{
	return fGetMember(rVal.*pMem, std::forward<tPaf>(rPaf)...);
}//fGetMember
template<typename tVal, typename tTup, nNums::tIndex... cIndexSeq>
[[nodiscard("get value member by path encapsulated in a tuple")]]
inline constexpr decltype(auto
) fGetMember(tVal &rVal, tTup &rTup, std::index_sequence<cIndexSeq...>)
{
	return fGetMember(rVal, std::get<cIndexSeq>(rTup)...);
}//fGetMember
template<typename tVal, typename tTup>
[[nodiscard("get value member by path encapsulated in a tuple")]]
inline constexpr decltype(auto) fGetMember(tVal &rVal, tTup &rTup)
{
	return fGetMember(
		rVal, rTup, std::make_index_sequence<std::tuple_size<tTup>::value>()
	);
}//fGetMember
}//namespace nMeta
}//namespace nLibAsist
#endif//dLibAsistHeadMetaHxx
