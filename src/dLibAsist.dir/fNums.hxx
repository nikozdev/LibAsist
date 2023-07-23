#ifndef dLibAsistNumsHxx
#define dLibAsistNumsHxx
//headers
#include "fTool.hxx"
#include "fBool.hxx"
//-//standard
#include <cmath>
#include <numeric>
#include <cstdint>
#include <limits>
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
// clang-format off
dDataDefConst auto		   cZero			 = 0;
dDataDefConst auto		   cUnit			 = 1;
dDataDefConst auto		   cUnitNeg			 = -1;
dDataDefConst auto		   cUnitPos			 = +1;
dDataDefIline const tCount cNullCountZero	 = cZero;
dDataDefIline const tCount cNullCountUnit	 = cUnit;
dDataDefIline const tCount cNullCountUnitNeg = cUnitNeg;
dDataDefIline const tCount cNullCountUnitPos = cUnitPos;
dDataDefIline const tIndex cNullInDexZero	 = cZero;
dDataDefIline const tIndex cNullInDexUnit	 = cUnit;
dDataDefIline const tIndex cNullInDexUnitNeg = cUnitNeg;
dDataDefIline const tIndex cNullInDexUnitPos = cUnitPos;
dDataDefConst auto		   cMathPi			 = 3.14159;
dDataDefConst auto		   cMathDegFromRad	 = 180.0 / cMathPi;
dDataDefConst auto		   cMathRadFromDeg	 = cMathPi / 180.0;
// clang-format on
//getters
//-//arithmetic
template<typename tNumV, typename tPowV = tNumV, typename tRetV = tNumV>
aUseReturned("get number multiplied by itself <power> times"
) dFuncDefConst tRetV fGetPow(tNumV vNumV, tPowV vPowV)
{
	return std::pow(static_cast<tReal>(vNumV), static_cast<tReal>(vPowV));
}//fGetPow
template<
	nBool::tBool cLower = nBool::cFalse,
	typename tNumT,
	typename tAliT = tNumT,
	typename tRetT = tNumT,
	tCount cSysT   = 2>
aUseReturned("get number aligned to lower or upper level of alignment"
) dFuncDefConst tRetT fGetAli(tNumT vNumT, tAliT vAliT)
{
	static_assert(cSysT == 2, "sorry, i do not support non-binary alignment");
	//align the value
	if constexpr(cLower)
	{
		vNumT -= static_cast<tNumT>(vAliT);
		//prevent underflow for already aligned case (v % a == 0)
		vNumT += 1;
		//get rid of the remainder
		vNumT += (vNumT % vAliT);
	}
	else
	{
		vNumT += static_cast<tNumT>(vAliT);
		//prevent overflow for already aligned case (v % a == 0)
		vNumT -= 1;
		//get rid of the remainder
		vNumT -= (vNumT % vAliT);
	}
	//return whatever type we need (pointer?)
	return reinterpret_cast<tRetT>(vNumT);
}//fGetAli
template<
	typename tNumT,
	typename tAliT = tNumT,
	typename tRetT = tNumT,
	tCount cSysT   = 2>
aUseReturned("get number aligned to lower level of alignment"
) dFuncDefConst tRetT fGetAliLower(tNumT vNumT, tAliT vAliT)
{
	return fGetAli<nBool::cTruth, tNumT, tAliT, tRetT, cSysT>(vNumT, vAliT);
}//fGetAliLower
template<
	typename tNumT,
	typename tAliT = tNumT,
	typename tRetT = tNumT,
	tCount cSysT   = 2>
