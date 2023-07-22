#ifndef dLibAsistHxx
#define dLibAsistHxx
//headers
#include "fOsys.hxx"
#include "fTool.hxx"
#include "fBool.hxx"
#include "fNums.hxx"
#include "fMeta.hxx"
#include "fText.hxx"
#include "fTime.hxx"
#include "fIpop.hxx"
#include "fDbug.hxx"
#include "fExec.hxx"
//content
namespace nLibAsist
{
namespace nMain
{
//imports
using namespace nBool;
using namespace nNums;
using namespace nMeta;
using namespace nText;
using namespace nTime;
using namespace nIpop;
using namespace nDbug;
using namespace nExec;
#ifdef dLibAsistMakeExe
//actions
aHasReturned("proxy main function can return an error code value"
) dFuncDefIline tECode fMain(nNums::tIntSM vArgC, nText::tCstr vArgV[])
{
	fOlog("hello world");
	if constexpr(cTruth)
	{
		fOput("{1}[{0}]=({1}", dProjName, nText::cEndlChar);
		std::copy(
			&vArgV[cZero],
			&vArgV[vArgC],
			std::ostream_iterator<tCstrM>(std::clog, nText::cEndlCstr)
		);
		fOput("{1})=[{0}]{1}", dProjName, nText::cEndlChar);
	}//title
#ifdef dLibAsistTestExe
	if(vArgC == 1)
	{
		return 1;
	}
	else if(fVetIn("tNums", &vArgV[cUnit], &vArgV[vArgC]))
	{
		fOlog("testing nums")
	}
	else if(fVetIn("tMeta", &vArgV[cUnit], &vArgV[vArgC]))
	{
		fOlog("testing meta")
	}
#endif//dLibAsistTestExe
	return errno;
}//fMain
}//nMain
#endif//dLibAsistMakeExe
}//namespace nLibAsist
#endif//dLibAsistHxx
