# libasist

- lib-asist
> library assistant
- it contains the most basic things repeatedly written in my projects
> > command line argument parsing
> > standard type aliases
> > standard headers
> > memory management
- initially created by me (nikozdev) to...
> avoid writting the same code for different projects
> make own standards, frameworks and write more consistent code
- the majority of the source code is written in c/c++ programming language
> i just love this lang and have no need for other langs yet... *for now*

## build and usage

- the primary build system is cmake
> which actually generates platform dependent build files
> and i recommend using the library as a subdirectory within cmake
> > since this is gonna have some internal definitions
> the build script is located at [env/CMakeLists.txt]
- this is header-only library (TODO)
> no compillation needed for usage
> pre-compiled-headers are highly recommended when including the project
- nothing is needed to build, only add this as a cmake subdirectory
> or include headers directly without any build system support

## file structure

- the root mostly consists of directories
> doc for documents and-or documentations
> env for environment, build systems, development tools
> gen for generated files, object code, binary files
> src for source files and headers
> rsc for resources, images, sounds, videos
- there are some files that are difficult to move away from root
> .gitignore - even moving this into individual folders
> > won't prevent malicious .DS\_Store from MacOS from spawning at the root
> .gitattributes - this should be almost the same for every directory

## design

- experimental
> i am a solo dev, not an expert
> this thing was initially developed for my usecases and my education
> i am also trying to get some source of truth for my code
- generic
> compile-time and run-time variables instead of magical or constant values
> prioritising interface flexibility over implementation details
- configurable
> by cmake and [env/CMakeLists.txt]
> by source code of a user
> by aliases of primitive and generic types
> for example: setting the integer type as "using v1s\_t = short;"
- independent
> only requires things that are already present in most cases
> > standard libraries and system api
