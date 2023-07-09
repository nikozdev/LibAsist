# libasist

- lib-asist
> library assistant
- the most basic things repeatedly written in my projects
- initially created by nikozdev to...
> avoid writting the same code for different projects
> avoid external dependencies ( yes, i had "dependophobia" )
> make own standards, frameworks and write more consistent code
- the majority of the source code is written in c/c++ programming language
> i just love this and have no need for other langs yet... *for now*
- the only build script i have is "Makefile"
> building
> cleaning
> installation
> uninstallation
> debugging
> execution
- just run "make *command*"
> appending "VARIABLE=VALUE" may affect the process

## precompile

- the important thing is that all headers are intended to be precompiled
> there are lots of standard headers included
> a lot of code is interconnected here
> so for now, this has to be in a precompiled header

## build and usage

- this library can be...
> included with some headers into source code
> compiled as an application for testing
> compiled as a library for linkage
- gnu/make is the main build system
> i find it the most verbose and specific build system
> i can set up anything i need with gnu/make on gnu/linux
- i may consider using cmake
> it would be easier to integrate other deps
> that would also be better for portability
> for now, i just dislike cmake and do not want to use it
> > because of it's format and interfaces

### link as an executable

- build and start
> make start
> > compile and link and run in the shell
> make rerun
> > recompile and relink and run in the shell
> make debug
> > recompile and relink and run in a debugger

### link as a library

- this can be built as...
> statically linked library
> > make build TYPE=SLL
> dynamically linked library
> > make build TYPE=DLL
- library usage depends on...
> operating system
> compiler

## design

- experimental
> i am a solo dev, not an expert
> this thing was initially developed for my usecases and my education
> i always wanna have some source of truth for my code
- generic
> compile-time and run-time variables instead of magical or constant values
> makefile is made as a general purpose file for scalable projects
> prioritising interface flexibility over implementation details
- configurable
> by makefile
> by source code of a user
> by aliases of primitive and generic types
> for example: setting the integer type as "using v1s\_t = short;"
- independent
> only requires things that are already present in most cases
> > standard libraries and system api
