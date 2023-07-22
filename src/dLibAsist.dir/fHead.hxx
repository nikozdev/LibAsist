#ifndef dLibAsistHeadHxx
#define dLibAsistHeadHxx
//configs
#ifndef dOsys
#if defined(__unix__) || defined(__APPLE__)
#define dOsysPosix
#if defined(__linux__)
#define dOsysLinux
#endif//ifd(__linux__)
#if defined(__APPLE__)
#define dOsysApple
#if defined(_TARGET_OS_MAC)
#define dOsysMacos
#endif//ifd(_TARGET_OS_MAC)
#endif//ifd(__APPLE__)
#endif//ifd(__unix__)
#if defined(_WIN32) || defined(_WIN64)
#define dOsysWinos
#endif//ifd(_WIN32) || defined(_WIN64)
#define dOsys
#endif//dOsys
#ifndef dTool
#if defined(__GNUC__) || defined(__GNUG__)
#if defined(__clang__)
#define dToolClang
#else
#define dToolGnucc
#endif//ifd(__clang__)
#endif//ifd(__GNUC__) || defined(__GNUG__)
#if defined(_MSC_VER)
#define dToolMsvcc
#endif//ifd(_MSC_VER)
#define dTool
#endif//dTool
#if defined(dLibAsistProjConfWork) || 1
//5-10% performance difference for me
#define dLibAsistMemoMSizeSet
//10-20% performance difference for me
#define dLibAsistMemoMSizeVet
#define dLibAsistMemoMDataVet
//most of the times this is gonna break memory allocations
#define dLibAsistMemoNewDelDef
#define dLibAsistMemoNewDelDefElog
#endif//ifd(dLibAsistProjConfWork)
//headers
#ifndef dOsys
#error "dOsys is not defined"
#elif(defined(dOsysPosix))
#include <unistd.h>
#endif//dOsys
//-//standard
#include <cstdlib>
#include <cstddef>
//-//-//help
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
//-//-//numeric
#include <cmath>
#include <numeric>
#include <cstdint>
//-//-//memory
#include <new>
#include <memory>
//-//-//string
#include <string>
#include <cstring>
#include <string_view>
#include <sstream>
#include <format>
//-//-//time
#include <ctime>
//-//-//ipop
#include <cstdio>
#include <iostream>
#ifndef dTool
#error "dTool is undefined"
#elif(defined(dToolClang) || defined(dToolMsvcc))
#include <filesystem>
namespace nLibAsist
{//imports
namespace nFileSys = std::filesystem;
}//namespace nLibAsist
#elif(defined(dToolGnucc))
#include <experimental/bits/fs_fwd.h>
#include <experimental/bits/fs_path.h>
#include <experimental/bits/fs_dir.h>
#include <experimental/bits/fs_ops.h>
namespace nLibAsist
{//imports
namespace nFileSys = std::experimental::filesystem;
}//namespace nLibAsist
#endif//ifd(dToolGnucc)
#include <fstream>
//-//execution
#include <csignal>
#include <thread>
//defines
//-//string
#ifndef fGetStrFromArg
#define fGetStrFromArg(str) #str
#endif//fGetStrFromArg
//-//meta
#ifdef dMeta
#ifndef fMetaEnumActNum
#define fMetaEnumActNum(vKey, vNum, vStr) e##vKey = vNum,
#endif//fMetaEnumActNum
#ifndef fMetaEnumActStr
#define fMetaEnumActStr(vKey, vNum, vStr) [e##vKey] = vStr,
#endif//fMetaEnumActStr
#ifndef fMetaEnumDef
#define fMetaEnumDef(eName, fFor)                       \
	enum e##eName : signed{                             \
		fFor(fMetaEnumActNum) e##eName##Last,           \
	};                                                  \
	constexpr const char *v##eName##Text[] = {          \
		fFor(fMetaEnumActStr)[e##eName##Last] = "last", \
	};
#endif//fMetaEnumDef
#endif//dMeta
//-//ipop
#ifndef fOput
#define fOput(...)                                                            \
	{                                                                         \
		std::format_to(                                                       \
			std::ostream_iterator<decltype(std::cout)::char_type>(std::cout), \
			__VA_ARGS__                                                       \
		);                                                                    \
	}
