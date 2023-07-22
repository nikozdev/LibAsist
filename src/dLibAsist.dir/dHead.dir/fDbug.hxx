#ifndef dLibAsistHeadDbugHxx
#define dLibAsistHeadDbugHxx
//headers
#include "fOsys.hxx"
#include "fTool.hxx"
#include "fText.hxx"
#include "fIpop.hxx"
//-//standard
#include <csignal>
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
}//namespace nLibAsist
#endif//dLibAsistHeadDbugHxx
