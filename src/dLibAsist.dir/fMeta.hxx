#ifndef dLibAsistMetaHxx
#define dLibAsistMetaHxx
//headers
#include "fTool.hxx"
#include "fBool.hxx"
#include "fNums.hxx"
//-//standard
#include <functional>
#include <algorithm>
#include <iterator>
//-//-//data
#include <initializer_list>
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
aUseReturned("get next value not equal to the first, or get the last"
) dFuncDefConst auto &fGetNequOrLast(const tVal &rNequ, const tVal &rNext)
{
	return rNext;
}//fGetNotEmpty
template<typename tVal, typename... tArg>
aUseReturned("get next value not equal to the first, or get the last"
) dFuncDefConst
	auto &fGetNequOrLast(const tVal &rNequ, const tVal &rNext, tArg &&...rList)
{
	return rNext == rNequ ? fGetNeq(rNequ, std::forward<tArg>(rList)...) : rNext;
}//fGetNotLast
template<typename tVal, typename tMem>
aUseReturned("get value member directly") dFuncDefConst decltype(auto
) fGetMember(tVal &rVal, tMem tVal::*pMem)
{
	return rVal.*pMem;
}//fGetMember
template<typename tVal, typename tMem, typename... tPaf>
aUseReturned("get value member by path") dFuncDefConst decltype(auto
) fGetMember(tVal &rVal, tMem tVal::*pMem, tPaf &&...rPaf)
{
	return fGetMember(rVal.*pMem, std::forward<tPaf>(rPaf)...);
}//fGetMember
template<typename tVal, typename tTup, nNums::tIndex... cIndexSeq>
aUseReturned("get value member by path encapsulated in a tuple"
) dFuncDefConst decltype(auto
) fGetMember(tVal &rVal, tTup &rTup, std::index_sequence<cIndexSeq...>)
{
	return fGetMember(rVal, std::get<cIndexSeq>(rTup)...);
}//fGetMember
template<typename tVal, typename tTup>
aUseReturned("get value member by path encapsulated in a tuple"
) dFuncDefConst decltype(auto) fGetMember(tVal &rVal, tTup &rTup)
{
	return fGetMember(
		rVal, rTup, std::make_index_sequence<std::tuple_size<tTup>::value>()
	);
}//fGetMember
}//namespace nMeta
}//namespace nLibAsist
#endif//dLibAsistMetaHxx
