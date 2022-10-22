# libasist

- lib-asist
> - library assistant
- utilities, functions, types, etc for programming
- initially created by nikodiho to...
> - avoid writting the same code for different projects
> - avoid external dependencies ( yes, i have "dependophobia" )
> - make own standards, framework
- source code is written in c/c++ programming language
- build scripts are written in the makefile for...
> - building
> - cleaning
> - installation
> - uninstallation
> - debugging
> - running
> just run "make *command*"
> - appending "VARIABLE=VALUE" does make sense

## build and usage

- this library can be...
> - compiled as an application for testing
> - compiled as a library for linkage
- gnu/make is the main build system
- "libasist.cxx" is needed to build an executable or a library
> by some reason clang is not gonna link an object file
> compiled from a file with header extension
> even though it is just a file name ending

### header

- everything is contained inside of a single header file libasist.hxx
> - \#include "path/to/libasist.hxx"
> > into any file on a project
- all symbols can be found inside of a single namespace

### executable

- header file has all of the "inline" source code
- build and start
> - make start
> > compile and link and run in the shell
> - make rerun
> > recompile and relink and run in the shell
> - make debug
> > recompile and relink and run in a debugger

### library

- it can be built as a...
> - static library
> > make build TYPE=SLL
> - dynamic library
> > make build TYPE=DLL
- usage depends on...
> - operating system
> - compiler

## design

- minimal
> - having less - doing more
> - the least amount of essential files
> > - this readme
> > - gitignore
> > - gitattributes
> > - makefile build script
> > - header
> > - source
> - everything in a single namespace
> - license is written at the bottom of the header file
- generic
> - compile-time and run-time variables instead of magical values
> - makefile is outlined as a general purpose file for scalable projects
> > no need to extend it here, but it can be used elsewhere
> > - some adjustments are needed of course
- embeddable
> - once built - only 2 files to care about: header and library
> - name collisions are prevented by "namespace" and "undef"
- configurable
> - by makefile
> - by source code of a user
> - by aliases of primitive and generic types
> - even the project name used in the source code can be changed
> > instead of the concrette name there is only "_NAME" compile-time variable
- independent
> - only requires things that are already present in most cases
