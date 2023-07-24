#ifndef dLibAsistOsysHxx
#define dLibAsistOsysHxx
//defines
#ifndef dOsysMask
#if defined(__unix__) || defined(__APPLE__)
#define dOsysMaskPosix 0b1000'0000'0000'0000
#if defined(__linux__)
#define dOsysMaskLinux 0b0100'0000'0000'0000
#else
#define dOsysMaskLinux 0b0000'0000'0000'0000
#endif//ifd(__linux__)
#if defined(__APPLE__)
#define dOsysMaskApple 0b0000'1000'0000'0000
#if defined(_TARGET_OS_MAC)
#define dOsysMaskMacos 0b0000'0100'0000'0000
#else
#define dOsysMaskMacos 0b0000'0000'0000'0000
#endif//ifd(_TARGET_OS_MAC)
#else
#define dOsysMaskApple 0b0000'0000'0000'0000
#endif//ifd(__APPLE__)
#else
#define dOsysMaskPosix 0b0000'0000'0000'0000
#endif//ifd(__unix__)
#if defined(_WIN32) || defined(_WIN64)
#define dOsysMaskWinos 0b0000'0000'1000'0000
#else
#define dOsysMaskWinos 0b0000'0000'0000'0000
#endif//ifd(_WIN32) || defined(_WIN64)
#define dOsysMask                                                      \
	(dOsysMaskPosix | dOsysMaskLinux | dOsysMaskApple | dOsysMaskMacos \
	 | dOsysMaskWinos)
#define dOsysMaskApply(dMask) (dOsysMask & dMask)
#define dOsysMaskCheck(dMask) (dOsysMaskApply(dMask) > 0)
#endif//dOsysMask
//headers
#ifndef dOsysMask
#error "dOsysMask is not defined"
#elif(dOsysMaskCheck(dOsysMaskPosix))
#include <unistd.h>
#endif//dOsysMask
//-//standard
#include <cstdlib>
#include <cstddef>
//content
#endif//dLibAsistOsysHxx
