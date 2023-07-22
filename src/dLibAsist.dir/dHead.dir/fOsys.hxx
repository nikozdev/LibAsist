#ifndef dLibAsistHeadOsyshxx
#define dLibAsistHeadOsyshxx
//defines
#ifndef dOsys
#if defined(__unix__) || defined(__APPLE__)
#define dOsysPosix
#if defined(__linux__)
#define dOsysLinux
#endif//ifd(__linux__)
#if defined(__APPLE__)
#define dOsysApple
#if defined(_TARGET_OS_MAC)
#define dOsysMacos
#endif//ifd(_TARGET_OS_MAC)
#endif//ifd(__APPLE__)
#endif//ifd(__unix__)
#if defined(_WIN32) || defined(_WIN64)
#define dOsysWinos
#endif//ifd(_WIN32) || defined(_WIN64)
#define dOsys
#endif//dOsys
//headers
#ifndef dOsys
#error "dOsys is not defined"
#elif(defined(dOsysPosix))
#include <unistd.h>
#endif//dOsys
//content
#endif//dLibAsistHeadOsyshxx
