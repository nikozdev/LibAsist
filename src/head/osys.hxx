#ifndef LIBASIST_HEAD_OSYS_HXX
#define LIBASIST_HEAD_OSYS_HXX 1

/* configs */

#ifndef _OSYS
#if defined(__unix__) || defined(__APPLE__)
#   define _OSYS_POSIX
#   if defined(__linux__)
#       define _OSYS_LINUX 1
#   endif/*ifd(__linux__)*/
#   if defined(__APPLE__)
#       define _OSYS_APPLE 1
#       if defined(_TARGET_OS_MAC)
#           define _OSYS_MACOS 1
#       endif/*ifd(_TARGET_OS_MAC)*/
#   endif/*ifd(__APPLE__)*/
#endif/*ifd(__unix__)*/
#if defined(_WIN32) || defined(_WIN64)
#   define _OSYS_WINOS 1
#endif/*ifd(_WIN32) || defined(_WIN64) */
#define _OSYS 1
#endif/*_OSYS*/

/* headers */

#ifndef _OSYS
#error "_OSYS is undefined"
#elif(defined(_OSYS_POSIX))
#include <unistd.h>
#endif/*_OSYS*/

#endif/*LIBASIST_HEAD_OSYS_HXX*/
