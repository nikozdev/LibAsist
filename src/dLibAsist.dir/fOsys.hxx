#ifndef dLibAsistOsyshxx
#define dLibAsistOsyshxx
//defines
#ifndef dLibAsistOsys
#if defined(__unix__) || defined(__APPLE__)
#define dLibAsistOsysPosix
#if defined(__linux__)
#define dLibAsistOsysLinux
#endif//ifd(__linux__)
#if defined(__APPLE__)
#define dLibAsistOsysApple
#if defined(_TARGET_OS_MAC)
#define dLibAsistOsysMacos
#endif//ifd(_TARGET_OS_MAC)
#endif//ifd(__APPLE__)
#endif//ifd(__unix__)
#if defined(_WIN32) || defined(_WIN64)
#define dLibAsistOsysWinos
#endif//ifd(_WIN32) || defined(_WIN64)
#define dLibAsistOsys
#endif//dLibAsistOsys
//headers
#ifndef dLibAsistOsys
#error "dLibAsistOsys is not defined"
#elif(defined(dLibAsistOsysPosix))
#include <unistd.h>
#endif//dLibAsistOsys
//-//standard
#include <cstdlib>
#include <cstddef>
//content
#endif//dLibAsistOsyshxx
