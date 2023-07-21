#ifndef dLibAsistMainCxx
#define dLibAsistMainCxx
//headers
#include "fMain.hxx"
//content
#ifdef dLibAsistMakeExe
//actions
int main(int vArgC, char *vArgV[])
{
	return nLibAsist::fMain(vArgC, vArgV);
}//main
#endif//dLibAsistMakeExe
#endif//dLibAsistMainCxx
