# libasist

- lib-asist
> - library assistant
- utilities, functions, types, etc for programming
- initially created by nikozdev to...
> - avoid writting the same code for different projects
> - avoid external dependencies ( yes, i have "dependophobia" )
> - make own standards, frameworks
- the majority of the source code is written in c/c++ programming language
- the only build script is "makefile" for...
> - building
> - cleaning
> - installation
> - uninstallation
> - debugging
> - execution
> just run "make *command*"
> - appending "VARIABLE=VALUE" may affect the process

## build and usage

- this library can be...
> - included with some headers into source code
> - compiled as an application for testing
> - compiled as a library for linkage
- gnu/make is the main build system

### link as an executable

- build and start
> - make start
> > compile and link and run in the shell
> - make rerun
> > recompile and relink and run in the shell
> - make debug
> > recompile and relink and run in a debugger

### link as a library

- this can be built as...
> - statically linked library
> > make build TYPE=SLL
> - dynamically linked library
> > make build TYPE=DLL
- library usage depends on...
> - operating system
> - compiler

## design

- generic
> - compile-time and run-time variables instead of magical or constant values
> - makefile is made as a general purpose file for scalable projects
> - templates and abstractions where it is appropriate
> - prioritising interface
- embeddable
> - include headers by requirement
> - name collisions are prevented by "namespace" and "#undef"
- configurable
> - by makefile
> - by source code of a user
> - by aliases of primitive and generic types
> > for example: setting the integer type as "using v1s\_t = short;"
> - even the project name used in the code can be changed
> > instead of the name there is only "_NAME" compile-time variable
- independent
> - only requires things that are already present in most cases
> > standard libraries, system api, popular generic api...
