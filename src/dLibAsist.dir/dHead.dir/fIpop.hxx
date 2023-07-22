#ifndef dLibAsistHeadIpopHxx
#define dLibAsistHeadIpopHxx
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
//defines
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
#endif//dLibAsistHeadIpopHxx