#endif//fOput
#ifndef fOlog
#define fOlog(...)                        \
	{                                     \
		fOput(                            \
			"[from]{:s}"                  \
			"[file]{:s}"                  \
			"[func]{:s}"                  \
			"[line]{:d}"                  \
			"[mesg]{:c}{:s}{:c}",         \
                                          \
			"olog",                       \
			dFileName,                    \
			dFuncName,                    \
			dFileLine,                    \
			::LibAsist::nText::cEndlChar, \
			std::format(__VA_ARGS__),     \
			::LibAsist::nText::cEndlChar  \
		);                                \
	}
#endif//fOlog
#ifndef fEput
#define fEput(...)                                                            \
	{                                                                         \
		std::format_to(                                                       \
			std::ostream_iterator<decltype(std::cerr)::char_type>(std::cout), \
			__VA_ARGS__                                                       \
		);                                                                    \
	}
#endif//fEput
#ifndef fElog
#define fElog(...)                        \
	{                                     \
		fEput(                            \
			"[from]{:s}"                  \
			"[file]{:s}"                  \
			"[func]{:s}"                  \
			"[line]{:d}"                  \
			"[mesg]{:c}{:s}{:c}",         \
                                          \
			"elog",                       \
			dFileName,                    \
			dFuncName,                    \
			dFileLine,                    \
			::LibAsist::nText::cEndlChar, \
			std::format(__VA_ARGS__),     \
			::LibAsist::nText::cEndlChar  \
		);                                \
	}
#endif//fElog
//-//dbug
#ifndef dFileName
#define dFileName __FILE__
#endif//dFileName
#ifndef dFileLine
#define dFileLine __LINE__
#endif//dFileLine
#ifndef dFuncName
#define dFuncName __FUNCTION__
#endif//dFuncName
#ifndef dFuncSign
#define dFuncSign __PRETTY_FUNCTION__
#endif//dFuncSign
#ifndef fError
#define fError(vCode, vActn, vArgs...)     \
	({                                     \
		fElog(vArgs);                      \
		::LibAsist::nDbug::breakpoint();   \
		::LibAsist::nDbug::vECode = vCode; \
		vActn;                             \
	})
#endif//fError - raise an error signal
#ifndef fEfnot
#define fEfnot(vExpr, vActn, vArgs...) \
	({                                 \
		if((vExpr) == 0)               \
		{                              \
			fError(1, vActn, vArgs);   \
		}                              \
	})
#endif//fEfnot - error if not
#ifndef fPcall
#define fPcall(vExec, vActn, ...)              \
	({                                         \
		vExec;                                 \
		fEfnot(                                \
			::LibAsist::nDbug::vECode == 0,    \
			{                                  \
				vActn;                         \
				::LibAsist::nDbug::vECode = 0; \
			},                                 \
			__VA_ARGS__                        \
		);                                     \
	})
