#ifndef LIBASIST_HEAD_TOOL_HXX
#define LIBASIST_HEAD_TOOL_HXX 1

#ifndef _TOOL
#if defined(__GNUC__) || defined(__GNUG__)
#   if defined(__clang__)
#       define _TOOL_CLANG 1
#   else
#       define _TOOL_GNUCC 1
#   endif/*ifd(__clang__)*/
#endif/*ifd(__GNUC__) || defined(__GNUG__)*/
#if defined(_MSC_VER)
#   define _TOOL_MSVCC 1
#endif/*ifd(_MSC_VER)*/
#define _TOOL 1
#endif/*_TOOL*/

#endif/*LIBASIST_HEAD_TOOL_HXX*/
