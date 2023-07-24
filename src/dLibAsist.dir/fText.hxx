#ifndef dLibAsistTextHxx
#define dLibAsistTextHxx
//headers
#include "fTool.hxx"
#include "fBool.hxx"
#include "fNums.hxx"
#include "fMemo.hxx"
//-//standard
#include <string>
#include <cstring>
#include <string_view>
#include <sstream>
#ifdef dLibAsistLibsPickFormatFmt
#include <fmt/format.h>
#include <fmt/ranges.h>
namespace nLibAsist
{
namespace nText
{
namespace nFormat = ::fmt;
}//namespace nText
}//namespace nLibAsist
#endif//dLibAsistLibsPickFormatFmt
#ifdef dLibAsistLibsPickFormatStd
#include <format>
namespace nLibAsist
{
namespace nText
{
namespace nFormat = ::std;
}//namespace nText
}//namespace nLibAsist
#endif//dLibAsistLibsPickFormatStd
//defines
#ifndef fGetStrFromArg
#define fGetStrFromArg(str) #str
#endif//fGetStrFromArg
//content
namespace nLibAsist
{
namespace nText
{
//imports
using namespace nBool;
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
dDataDefConst tCstrM cBellCstr = "\a";
dDataDefConst tCharM cBellChar = '\a';
dDataDefConst tCstrM cEndlCstr = "\n";
dDataDefConst tCharM cEndlChar = '\n';
dDataDefConst tCstrM cEndsCstr = "\0";
dDataDefConst tCharM cEndsChar = '\0';
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

		dFuncDefConst tConstant(tData vData) noexcept: vData{vData}
		{
		}

	public://datadef

		tData vData;
	} tConstant;

public://consdef

	dDataDefConst dDataDefInter tHash cMoved = 0xff'ff'ff'ff;
	dDataDefConst dDataDefInter tHash cPrime = 0x00'ff'ff'ff;

public://codetor

	aUseReturned("make hashed string with default values"
	) dFuncDefConst tHstrT() noexcept
	{
	}
	aUseReturned("make hashed string with all given values"
	) dFuncDefConst tHstrT(tCstr cData, const tSize cSize, const tHash cHash) noexcept
		: cData{cData}, cSize{cSize}, cHash{cHash}
	{
	}
	aUseReturned("make hashed string out of a string with defined size"
	) dFuncDefConst tHstrT(tCstr cData, const tSize cSize) noexcept
		: tThis{fMakeHstr(cData, cSize)}
	{
	}

	template<tSize cSizeT>
	aUseReturned("make hashed string out of a stack-allocated string"
	) dFuncDefConst tHstrT(tCstr (&cData)[cSizeT]) noexcept
		: tThis{fMakeHstr(cData, cSizeT)}
	{
	}

	aUseReturned("make hashed string out of the constant wrapper"
	) explicit dFuncDefConst tHstrT(tConstant vConstant) noexcept
		: tThis{fMakeHstr(vConstant.vData)}
	{
	}

public://actions

	aUseReturned("make hashed string out of string with null-terminator"
	) dFuncDefConst dFuncDefInter tThis fMakeHstr(tCstr cData) noexcept
	{
		tHash vHash = tThis::cMoved;
		tSize vSize = 0;
		for(; cData[vSize]; ++vSize)
		{
			vHash = (vHash ^ static_cast<tHash>(cData[vSize])) * cPrime;
		}
		return tThis{cData, vSize, vHash};
	}//fMakeHstr
	aUseReturned("make hashed string out of a string with defined size"
	) dFuncDefConst dFuncDefInter tThis fMakeHstr(tCstr cData, tSize vSize) noexcept
	{
		tHash vHash = tThis::cMoved;
		for(tSize vStep{}; vStep < vSize; ++vStep)
		{
			vHash = (vHash ^ static_cast<tHash>(cData[vStep])) * cPrime;
		}
		return tThis{cData, vSize, vHash};
	}//fMakeHstr
	aUseReturned("make hashed value out of c-string with defined size"
	) dFuncDefConst dFuncDefInter tHash
		fMakeHash(tCstr cData, const tSize cSize) noexcept
	{
		return fMakeHstr(cData, cSize);
	}//fMakeHash
	template<tSize cSize>
	aUseReturned("make hashed value out of stack-allocated c-string"
	) dFuncDefConst dFuncDefInter tHash fMakeHash(tCstr (&cData)[cSize]
	) noexcept
	{
		return fMakeHstr(cData, cSize);
	}//fMakeHash
	aUseReturned("make hashed value out of constant wrapper"
	) dFuncDefInter dFuncDefConst tHash fMakeHash(tConstant vConstant) noexcept
	{
		return fMakeHstr(vConstant);
	}//fMakeHash

public://operats

