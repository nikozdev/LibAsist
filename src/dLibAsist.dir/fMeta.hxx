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
//typedef
using tVoid = void;
template<typename tValT>
using tIList = std::initializer_list<tValT>;
/* tTypeDef
 * compile-time meta-type to "typedef ... tType" in itself
 */
template<typename tTypeT>
dTypeDefIline struct tTypeDef
{
	typedef tTypeT tType;
};
/* tTypeDefIfThenOnly
 * compile-time meta-type to "typedef ... tType" in itself
 * "tType" is gonna be defined as "tThenT" only if "cIfT" is 1
 */
template<nBool::tBool cIfT, typename tThenT>
dTypeDefIline struct tTypeDefIfThenOnly
{
	typedef tThenT tType;
};//tTypeDefIfThenOnly<cTruth>
template<typename tThenT>
dTypeDefIline struct tTypeDefIfThenOnly<nBool::cFalse, tThenT>
{
};//tTypeDefIfThenOnly<cFalse>
/* tTypeDefIfThenElse
 * compile-time meta-type to "typedef ... tType" in itself
 * "tType" is "tThenT" if "cIfT" is 1
 * "tElse" is "tThenT" if "cIfT" is 0
 */
template<nBool::tBool cIfT, typename tThenT, typename tElseT = tThenT>
dTypeDefIline struct tTypeDefIfThenElse
{
	typedef tThenT tType;
};//tTypeDefIfThenElse<cTruth>
template<typename tThenT, typename tElseT>
dTypeDefIline struct tTypeDefIfThenElse<nBool::cFalse, tThenT, tElseT>
{
	typedef tElseT tType;
};//tTypeDefSwitch<cFalse>
//actions
template<typename tVal>
aUseReturned("get next value not equal to the first, or get the last"
) dFuncDefConst auto &fGetNequOrLast(const tVal &rNequ, const tVal &rNext)
{
	return rNext;
}//fGetNotEmpty
template<typename tVal, typename... tArg>
aUseReturned("get next value not equal to the first, or get the last"
) dFuncDefConst auto
	&fGetNequOrLast(const tVal &rNequ, const tVal &rNext, tArg &&...rList)
{
	return rNext == rNequ ? fGetNequOrLast(rNequ, std::forward<tArg>(rList)...) : rNext;
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