aUseReturned("get number aligned to upper level of alignment"
) dFuncDefConst tRetT fGetAliUpper(tNumT vNumT, tAliT vAliT)
{
	return fGetAli<nBool::cFalse, tNumT, tAliT, tRetT, cSysT>(vNumT, vAliT);
}//fGetAliUpper
template<typename tDegN, typename tRadN = tDegN>
aUseReturned("convert degrees into radians"
) dFuncDefConst tDegN fGetDegFromRad(tRadN vRadN)
{
	return reinterpret_cast<tDegN>(vRadN * cMathDegFromRad);
}//fGetDegFromRad
template<typename tRadN, typename tDegN = tRadN>
aUseReturned("convert radians into degrees"
) dFuncDefConst tRadN fGetRadFromDeg(tDegN vDegN)
{
	return reinterpret_cast<tRadN>(vDegN * cMathRadFromDeg);
}//fGetRadFromDeg
//-//meta
template<typename tNumV = tIntSM>
aUseReturned("get -1 or +1 out of signed number (+1 for 0 because -128+127)"
) dFuncDefConst auto fGetSign(tNumV vNumV)
{
	static_assert(std::is_signed<tNumV>().value, "sign of unsigned number");
	return vNumV < cZero ? cUnitNeg : cUnitPos;
}//fGetSign
template<typename tNumV>
aUseReturned("get absulute number by getting rid of the sign"
) dFuncDefConst auto fGetAbs(tNumV vNumV)
{
	return vNumV < cZero ? -vNumV : +vNumV;
}//fGetAbs
template<typename tNumV, tCount cSysN = 10>
aUseReturned("get digit count of number"
) dFuncDefConst auto fGetCount(tNumV vNumV)
{
	static_assert((cSysN > cUnit), "numeric system with 1 digit or less");
	tCount vCount = cZero;
	vNumV		  = fGetAbs(vNumV);
	while(vNumV > 0)
	{
		vNumV /= cSysN;
		vCount += 1;
	}
	return vCount;
}//fGetCount
template<typename tNumV = tIntSM, tCount cSysN = 10>
aUseReturned("get digit on position from left"
) dFuncDefConst tNumV fGetFromL(tNumV vNumV, tIndex vPosI)
{
	static_assert((cSysN > 1), "numeric system with 1 digit or less");
	vNumV = fGetAbs(vNumV);
	return (vNumV / fGetPow(cSysN, fGetCount(vNumV) - vPosI)) % cSysN;
}//fGetSideL
template<typename tNumV = tIntSM, tCount cSysN = 10>
aUseReturned("get digit on position from right"
) dFuncDefConst tNumV fGetFromR(tNumV vNumV, tIndex vPosI)
{
	static_assert((cSysN > 1), "numeric system with 1 digit or less");
	vNumV = fGetAbs(vNumV);
	return (vNumV / fGetPow(cSysN, vPosI - 1)) % cSysN;
}//fGetFromR
//-//transformation
template<typename tNumV, tCount cSysN = 10>
aUseReturned("reverse a number from right to left"
) dFuncDefConst tNumV fGetRev(tNumV vNumV)
{
	static_assert((cSysN > cUnit), "numeric system with 1 digit or less");
	tNumV vRevN = 0;
	tNumV vSign = fGetSign(vNumV);
	vNumV		= fGetAbs(vNumV);
	while(vNumV > cSysN)
	{
		vRevN += vNumV % cSysN;
		vRevN *= cSysN;
		vNumV /= cSysN;
	}
	vRevN += vNumV % cSysN;
	vNumV /= cSysN;
	return vRevN * vSign;
}//fGetRev
//-//relation
template<typename tNumL, typename tNumR = tNumL, typename tRetV = tNumL>
aUseReturned("get minimum of 2 values with any type"
) dFuncDefConst tRetV fGetMin(tNumL vNumL, tNumR vNumR)
{
	return std::min(static_cast<tRetV>(vNumL), static_cast<tRetV>(vNumR));
}//fGetMin
template<typename tNumL, typename tNumR = tNumL, typename tRetV = tNumL>
aUseReturned("get maximum of 2 values with any type"
) dFuncDefConst tRetV fGetMax(tNumL vNumL, tNumR vNumR)
{
	return std::max(static_cast<tRetV>(vNumL), static_cast<tRetV>(vNumR));
}//fGetMax
template<typename tNumT, typename tMinT, typename tMaxT, typename tRetT = tNumT>
aUseReturned("get rectangular linear unit"
) dFuncDefConst tRetT fGetISide(tNumT vNum, tMinT vMin, tMaxT vMax)
{
	return fGetMin(fGetMax(vMin, vNum), vMax);
}//fGetClam
template<typename tNumT, typename tRetT = tNumT>
aUseReturned("get rectangular linear unit"
) dFuncDefConst tRetT fGetRelu(tNumT vNumV)
{
	return fGetISide(vNumV, 0, 1);
}//fGetRelu
template<typename tNumV, typename tNumL = tNumV, typename tNumR = tNumL>
aUseReturned("check if a number is inside of boundaries"
) dFuncDefConst nBool::tBool fVetISide(tNumV vNumV, tNumL vNumL, tNumR vNumR)
{
	return (vNumV >= vNumL) && (vNumR >= vNumV);
}//fVetISide
template<typename tNumV, typename tNumL = tNumV, typename tNumR = tNumL>
aUseReturned("check if a number is inside of boundaries"
) dFuncDefConst nBool::tBool fVetOSide(tNumV vNumV, tNumL vNumL, tNumR vNumR)
{
	return (vNumV < vNumL) || (vNumR > vNumV);
}//fVetOSide
}//namespace nNums
}//namespace nLibAsist
#endif//dLibAsistNumsHxx