#endif//fPcall - protected call
//content
namespace nLibAsist
{
//typedef
using tVoid = void;
template<typename tValT>
using tListI = std::initializer_list<tValT>;//list-initializer template type
namespace nBool
{
//consdef
constexpr auto cTruth = true;
constexpr auto cFalse = false;
//typedef
using tBool = bool;
using tFlag = bool;
}//namespace nBool
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
namespace nMemo
{
//typedef
//-//byte
using tByteU = unsigned char;//type of byte unsigned
using tByteS = signed char;	 //type of byte signed
using tByteM = char;		 //type of byte main
using tByte	 = tByteM;		 //type of byte
//-//data
using tDataA = void *;	//type of data abstract
using tDataU = tByteU *;//type of data unsigned
using tDataS = tByteS *;//type of data signed
using tDataM = tByteM *;//type of data main
using tData	 = tByte *; //type of data
//consdef
constexpr auto	  cNull		= nullptr;//null pointer constant
inline const auto cNullData = cNull;  //null object pointer
}//namespace nMemo
// clang-format off
namespace nMeta
{
//enumdef
#ifdef dMeta
#ifndef fMetaEnumForError
#define fMetaEnumForError(fAct)                            \
	fAct(ErrorNone, 0x00, "none error")                    \
	fAct(ErrorArgc, 0x01, "invalid argument count")        \
	fAct(ErrorArgv, 0x02, "invalid argument value")        \
	fAct(ErrorComd, 0x03, "invalid command")               \
	fAct(ErrorOpts, 0x04, "invalid options")               \
	fAct(ErrorConf, 0x05, "invalid configuration")         \
	fAct(ErrorEvar, 0x06, "invalid environment variable")  \
	fAct(ErrorProc, 0x07, "run-time error in the process") \
//fMetaEnumForError
fMetaEnumDef(Error, fMetaEnumForError)
#endif//fMetaEnumForError
#ifndef fMetaEnumForTimeZone
#define fMetaEnumForTimeZone(fAct)          \
	fAct(TimeZoneNone,  0x0, "none time")   \
	fAct(TimeZoneLocal, 0x1, "local time")  \
	fAct(TimeZoneGmt,   0x2, "global time") \
//fMetaEnumForTimeZone
	fMetaEnumDef(TimeZone, fMetaEnumForTimeZone)
#endif//fMetaEnumForTimeZone
#ifndef fMetaEnumForFileFormat
#define fMetaEnumForFileFormat(fAct)    \
	fAct(FileFormatBin,    0x0, "bin")  \
	fAct(FileFormatConfig, 0x1, "cfg")  \
//fMetaEnumForFileFormat
fMetaEnumDef(FileFormat, fMetaEnumForFileFormat)
#endif//fMetaEnumForFileFormat
#ifndef fMetaEnumForAscii
#define fMetaEnumForAscii(fAct)                     \
	/*control*/                                     \
	fAct(Ascii_nul, 0x00, "zero terminator")        \
	fAct(Ascii_soh, 0x01, "soh ?")                  \
	fAct(Ascii_stx, 0x02, "stx ?")                  \
	fAct(Ascii_etx, 0x03, "etx ?")                  \
	fAct(Ascii_eot, 0x04, "eot ?")                  \
	fAct(Ascii_enq, 0x05, "enq ?")                  \
	fAct(Ascii_ack, 0x06, "ack ?")                  \
	fAct(Ascii_bel, 0x07, "bell sound")             \
	fAct(Ascii_bs, 0x08, "backspace")               \
	fAct(Ascii_ht, 0x09, "horizontal tab")          \
	fAct(Ascii_nl, 0x0a, "new line")                \
	fAct(Ascii_vt, 0x0b, "vertical tab")            \
	fAct(Ascii_np, 0x0c, "np ?")                    \
	fAct(Ascii_cr, 0x0d, "cariage return")          \
	fAct(Ascii_so, 0x0e, "so ?")                    \
	fAct(Ascii_si, 0x0f, "si ?")                    \
	fAct(Ascii_dle, 0x10, "dle ?")                  \
	fAct(Ascii_dc1, 0x11, "dc1 ?")                  \
	fAct(Ascii_dc2, 0x12, "dc2 ?")                  \
	fAct(Ascii_dc3, 0x13, "dc3 ?")                  \
	fAct(Ascii_dc4, 0x14, "dc4 ?")                  \
	fAct(Ascii_nak, 0x15, "nak ?")                  \
	fAct(Ascii_syn, 0x16, "syn ?")                  \
	fAct(Ascii_etb, 0x17, "etb ?")                  \
	fAct(Ascii_can, 0x18, "can ?")                  \
	fAct(Ascii_em, 0x19, "em ?")                    \
	fAct(Ascii_sub, 0x1a, "sub ?")                  \
	fAct(Ascii_esc, 0x1b, "escape")                 \
	fAct(Ascii_fs, 0x1c, "fs ?")                    \
	fAct(Ascii_gs, 0x1d, "gs ?")                    \
	fAct(Ascii_rs, 0x1e, "rs ?")                    \
	fAct(Ascii_us, 0x1f, "us ?")                    \
	/*visible*/                                     \
	fAct(Ascii_sp, 0x20, "space")                   \
	fAct(Ascii_exs, 0x21, "exclamation-sign")       \
	fAct(Ascii_dqt, 0x22, "double-quote")           \
	fAct(Ascii_hash, 0x23, "hash-symbol")           \
	fAct(Ascii_cash, 0x24, "dollar-sign")           \
	fAct(Ascii_perc, 0x25, "percent-sign")          \
	fAct(Ascii_ands, 0x26, "and-sign or ampersand") \
	fAct(Ascii_sqt, 0x27, "single-quote")           \
	fAct(Ascii_lrb, 0x28, "left-round-bracket")     \
	fAct(Ascii_rrb, 0x29, "right-roud-bracket")     \
	fAct(Ascii_star, 0x2a, "asterisk")              \
	fAct(Ascii_add, 0x2b, "plus")                   \
	fAct(Ascii_com, 0x2c, "comma")                  \
	fAct(Ascii_min, 0x2d, "minus")                  \
	fAct(Ascii_dot, 0x2e, "dot")                    \
	fAct(Ascii_fsl, 0x2f, "forward-slash")          \
	fAct(Ascii_n0, 0x30, "number-zero")             \
	fAct(Ascii_n1, 0x31, "number-one")              \
	fAct(Ascii_n2, 0x32, "number-two")              \
	fAct(Ascii_n3, 0x33, "number-three")            \
	fAct(Ascii_n4, 0x34, "number-four")             \
	fAct(Ascii_n5, 0x35, "number-five")             \
	fAct(Ascii_n6, 0x36, "number-six")              \
	fAct(Ascii_n7, 0x37, "number-seven")            \
	fAct(Ascii_n8, 0x38, "number-eight")            \
	fAct(Ascii_n9, 0x39, "number-nine")             \
	fAct(Ascii_col, 0x3a, "colon")                  \
	fAct(Ascii_scol, 0x3b, "semi-colon")            \
	fAct(Ascii_lts, 0x3c, "less-than-sign")         \
	fAct(Ascii_ets, 0x3d, "equal-to-sign")          \
	fAct(Ascii_mts, 0x3e, "more-than-sign")         \
	fAct(Ascii_qus, 0x3f, "question-sign")          \
	fAct(Ascii_at, 0x40, "at-sign")                 \
	fAct(Ascii_A, 0x41, "capital-letter-a")         \
	fAct(Ascii_B, 0x42, "capital-letter-b")         \
	fAct(Ascii_C, 0x43, "capital-letter-c")         \
	fAct(Ascii_D, 0x44, "capital-letter-d")         \
	fAct(Ascii_E, 0x45, "capital-letter-e")         \
	fAct(Ascii_F, 0x46, "capital-letter-f")         \
	fAct(Ascii_G, 0x47, "capital-letter-g")         \
	fAct(Ascii_H, 0x48, "capital-letter-h")         \
	fAct(Ascii_I, 0x49, "capital-letter-i")         \
	fAct(Ascii_J, 0x4a, "capital-letter-j")         \
	fAct(Ascii_K, 0x4b, "capital-letter-k")         \
	fAct(Ascii_L, 0x4c, "capital-letter-l")         \
	fAct(Ascii_M, 0x4d, "capital-letter-m")         \
	fAct(Ascii_N, 0x4e, "capital-letter-n")         \
	fAct(Ascii_O, 0x4f, "capital-letter-o")         \
	fAct(Ascii_P, 0x50, "capital-letter-p")         \
	fAct(Ascii_Q, 0x51, "capital-letter-q")         \
	fAct(Ascii_R, 0x52, "capital-letter-r")         \
	fAct(Ascii_S, 0x53, "capital-letter-s")         \
	fAct(Ascii_T, 0x54, "capital-letter-t")         \
	fAct(Ascii_U, 0x55, "capital-letter-u")         \
	fAct(Ascii_V, 0x56, "capital-letter-v")         \
	fAct(Ascii_W, 0x57, "capital-letter-w")         \
	fAct(Ascii_X, 0x58, "capital-letter-x")         \
	fAct(Ascii_Y, 0x59, "capital-letter-y")         \
	fAct(Ascii_Z, 0x5a, "capital-letter-z")         \
	fAct(Ascii_lsb, 0x5b, "left-square-bracket")    \
	fAct(Ascii_bsl, 0x5c, "backward-slash")         \
	fAct(Ascii_rsb, 0x5d, "right-square-bracket")   \
	fAct(Ascii_car, 0x5e, "carret")                 \
	fAct(Ascii_usco, 0x5f, "underscore")            \
	fAct(Ascii_apos, 0x60, "apostrophe")            \
	fAct(Ascii_a, 0x61, "letter-a")                 \
	fAct(Ascii_b, 0x62, "letter-b")                 \
	fAct(Ascii_c, 0x63, "letter-c")                 \
	fAct(Ascii_d, 0x64, "letter-d")                 \
	fAct(Ascii_e, 0x65, "letter-e")                 \
	fAct(Ascii_f, 0x66, "letter-f")                 \
	fAct(Ascii_g, 0x67, "letter-g")                 \
	fAct(Ascii_h, 0x68, "letter-h")                 \
	fAct(Ascii_i, 0x69, "letter-i")                 \
	fAct(Ascii_j, 0x6a, "letter-j")                 \
	fAct(Ascii_k, 0x6b, "letter-k")                 \
	fAct(Ascii_l, 0x6c, "letter-l")                 \
	fAct(Ascii_m, 0x6d, "letter-m")                 \
	fAct(Ascii_n, 0x6e, "letter-n")                 \
	fAct(Ascii_o, 0x6f, "letter-o")                 \
	fAct(Ascii_p, 0x70, "letter-p")                 \
	fAct(Ascii_q, 0x71, "letter-q")                 \
	fAct(Ascii_r, 0x72, "letter-r")                 \
	fAct(Ascii_s, 0x73, "letter-s")                 \
	fAct(Ascii_t, 0x74, "letter-t")                 \
	fAct(Ascii_u, 0x75, "letter-u")                 \
	fAct(Ascii_v, 0x76, "letter-v")                 \
	fAct(Ascii_w, 0x77, "letter-w")                 \
	fAct(Ascii_x, 0x78, "letter-x")                 \
	fAct(Ascii_y, 0x79, "letter-y")                 \
	fAct(Ascii_z, 0x7a, "letter-z")                 \
	fAct(Ascii_lcub, 0x7b, "left-curly-bracket")    \
	fAct(Ascii_vbar, 0x7c, "vertical-bar")          \
	fAct(Ascii_rcub, 0x7d, "right-curly-bracket")   \
	fAct(Ascii_tld, 0x7e, "tilde")                  \
	fAct(Ascii_del, 0x7f, "delete")                 \
//fMetaEnumForAscii
fMetaEnumDef(Ascii, fMetaEnumForAscii)
#endif//fMetaEnumForAscii
#endif//dMeta
namespace {}
// clang-format on
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
namespace nText
{
//aliases
using tSize = nNums::tSize;
//-//character
using tCharU = unsigned char;//type of character unsigned
using tCharS = signed char;	 //type of character signed
using tCharW = wchar_t;		 //type of character wide
using tCharM = char;		 //type of character main
using tChar	 = tCharM;		 //type of character
//-//data
using tDataU = tChar *; //type of character data unsigned
using tDataS = tCharS *;//type of character data signed
using tDataW = tCharW *;//type of character data wide
using tDataM = tCharM *;//type of character data main
using tData	 = tDataM;	//type of character data
//-//string
//-//-//constant
using tCstrU = const tCharU *;//type of constant string unsigned
using tCstrS = const tCharS *;//type of constant string signed
using tCstrM = const tCharM *;//type of constant string main
using tCstr	 = tCstrM;		  //type of constant string
//-//-//view
using tVstrU = std::basic_string_view<tCharU>;//type of view string unsigned
using tVstrS = std::basic_string_view<tCharS>;//type of view string signed
using tVstrM = std::basic_string_view<tCharM>;//type of view string (main)
using tVstr	 = tVstrM;						  //type of view string
//-//-//dynamic
using tDstrU = std::basic_string<tCharU>;//type of dynamic string unsigned
using tDstrS = std::basic_string<tCharS>;//type of dynamic string signed
using tDstrM = std::basic_string<tCharM>;//type of dynamic string main
using tDstr	 = tDstrM;					 //type of dynamic string
//consdef
constexpr tCstrM cBellCstr = "\a";
constexpr tCharM cBellChar = '\a';
constexpr tCstrM cEndlCstr = "\n";
constexpr tCharM cEndlChar = '\n';
constexpr tCstrM cEndsCstr = "\0";
constexpr tCharM cEndsChar = '\0';
//typedef
template<typename tCharT>
class tHstrT
{
public://typedef

