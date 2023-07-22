#ifndef dLibAsistHeadNumsHxx
#define dLibAsistHeadNumsHxx
//headers
#include "fBool.hxx"
//-//standard
#include <cmath>
#include <numeric>
#include <cstdint>
//content
namespace nLibAsist
{
namespace nNums
{
//typedef
//-//integral
//-//-//unsigned
using tIntU1 = uint8_t; //type of integer unsigned with 1 byte size
using tIntU2 = uint16_t;//type of integer unsigned with 2 byte size
using tIntU4 = uint32_t;//type of integer unsigned with 4 byte size
using tIntU8 = uint64_t;//type of integer unsigned with 8 byte size
using tIntUM = unsigned;//type of integer unsigned main
using tIntU	 = tIntUM;	//type of integer unsigned
//-//-//signed
using tIntS1 = int8_t; //type of integer signed with 1 byte size
using tIntS2 = int16_t;//type of integer signed with 2 byte size
using tIntS4 = int32_t;//type of integer signed with 4 byte size
using tIntS8 = int64_t;//type of integer signed with 8 byte size
using tIntSM = signed; //type of integer signed main
using tIntS	 = tIntSM; //type of integer signed
//-//-//main
using tIndex = tIntS4;//type of identifier number
using tCount = tIntU4;//type of quantity number
//-//size
using tSizeU = size_t; //type of size unsigned
using tSizeS = ssize_t;//type of size signed
using tSizeM = size_t; //type of size main
using tSize	 = tSizeM; //type of size
//-//step
using tStepU = tSizeU;//type of step unsigned
using tStepS = tSizeS;//type of step signed
using tStepM = tSizeM;//type of step main
using tStep	 = tSize; //type of step
//-//fractional
using tReal4 = float; //type of fractional number with 4 byte size
using tReal8 = double;//type of fractional number with 8 byte size
using tRealM = float; //type of fractional number main
using tReal	 = tRealM;//type of fractional number
//consdef
constexpr auto		cZero			  = 0;		 //0
constexpr auto		cUnit			  = 1;		 //1
constexpr auto		cUnitNeg		  = -1;		 //-1
constexpr auto		cUnitPos		  = +1;		 //+1
inline const tCount cNullCountZero	  = cZero;	 //null object count 0
inline const tCount cNullCountUnit	  = cUnit;	 //null object count 1
inline const tCount cNullCountUnitNeg = cUnitNeg;//null object count -1
inline const tCount cNullCountUnitPos = cUnitPos;//null object count +1
inline const tIndex cNullIndexZero	  = cZero;	 //null object index 0
inline const tIndex cNullIndexUnit	  = cUnit;	 //null object count 1
inline const tIndex cNullIndexUnitNeg = cUnitNeg;//null object count -1
inline const tIndex cNullIndexUnitPos = cUnitPos;//null object count +1
constexpr auto		cMathPi			  = 3.14159;
constexpr auto		cMathDegFromRad	  = 180.0 / cMathPi;
constexpr auto		cMathRadFromDeg	  = cMathPi / 180.0;
//getters
//-//arithmetic
template<typename tNumV, typename tPowV>
[[nodiscard("get number multiplied by itself <power> times")]]
inline constexpr auto fGetPow(tNumV vNumV, tPowV vPowV)
{
	return std::pow(vNumV, vPowV);
}//fGetPow
template<
	nBool::tBool cLower = nBool::cFalse,
	typename tRetV,
	typename tNumV,
	typename tAliV,
	tCount cSysN = 2>
[[nodiscard("get number aligned to lower or upper level of alignment")]]
constexpr tRetV fGetAli(tNumV vNumV, tAliV vAliV)
{
	static_assert(cSysN == 2, "sorry, i do not support non-binary alignment");
	//align the value
	if constexpr(cLower)
	{
		vNumV -= static_cast<tNumV>(vAliV);
		//prevent underflow for already aligned case (v % a == 0)
		vNumV += 1;
		//get rid of the remainder
		vNumV += (vNumV % vAliV);
	}
	else
	{
		vNumV += static_cast<tNumV>(vAliV);
		//prevent overflow for already aligned case (v % a == 0)
		vNumV -= 1;
		//get rid of the remainder
		vNumV -= (vNumV % vAliV);
	}
	//return whatever type we need (pointer?)
	return reinterpret_cast<tRetV>(vNumV);
}//fGetAli
template<typename tRetT, typename tNumV, typename tAliV, tCount cSysN = 2>
[[nodiscard("get number aligned to lower level of alignment")]]
constexpr tRetT fGetAliLower(tNumV vNumV, tAliV vAliV)
{
	return fGetAli<nBool::cTruth, tRetT, tNumV, tAliV, cSysN>(vNumV, vAliV);
}//fGetAliLower
template<typename tRetT, typename tNumV, typename tAliV, tCount cSysN = 2>
[[nodiscard("get number aligned to upper level of alignment")]]
constexpr tRetT fGetAliUpper(tNumV vNumV, tAliV vAliV)
{
	return fGetAli<nBool::cFalse, tRetT, tNumV, tAliV>(vNumV, vAliV);
}//fGetAliUpper
template<typename tDegN, typename tRadN>
[[nodiscard("convert degrees into radians")]]
constexpr tDegN fGetDegFromRad(tRadN vRadN)
{
	return reinterpret_cast<tDegN>(vRadN * cMathDegFromRad);
}//fGetDegFromRad
template<typename tDegN, typename tRadN>
[[nodiscard("convert radians into degrees")]]
constexpr tRadN fGetRadFromDeg(tDegN vDegN)
{
	return reinterpret_cast<tRadN>(vDegN * cMathRadFromDeg);
}//fGetRadFromDeg
//-//meta
template<typename tNumV = tIntSM>
[[nodiscard("get -1 or +1 out of signed number (+1 for 0 because -128+127)")]]
inline constexpr auto fGetSign(tNumV vNumV)
{
	static_assert(std::is_signed<tNumV>().value, "sign of unsigned number");
	return vNumV < cZero ? cUnitNeg : cUnitPos;
}//fGetSign
template<typename tNumV, tCount cSysN = 10>
[[nodiscard("get digit count of number")]]
inline constexpr auto fGetCount(tNumV vNumV)
{
	static_assert((cSysN > cUnit), "numeric system with 1 digit or less");
	tCount vCount = cZero;
	while(vNumV > 0)
	{
		vNumV /= cSysN;
		vCount += 1;
	}
	return vCount;
}//fGetCount
template<typename tNumV = tIntSM, tCount cSysN = 10>
[[nodiscard("get digit on position from left")]]
inline constexpr tNumV fGetFromL(tNumV vNumV, tIndex vPosI)
{
	static_assert((cSysN > 1), "numeric system with 1 digit or less");
	return vNumV % fGetPower<tNumV>(cSysN, vPosI + 1)
		 / fGetPow<tNumV>(cSysN, vPosI - 1);
}//fGetSideL
template<typename tNumV = tIntSM, tCount cSysN = 10>
[[nodiscard("get digit on position from right")]]
inline constexpr tNumV fGetFromR(tNumV vNumV, tIndex vPosI)
{
	static_assert((cSysN > 1), "numeric system with 1 digit or less");
	return vNumV / fGetPower<tNumV>(cSysN, vPosI - 1) % cSysN;
}//fGetFromR
//-//transformation
template<typename tNumV, tCount cSysN = 10>
[[nodiscard("reverse a number from right to left")]]
inline constexpr tNumV fGetRev(tNumV vNumV)
{
	static_assert((cSysN > cUnit), "numeric system with 1 digit or less");
	tNumV vRevN = 0;
	while(vNumV > cSysN)
	{
		vRevN += vNumV % cSysN;
		vRevN *= cSysN;
		vNumV /= cSysN;
	}
	vRevN += vNumV % cSysN;
	vNumV /= cSysN;
	return vRevN;
}//fGetRev
//-//relation
template<typename tNumL, typename tNumR = tNumL, typename tRetV = tNumL>
[[nodiscard("get minimum of 2 values with any type")]]
inline constexpr tRetV fGetMin(tNumL vNumL, tNumR vNumR)
{
	return std::min(static_cast<tRetV>(vNumL), static_cast<tRetV>(vNumR));
}//fGetMin
template<typename tNumL, typename tNumR = tNumL, typename tRetV = tNumL>
[[nodiscard("get maximum of 2 values with any type")]]
inline constexpr tRetV fGetMax(tNumL vNumL, tNumR vNumR)
{
	return std::max(static_cast<tRetV>(vNumL), static_cast<tRetV>(vNumR));
}//fGetMax
template<typename tNumV, typename tNumL = tNumV, typename tNumR = tNumL>
[[nodiscard("check if a number is inside of boundaries")]]
inline constexpr nBool::tBool fVetISide(tNumV vNumV, tNumL vNumL, tNumR vNumR)
{
	return (vNumV >= vNumL) && (vNumR >= vNumV);
}//fVetISide
template<typename tNumV, typename tNumL, typename tNumR>
[[nodiscard("check if a number is inside of boundaries")]]
inline constexpr nBool::tBool fVetOSide(tNumV vNumV, tNumL vNumL, tNumR vNumR)
{
	return (vNumV < vNumL) || (vNumR > vNumV);
}//fVetOSide
}//namespace nNums
}//namespace nLibAsist
#endif//dLibAsistHeadNumsHxx
