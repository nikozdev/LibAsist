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
#include "fExec.hxx"
#include "fDbug.hxx"
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
using namespace nExec;
using namespace nDbug;
#ifdef dLibAsistMakeExe
//actions
aHasReturned("proxy main function can return an error code value"
) dFuncDefIline tECode fMain(tIntSM vArgC, tCstr vArgV[])
{
	fOput("{1}[{0}]=({1}", dProjName, cEndlChar);
	fOlog("hello world");
	if constexpr(cTruth)
	{
		std::copy(
			&vArgV[cZero],
			&vArgV[vArgC],
			std::ostream_iterator<tCstrM>(std::clog, cEndlCstr)
		);
	}//title
#ifdef dLibAsistTestExe
	if(vArgC == 1)
	{
		fElog("undefined testing arguments");
		errno = EINVAL;
	}
	if(fVetIn("tOsys", &vArgV[cUnit], &vArgV[vArgC]))
	{
		fOput("[tOsys]=(\n");
		dDataDefConst std::pair<tCstr, tMask> cOsysTable[]{
			{"Posix", dOsysMaskPosix},
			{"Linux", dOsysMaskLinux},
			{"Apple", dOsysMaskApple},
			{"Macos", dOsysMaskMacos},
			{"Winos", dOsysMaskWinos},
		};//cOsysTable
		for(auto vI: cOsysTable)
		{
			fOput(
				"[{0:s}]=([flag]=({1:1b})[mask]=({2:016b})){3:c}",
				vI.first,
				dOsysMaskCheck(vI.second),
				dOsysMaskApply(vI.second),
				'\n'
			);
		}
		fOput(")=[tOsys]\n");
	}
	if(fVetIn("tTool", &vArgV[cUnit], &vArgV[vArgC]))
	{
		fOput("[tTool]=(\n");
		dDataDefConst std::pair<tCstr, tMask> cOsysTable[]{
			{"Clang", dToolMaskClang},
			{"Gnucc", dToolMaskGnucc},
			{"Msvcc", dToolMaskMsvcc},
		};//cOsysTable
		for(auto vI: cOsysTable)
		{
			fOput(
				"[{0:s}]=([flag]=({1:1b})[mask]=({2:016b})){3:c}",
				vI.first,
				dToolMaskCheck(vI.second),
				dToolMaskApply(vI.second),
				'\n'
			);
		}
		fOput(")=[tTool]\n");
	}
	if(fVetIn("tBool", &vArgV[cUnit], &vArgV[vArgC]))
	{
		fOput("[tBool]=(\n");
		fOput(")=[tBool]\n");
	}
	if(fVetIn("tNums", &vArgV[cUnit], &vArgV[vArgC]))
	{
		fOput("[tNums]=(\n");
		fOput("[fGetPow(2,2)]=({0})\n", fGetPow(2, 2));
		fOput("[fGetAliUpper(2,8)]=({0})\n", fGetAliUpper(2, 8));
		fOput("[fGetAliLower(7,4)]=({0})\n", fGetAliLower(7, 4));
		fOput("[fGetAbs(-4200)]=({0})\n", fGetAbs(-4'200));
		fOput("[fGetSign(-420)]=({0})\n", fGetSign(-420));
		fOput("[fGetCount(-42)]=({0})\n", fGetCount(-42));
		fOput("[fGetFromL(-123456,3)]=({0})\n", fGetFromL(-123'456, 3));
		fOput("[fGetFromR(-123456,3)]=({0})\n", fGetFromR(-123'456, 3));
		fOput("[fGetRev(-12345)]=({0})\n", fGetRev(-12'345));
		fOput("[fGetMin(-1,+1)]=({0:+})\n", fGetMin(-1, +1));
		fOput("[fGetMax(-1,+1)]=({0:+})\n", fGetMax(-1, +1));
		fOput("[fVetISide(0,-1,+1)]=({0:b})\n", fVetISide(0, -1, +1));
		fOput("[fVetOSide(2,-1,+1)]=({0:b})\n", fVetOSide(2, -1, +1));
		fOput(")=[tNums]\n");
	}
	if(fVetIn("tMeta", &vArgV[cUnit], &vArgV[vArgC]))
	{
		fOput("[tMeta]=(\n");
		struct tS
		{
			tIntSM vI = 1;
		} vS;
		std::tuple<decltype(&tS::vI)> vT = {&tS::vI};
		fOput("[fGetNequOrLast(1,1,3,4)]=({0:})\n", fGetNequOrLast(1, 1, 3, 4));
		fOput(
			"[fGetMember(vS,&tS::vI)]=({0:})\n", fGetMember(vS, std::get<0>(vT))
		);
		//fOput("[fGetMember(vS,{&tS::vT})]=({0:})\n", fGetMember(vS, vT));
		fOput(")=[tMeta]\n");
	}
	if(fVetIn("tText", &vArgV[cUnit], &vArgV[vArgC]))
	{
		fOput("[tText]=(\n");
		fOput(")=[tText]\n");
	}
	if(fVetIn("tTime", &vArgV[cUnit], &vArgV[vArgC]))
	{
		fOput("[tTime]=(\n");
		fOput(")=[tTime]\n");
	}
	if(fVetIn("tIpop", &vArgV[cUnit], &vArgV[vArgC]))
	{
		fOput("[tIpop]=(\n");
		fOput(")=[tIpop]\n");
	}
	if(fVetIn("tExec", &vArgV[cUnit], &vArgV[vArgC]))
	{
		fOput("[tExec]=(\n");
		if constexpr(cTruth)
		{
			tIndex vIndex = 1;
			//-//task
			tTask<tIndex(tIndex &)> vTask(
				[](tIndex &rIndex)
				{
					fElog("task");
					return rIndex++;
				}
			);
			tGetter<tIndex> vTaskGetter = vTask.get_future();
			tFlow{std::move(vTask), std::ref(vIndex)}.detach();
			vTaskGetter.wait();
			//-//call
			tGetter<tIndex> vCallGetter = fCallDefer(
				[](tIndex &vIndex) -> tIndex
				{
					fOlog("call");
					return vIndex++;
				},
				std::ref(vIndex)
			);
			vCallGetter.wait();
			//-//setter
			tSetter<tIndex> vSetter;
			tGetter<tIndex> vSetterGetter = vSetter.get_future();
			auto vSetterProc = [](tSetter<tIndex> &rSetter, tIndex &rIndex)
			{
				fElog("setter");
				rSetter.set_value_at_thread_exit(rIndex++);
			};
			tFlow(vSetterProc, std::ref(vSetter), std::ref(vIndex)).detach();
			vSetterGetter.wait();
			fOlog(
				"[task]=({0})\n[call]=({1})\n[setter]=({2})\n",
				vTaskGetter.get(),
				vCallGetter.get(),
				vSetterGetter.get()
			);
		}//future
		if constexpr(cTruth)
		{
			tCount	vCount = 0;
			tLocker vLocker;
			auto	fFlow = [](tLocker &rLocker, tCount &rCount)
			{
				auto vFlowIndex = fGetFlowIndex();
				for(auto vI = 1; vI <= 1'000'000; vI++)
				{
					tLockerGuard vLockerGuard(rLocker);
					//rLocker.fLock();
					rCount += 1;
					if(vI % 100'000 == 0)
					{
						fEput(
							"[flowid]=({0:x})[icount]=({1})\n", vFlowIndex, rCount
						);
					}
					//rLocker.fOpen();
				}
				return rCount;
			};//fFlow
			tFlow{fFlow, std::ref(vLocker), std::ref(vCount)}.detach();
			tFlow{fFlow, std::ref(vLocker), std::ref(vCount)}.join();
			fOlog("[flowid]=({0:x})[icount]=({1})", fGetFlowIndex(), vCount);
		}//mutex
		fOput("\n)=[tExec]\n");
	}
	if(fVetIn("tDbug", &vArgV[cUnit], &vArgV[vArgC]))
	{
		fOput("\n[tDbug]=(\n");
		fOput("\n)=[tDbug]\n");
	}
#endif//dLibAsistTestExe
	fOput("{1})=[{0}]{1}", dProjName, cEndlChar);
	return errno;
}//fMain
}//nMain
#endif//dLibAsistMakeExe
}//namespace nLibAsist
#endif//dLibAsistHxx