	using tThis = tHstrT<tCharT>;
	using tChar = tCharT;
	using tData = tChar *;
	using tCstr = const tChar *;
	using tHash = nNums::tSize;
	typedef struct tConstant
	{
	public: /* codetor */

		constexpr tConstant(tData vData) noexcept: vData{vData}
		{
		}

	public://datadef

		tData vData;
	} tConstant;

public://consdef

	static constexpr tHash cMoved = 0xff'ff'ff'ff;
	static constexpr tHash cPrime = 0x00'ff'ff'ff;

public://codetor

	constexpr tHstrT() noexcept
	{
	}
	constexpr tHstrT(tCstr cData, const tSize cSize, const tHash cHash) noexcept
		: cData{cData}, cSize{cSize}, cHash{cHash}
	{
	}
	constexpr tHstrT(tCstr cData, const tSize cSize) noexcept
		: tThis{fMakeHstr(cData, cSize)}
	{
	}

	template<tSize cSizeT>
	constexpr tHstrT(tCstr (&cData)[cSizeT]) noexcept
		: tThis{fMakeHstr(cData, cSizeT)}
	{
	}

	explicit constexpr tHstrT(tConstant vConstant) noexcept
		: tThis{fMakeHstr(vConstant.vData)}
	{
	}

public://actions

