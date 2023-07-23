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
	fOlog("hello world");
	if constexpr(cTruth)
	{
		fOput("{1}[{0}]=({1}", dProjName, cEndlChar);
		std::copy(
			&vArgV[cZero],
			&vArgV[vArgC],
			std::ostream_iterator<tCstrM>(std::clog, cEndlCstr)
		);
		fOput("{1})=[{0}]{1}", dProjName, cEndlChar);
	}//title
#ifdef dLibAsistTestExe
	if(vArgC == 1)
	{
		fElog("undefined testing arguments");
		return 1;
	}
	if(fVetIn("tOsys", &vArgV[cUnit], &vArgV[vArgC]))
	{
		fOput("[osys]=(\n");
		fOput(")=[osys]\n");
	}
	if(fVetIn("tTool", &vArgV[cUnit], &vArgV[vArgC]))
	{
		fOput("[tool]=(\n");
		fOput(")=[tool]\n");
	}
	if(fVetIn("tBool", &vArgV[cUnit], &vArgV[vArgC]))
	{
		fOput("[bool]=(\n");
		fOput(")=[bool]\n");
	}
	if(fVetIn("tNums", &vArgV[cUnit], &vArgV[vArgC]))
	{
		fOput("[nums]=(\n");
		fOput(")=[nums]\n");
	}
	if(fVetIn("tMeta", &vArgV[cUnit], &vArgV[vArgC]))
	{
		fOput("[meta]=(\n");
		fOput(")=[meta]\n");
	}
	if(fVetIn("tText", &vArgV[cUnit], &vArgV[vArgC]))
	{
		fOput("[text]=(\n");
		fOput(")=[text]\n");
	}
	if(fVetIn("tTime", &vArgV[cUnit], &vArgV[vArgC]))
	{
		fOput("[time]=(\n");
		fOput(")=[time]\n");
	}
	if(fVetIn("tIpop", &vArgV[cUnit], &vArgV[vArgC]))
	{
		fOput("[ipop]=(\n");
		fOput(")=[ipop]\n");
	}
	if(fVetIn("tExec", &vArgV[cUnit], &vArgV[vArgC]))
	{
		fOput("[exec]=(\n");
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
		fOput("\n)=[exec]\n");
	}
	if(fVetIn("tDbug", &vArgV[cUnit], &vArgV[vArgC]))
	{
		fOput("\n[dbug]=(\n");
		fOput("\n)=[dbug]\n");
	}
#endif//dLibAsistTestExe
	return errno;
}//fMain
}//nMain
#endif//dLibAsistMakeExe
}//namespace nLibAsist
#endif//dLibAsistHxx
