#ifndef dLibAsistToolHxx
#define dLibAsistToolHxx
//defines
#ifndef dToolMask
#if defined(__GNUC__) || defined(__GNUG__)
#if defined(__clang__)
#define dToolMaskClang 0b1000'0000
#define dToolMaskGnucc 0b0000'0000
#else
#define dToolMaskClang 0b0000'0000
#define dToolMaskGnucc 0b0100'0000
#endif//ifd(__clang__)
#endif//ifd(__GNUC__) || defined(__GNUG__)
#if defined(_MSC_VER)
#define dToolMaskMsvcc 0b0010'0000
#else
#define dToolMaskMsvcc 0b0000'0000
#endif//ifd(_MSC_VER)
#define dToolMask			  (dToolMaskClang | dToolMaskGnucc | dToolMaskMsvcc)
#define dToolMaskApply(dMask) (dToolMask & dMask)
#define dToolMaskCheck(dMask) (dToolMaskApply(dMask) > 0)
#endif//dToolMask
//-//attributes-with-comments
#ifndef aLibAsist
#define aLibAsist
#define aDeprecation(...) [[deprecated(__VA_ARGS__)]]
#define aUseReturned(...) [[nodiscard(__VA_ARGS__)]]
#define aHasReturned(...) [[]]
#define aNotReturned(...) [[noreturn]]
#define aCanBeUnused(...) [[maybe_unused]]
#ifndef dToolMask
#error("undefined code-processing tool")
#elif defined(dToolMaskGnucc)
#define aSetDeclspec(vSpec, ...) ()
#define aDllExported(...)		 ()
#define aDllImported(...)		 ()
#elif defined(dToolMaskMsvcc)
#define aSetDeclspec(vSpec, ...) __declspec(vSpec)
#define aDllExported(...)		 __declspec(__dllexport)
#define aDllImported(...)		 __declspec(__dllimport)
#elif defined(dToolMaskClang)
#define aSetDeclspec(vSpec, ...) ()
#define aDllExported(...)		 ()
#define aDllImported(...)		 ()
#else
#error("unhandled code-processing tool")
#endif//dToolMask
#endif//aLibAsist
//-//dec-n-def
namespace nLibAsist
{
namespace nTool
{
//-//-//function
//-//-//-//declaration
#ifndef dFuncDec
#define dFuncDecIline inline   //declare function using inlining
#define dFuncDecConst constexpr//declare function using compile-time
#define dFuncDecExter extern   //declare function used externally
#define dFuncDecInter static   //declare function used internally
#define dFuncDec
#endif//dFuncDec
#if defined(dFuncDec)
dFuncDecIline auto fFuncIline();
dFuncDecConst auto fFuncConst();
dFuncDecExter auto fFuncExter();
dFuncDecInter auto fFuncInter();
#endif//ifd(dFuncDec)
//-//-//-//definition
#ifndef dFuncDef
#define dFuncDefIline inline   //define function using inlining
#define dFuncDefConst constexpr//define function using compile-time
#define dFuncDefExter		   //define function used externally
#define dFuncDefInter static   //define function used internally
#define dFuncDef
#endif//dFuncDef
#if defined(dFuncDef)
dFuncDefIline auto fFuncIline()
{
}
dFuncDefConst auto fFuncConst()
{
}
dFuncDefExter auto fFuncExter()
{
}
dFuncDefInter auto fFuncInter()
{
}
#endif//ifd(dFuncDef)
//-//-//variable
//-//-//-//declaration
#ifndef dDataDec
#define dDataDecExter extern//declare variable used externally
#define dDataDec
#endif//dDataDec
#if defined(dDataDec)
dDataDecExter int vDataExter;
#endif//dDataDec
//-//-//-//definition
#ifndef dDataDef
#define dDataDefIline inline   //define variable using inlining
#define dDataDefConst constexpr//define variable using compile-time
#define dDataDefExter		   //define variable used externally
#define dDataDefInter static   //define variable used internally
#define dDataDef
#endif//dDataDef
#if defined(dDataDef)
dDataDefIline int vDataIline;
dDataDefConst int vDataConst = 0;
dDataDefExter int vDataExter;
dDataDefInter int vDataInter;
#endif//ifd(dDataDef)
//-//-//type
//-//-//-//declaration
#ifndef dTypeDec
#define dTypeDecIline//define type using inlining
#define dTypeDecExter//define type using it externally
#define dTypeDecInter//define type using it internally
#define dTypeDec
#endif//dTypeDec
#if defined(dTypeDec)
dTypeDecIline struct tTypeIline;
dTypeDecExter struct tTypeExter;
dTypeDecInter struct tTypeInter;
#endif//ifd(dTypeDec)
//-//-//-//definition
#ifndef dTypeDef
#define dTypeDefIline//define type using inlining
#define dTypeDefInter//define type used internally
#define dTypeDefExter//define type used externally
#define dTypeDef
#endif//dTypeDef
#if defined(dTypeDef)
dTypeDefIline struct tTypeIline
{
};
dTypeDefExter struct tTypeExter
{
};
dTypeDefInter struct tTypeInter
{
};
#endif//ifd(dTypeDef)
}//namespace nTool
}//namespace nLibAsist
//headers
#include <algorithm>
//content
#endif//dLibAsistToolHxx