	aUseReturned("convert hashed string into the hashed value") dFuncDefConst
	operator tHash() const noexcept
	{
		return this->hash;
	}//operator tHash
	aUseReturned("convert hashed string into the original string"
	) dFuncDefConst explicit
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
aUseReturned("deduction guide for hashed-string from c-string"
) dFuncDefExter explicit tHstrT(const tCharT *cData, const tSize cSize)
	-> tHstrT<tCharT>;
template<typename tCharT, tSize cSizeT>
aUseReturned("deduction guide for hashed-string from stack-allocated-string"
) dFuncDefExter tHstrT(const tCharT (&cData)[cSizeT]) -> tHstrT<tCharT>;
//operats
//-//string
//-//-//hashed
//-//-//-//equal
template<typename tCharT>
aUseReturned("compare hashes of hashed strings") dFuncDefConst tBool
operator==(const tHstrT<tCharT> &vHstrL, const tHstrT<tCharT> &vHstrR)
{
	return vHstrL.vHash == vHstrR.vHash;
}//operator==
template<typename tCharT>
aUseReturned("compare hashes of hashed strings") dFuncDefConst tBool
operator!=(const tHstrT<tCharT> &vHstrL, const tHstrT<tCharT> &vHstrR)
{
	return !(vHstrL == vHstrR);
}//operator!=
//-//-//-//less than
template<typename tCharT>
aUseReturned("compare sizes of hashed strings") dFuncDefConst tBool
operator<(const tHstrT<tCharT> &vHstrL, const tHstrT<tCharT> &vHstrR)
{
	return vHstrL.cSize < vHstrR.cSize;
}//operator<
template<typename tCharT>
aUseReturned("compare sizes of hashed strings") dFuncDefConst tBool
operator<=(const tHstrT<tCharT> &vHstrL, const tHstrT<tCharT> &vHstrR)
{
	return !(vHstrL < vHstrR);
}//operator<=
//-//-//-//more than
template<typename tCharT>
aUseReturned("compare sizes of hashed strings") dFuncDefConst tBool
operator>(const tHstrT<tCharT> &vHstrL, const tHstrT<tCharT> &vHstrR)
{
	return vHstrL < vHstrR;
}//operator>
template<typename tCharT>
aUseReturned("compare sizes of hashed strings") dFuncDefConst tBool
operator>=(const tHstrT<tChar> &vHstrL, const tHstrT<tCharT> &vHstrR)
{
	return !(vHstrL < vHstrR);
}//operator>=
//-//-//-//literal
aUseReturned("string literal for hashed-string-main conversion"
) dFuncDefConst tHstrM
operator""_Hstr(const tCharM *cData, tSize cSize) noexcept
{
	return tHstrM::fMakeHstr(cData, cSize);
}//operator""
//-//-//constant
aUseReturned("string literal for string conversion") dFuncDefConst tCstr
operator""_Cstr(const tChar *cData, tSize csize) noexcept
{
	return tCstr{cData};
}//operator""
//-//-//dynamic
aUseReturned("string literal for dynamic-string conversion") dFuncDefIline tDstr
operator""_Dstr(const tChar *cData, tSize cSize) noexcept
{
	return tDstr{cData, cSize};
}//operator""
//-//-//view
aUseReturned("string literal for view-string conversion") dFuncDefConst tVstr
operator""_Vstr(const tChar *cData, const tSize cSize) noexcept
{
	return tVstr{cData, cSize};
}//operator""
//actions
aUseReturned("compare two c-strings for being one equal to the other"
) dFuncDefIline tBool fVetEq(tCstr vCstrL, tCstr vCstrR, tBool vVet = 1)
{
	return (std::strcmp(vCstrL, vCstrR) == 0) == vVet;
}//fVetEq
aUseReturned("compare two c-strings for being one longer than the other"
) dFuncDefIline tBool fVetGt(tCstr vCstrL, tCstr vCstrR)
{
	return std::strlen(vCstrL) > std::strlen(vCstrR);
}//fVetGt
aUseReturned("compare two c-strings for being one shorter than the other"
) dFuncDefIline tBool fVetLt(tCstr vCstrL, tCstr vCstrR)
{
	return std::strlen(vCstrL) < std::strlen(vCstrR);
}//fVetLt
aUseReturned("find out if the given string string array contains a string"
) dFuncDefIline tBool
	fVetIn(tCstrM vCstr, tCstrM pHead[], tCstrM pTail[], tBool vVet = 1)
{
	for(tCstrM *pIter = pHead; pIter < pTail; pIter++)
	{
		if(fVetEq(vCstr, *pIter))
		{
			return vVet;
		}
	}
	return !vVet;
}//fVetIn
}//namespace nText
}//namespace nLibAsist
#if 0
namespace std
{
template<>
struct formatter<nLibAsist::nText::tDataM*>: public formatter<void *>
{
};
template<>
struct formatter<nLibAsist::nText::tIntSM*>: public formatter<void *>
{
};
template<>
struct formatter<nLibAsist::nText::tIntUM*>: public formatter<void *>
{
};
template<>
struct formatter<nLibAsist::nNums::tRealM*>: public formatter<void *>
{
};
}//namespace std
#endif
#endif//dLibAsistTextHxx
