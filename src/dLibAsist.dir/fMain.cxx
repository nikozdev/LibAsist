#ifndef dLibAsistMainCxx
#define dLibAsistMainCxx
//headers
#include "fHead.hxx"
//content
#ifdef dLibAsistMakeExe
//actions
int main(int vArgC, const char *vArgV[])
{
	return ::nLibAsist::nMain::fMain(vArgC, vArgV);
}//main
#endif//dLibAsistMakeExe
#endif//dLibAsistMainCxx
