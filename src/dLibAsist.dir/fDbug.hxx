#ifndef dLibAsistDbugHxx
#define dLibAsistDbugHxx
//headers
#include "fOsys.hxx"
#include "fTool.hxx"
#include "fText.hxx"
#include "fIpop.hxx"
//-//standard
#include <csignal>
#include <cerrno>
//defines
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
#define fError(vCode, vActn, vArgs...)   \
	({                                   \
		fElog(vArgs);                    \
		::LibAsist::nDbug::breakpoint(); \
		errno = vCode;                   \
		vActn;                           \
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
#define fPcall(vExec, vActn, ...) \
	({                            \
		vExec;                    \
		fEfnot(                   \
			errno == 0,           \
			{                     \
				vActn;            \
				errno = 0;        \
			},                    \
			__VA_ARGS__           \
		);                        \
	})
#endif//fPcall - protected call
//content
namespace nLibAsist
{
namespace nDbug
{
//typedef
using tECode = nNums::tIntSM;
//actions
#ifdef dLibAsistProjConfWork
#ifdef SIGINT
dFuncDefIline auto fBreak()
{
	std::raise(SIGINT);
}//fBreak
#elif(defined(dLibAsistOsysWinos))
dFuncDefIline auto fBreak()
{
	fEput(text::cBellCstr);
	system("pause");
}//fBreak
#else
#error "fBrean function is not defined"
#endif//SIGINT
#else
dFuncDefIline auto fBreak()
{
}//fBreak
#endif//dLibAsistProjConfWork
}//namespace nDbug
}//namespace nLibAsist
#endif//dLibAsistDbugHxx
