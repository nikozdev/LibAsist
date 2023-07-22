#ifndef dLibAsistIpopHxx
#define dLibAsistIpopHxx
//headers
#include "fOsys.hxx"
#include "fTool.hxx"
#include "fNums.hxx"
#include "fMemo.hxx"
#include "fText.hxx"
//-//standard
#include <cstdio>
#include <iostream>
#include <fstream>
#ifndef dLibAsistTool
#error "dLibAsistTool is undefined"
#elif(defined(dLibAsistToolClang) || defined(dLibAsistToolMsvcc))
#include <filesystem>
namespace nLibAsist
{//imports
namespace nFileSys = std::filesystem;
}//namespace nLibAsist
#elif(defined(dLibAsistToolGnucc))
#include <experimental/bits/fs_fwd.h>
#include <experimental/bits/fs_path.h>
#include <experimental/bits/fs_dir.h>
#include <experimental/bits/fs_ops.h>
namespace nLibAsist
{//imports
namespace nFileSys = std::experimental::filesystem;
}//namespace nLibAsist
#endif//ifd(dLibAsistToolGnucc)
//defines
#ifndef fOput
#define fOput(...)                                                            \
	{                                                                         \
		::nLibAsist::nText::nFormat::format_to(                               \
			std::ostream_iterator<decltype(std::cout)::char_type>(std::cout), \
			__VA_ARGS__                                                       \
		);                                                                    \
	}
#endif//fOput
#ifndef fOlog
#define fOlog(...)                                            \
	{                                                         \
		fOput(                                                \
			"[from]{:s}"                                      \
			"[file]{:s}"                                      \
			"[func]{:s}"                                      \
			"[line]{:d}"                                      \
			"[mesg]{:c}{:s}{:c}",                             \
                                                              \
			"olog",                                           \
			dFileName,                                        \
			dFuncName,                                        \
			dFileLine,                                        \
			::nLibAsist::nText::cEndlChar,                    \
			::nLibAsist::nText::nFormat::format(__VA_ARGS__), \
			::nLibAsist::nText::cEndlChar                     \
		);                                                    \
	}
#endif//fOlog
#ifndef fEput
#define fEput(...)                                                            \
	{                                                                         \
		::nLibAsist::nText::nFormat::format_to(                               \
			std::ostream_iterator<decltype(std::cerr)::char_type>(std::cout), \
			__VA_ARGS__                                                       \
		);                                                                    \
	}
#endif//fEput
#ifndef fElog
#define fElog(...)                                            \
	{                                                         \
		fEput(                                                \
			"[from]{:s}"                                      \
			"[file]{:s}"                                      \
			"[func]{:s}"                                      \
			"[line]{:d}"                                      \
			"[mesg]{:c}{:s}{:c}",                             \
                                                              \
			"elog",                                           \
			dFileName,                                        \
			dFuncName,                                        \
			dFileLine,                                        \
			::nLibAsist::nText::cEndlChar,                    \
			::nLibAsist::nText::nFormat::format(__VA_ARGS__), \
			::nLibAsist::nText::cEndlChar                     \
		);                                                    \
	}
#endif//fElog
//content
namespace nLibAsist
{
namespace nIpop
{
using tFilePath = nFileSys::path;
using tFdirInfo = nFileSys::directory_entry;
using tFdirIter = nFileSys::directory_iterator;
using tSizeInfo = nFileSys::space_info;
}//namespace nIpop
}//namespace nLibAsist
#endif//dLibAsistIpopHxx