	[[nodiscard("make hashed string out of c-string with null-terminator")]]
	static constexpr tThis fMakeHstr(tCstr cData) noexcept
	{
		tHash vHash = tThis::cMoved;
		tSize vSize = 0;
		for(; cData[vSize]; ++vSize)
		{
			vHash = (vHash ^ static_cast<tHash>(cData[vSize])) * cPrime;
		}
		return tThis{cData, vSize, vHash};
	}//fMakeHstr
	[[nodiscard("make hashed string out of c-string with defined size")]]
	static constexpr tThis fMakeHstr(tCstr cData, tSize vSize) noexcept
	{
		tHash vHash = tThis::cMoved;
		for(tSize vStep{}; vStep < vSize; ++vStep)
		{
			vHash = (vHash ^ static_cast<tHash>(cData[vStep])) * cPrime;
		}
		return tThis{cData, vSize, vHash};
	}//fMakeHstr
	[[nodiscard("make hashed value out of c-string with defined size")]]
	static constexpr tHash fMakeHash(tCstr cData, const tSize cSize) noexcept
	{
		return fMakeHstr(cData, cSize);
	}//fMakeHash
	template<tSize cSize>
	[[nodiscard("make hashed value out of stack-allocated c-string")]]
	static constexpr tHash fMakeHash(tCstr (&cData)[cSize]) noexcept
	{
		return fMakeHstr(cData, cSize);
	}//fMakeHash
	[[nodiscard("make hashed value out of constant wrapper")]]
	static constexpr tHash fMakeHash(tConstant vConstant) noexcept
	{
		return fMakeHstr(vConstant);
	}//fMakeHash

public: /* symbols */

