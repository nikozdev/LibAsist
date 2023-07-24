#ifndef dLibAsistTimeHxx
#define dLibAsistTimeHxx
//headers
#include "fNums.hxx"
#include "fMemo.hxx"
#include "fText.hxx"
//-//standard
#include <ctime>
#include <chrono>
//content
namespace nLibAsist
{
namespace nTime
{
//imports
using namespace std::literals;
//consdef
dDataDefConst auto cFormat = "y%ym%md%d-h%Hm%Ms%S";
}//namespace nTime
}//namespace nLibAsist
#endif//dLibAsistTimeHxx
