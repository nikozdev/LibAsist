#ifndef dLibAsistHeadTextHxx
#define dLibAsistHeadTextHxx
//headers
#include "fBool.hxx"
#include "fNums.hxx"
#include "fMemo.hxx"
//-//standard
#include <string>
#include <cstring>
#include <string_view>
#include <sstream>
#include <format>
//defines
#ifndef fGetStrFromArg
#define fGetStrFromArg(str) #str
#endif//fGetStrFromArg
//content
namespace nLibAsist
{
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
#endif//dLibAsistHeadTextHxx
