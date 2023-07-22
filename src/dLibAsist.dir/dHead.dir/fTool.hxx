#ifndef dLibAsistHeadToolhxx
#define dLibAsistHeadToolhxx
//defines
#ifndef dTool
#if defined(__GNUC__) || defined(__GNUG__)
#if defined(__clang__)
#define dToolClang
#else
#define dToolGnucc
#endif//ifd(__clang__)
#endif//ifd(__GNUC__) || defined(__GNUG__)
#if defined(_MSC_VER)
#define dToolMsvcc
#endif//ifd(_MSC_VER)
#define dTool
#endif//dTool
//content
#endif//dLibAsistHeadToolhxx