	[[nodiscard("convert hashed string into the hashed value")]] constexpr
	operator tHash() const noexcept
	{
		return this->hash;
	}//operator tHash
	[[nodiscard("convert hashed string into the original string"
	)]] constexpr explicit
	operator const tChar *() const noexcept
	{
		return this->cData;
	}//operator tData

public://datadef

	tCstr cData;//original string
	tSize cSize;//original string size
	tHash cHash;//hashed value

};							  //hash string
using tHstrU = tHstrT<tCharU>;//type of hashed string unsigned
using tHstrS = tHstrT<tCharS>;//type of hashed string signed
using tHstrM = tHstrT<tCharM>;//type of hashed string main
using tHstr	 = tHstrT<tChar>; //type of hashed string
//deducts
template<typename tCharT>
[[nodiscard("deduction guide for hashed-string from c-string"
)]] tHstrT(const tCharT *cData, const tSize cSize) -> tHstrT<tCharT>;
template<typename tCharT, tSize cSizeT>
[[nodiscard("deduction guide for hashed-string from stack-allocated-string"
)]] tHstrT(const tCharT (&cData)[cSizeT]) -> tHstrT<tCharT>;
//operats
//-//string
//-//-//hashed
//-//-//-//equal
template<typename tCharT>
[[nodiscard("compare hashes of hashed strings")]]
inline constexpr nBool::tBool
operator==(const tHstrT<tCharT> &vHstrL, const tHstrT<tCharT> &vHstrR)
{
	return vHstrL.vHash == vHstrR.vHash;
}//operator==
template<typename tCharT>
[[nodiscard("compare hashes of hashed strings")]]
inline constexpr nBool::tBool
operator!=(const tHstrT<tCharT> &vHstrL, const tHstrT<tCharT> &vHstrR)
{
	return !(vHstrL == vHstrR);
}//operator!=
//-//-//-//less than
template<typename tCharT>
[[nodiscard("compare sizes of hashed strings")]]
inline constexpr nBool::tBool
operator<(const tHstrT<tCharT> &vHstrL, const tHstrT<tCharT> &vHstrR)
{
	return vHstrL.cSize < vHstrR.cSize;
}//operator<
template<typename tCharT>
[[nodiscard]]
inline constexpr nBool::tBool
operator<=(const tHstrT<tCharT> &vHstrL, const tHstrT<tCharT> &vHstrR)
{
	return !(vHstrL < vHstrR);
}//operator<=
//-//-//-//more than
template<typename tCharT>
[[nodiscard]]
inline constexpr nBool::tBool
operator>(const tHstrT<tCharT> &vHstrL, const tHstrT<tCharT> &vHstrR)
{
	return vHstrL < vHstrR;
}//operator>
template<typename tCharT>
[[nodiscard("compare sizes of hashed strings")]]
inline constexpr nBool::tBool
operator>=(const tHstrT<tChar> &vHstrL, const tHstrT<tCharT> &vHstrR)
{
	return !(vHstrL < vHstrR);
}//operator>=
//-//-//-//literal
[[nodiscard("string literal for hashed-string-main conversion")]]
inline constexpr tHstrM
operator""_HstrM(const tCharM *cData, tSize cSize) noexcept
{
	return tHstrM::fMakeHstr(cData, cSize);
}//operator""
//-//-//constant
[[nodiscard("string literal for static-string conversion")]]
inline constexpr tCstr
operator""_Cstr(const tChar *cData, tSize csize) noexcept
{
	return tCstr{cData};
}//operator""
//-//-//dynamic
[[nodiscard("string literal for dynamic-string conversion")]]
inline tDstr
operator""_Dstr(const tChar *cData, tSize cSize) noexcept
{
	return tDstr{cData, cSize};
}//operator""
//-//-//view
[[nodiscard("string literal for view-string conversion")]]
inline tVstr
operator""_Vstr(const tChar *cData, const tSize cSize) noexcept
{
	return tVstr{cData, cSize};
}//operator""
}//namespace nText
namespace nTime
{
constexpr auto cFormat = "y%ym%md%d-h%Hm%Ms%S";
}//namespace nTime
namespace nIpop
{
using tFilePath = nFileSys::path;
using tFdirInfo = nFileSys::directory_entry;
using tFdirIter = nFileSys::directory_iterator;
using tSizeInfo = nFileSys::space_info;
}//namespace nIpop
namespace nDbug
{
//datadef
inline static auto vECode = 0;
//actions
#ifdef dLibAsistProjConfWork
#ifdef SIGINT
inline auto breakpoint()
{
	std::raise(SIGINT);
}
#elif(defined(dOsysWinos))
inline auto breakpoint()
{
	fEput(text::cBellCstr);
	system("pause");
}
#else
#error "breakpoint function is not defined"
#endif//SIGINT
#else
inline auto breakpoint()
{
}
#endif /*_CONF_WORK*/
}//namespace nDbug
namespace nExec
{
using tFlow = std::thread;
}//namespace nExec
}//namespace nLibAsist
#if 0
namespace std
{
template<>
struct formatter<libasist::stChar>: public formatter<void *>
{
};
template<>
struct formatter<libasist::utChar>: public formatter<void *>
{
};
template<>
struct formatter<short signed *>: public formatter<void *>
{
};
template<>
struct formatter<short unsigned *>: public formatter<void *>
{
};
template<>
struct formatter<int signed *>: public formatter<void *>
{
};
template<>
struct formatter<int unsigned *>: public formatter<void *>
{
};
template<>
struct formatter<float *>: public formatter<void *>
{
};
template<>
struct formatter<double *>: public formatter<void *>
{
};
}//namespace std
#endif
#endif//dLibAsistHeadHxx
