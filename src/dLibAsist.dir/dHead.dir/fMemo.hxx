#ifndef dLibAsistHeadMemoHxx
#define dLibAsistHeadMemoHxx
//headers
#include "fBool.hxx"
#include "fNums.hxx"
//-//standard
#include <new>
#include <memory>
//content
namespace nLibAsist
{
namespace nMemo
{
//typedef
//-//byte
using tByteU = unsigned char;//type of byte unsigned
using tByteS = signed char;	 //type of byte signed
using tByteM = char;		 //type of byte main
using tByte	 = tByteM;		 //type of byte
//-//data
using tDataA = void *;	//type of data abstract
using tDataU = tByteU *;//type of data unsigned
using tDataS = tByteS *;//type of data signed
using tDataM = tByteM *;//type of data main
using tData	 = tByte *; //type of data
//consdef
constexpr auto	  cNull		= nullptr;//null pointer constant
inline const auto cNullData = cNull;  //null object pointer
}//namespace nMemo
}//namespace nLibAsist
#endif//dLibAsistHeadMemoHxx
