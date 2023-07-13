cmake_minimum_required(VERSION 3.20)
# proj
project(libasist
    VERSION "0.3.0"
    DESCRIPTION "core library of nikozdev"
    ) # project
set(vProjName "${PROJECT_NAME}")
set(vProjVnum "${PROJECT_VERSION}")
set(vProjType EXE)
set(vProjConf WORK)
# lang
set(CXX_STANDARD 20)
set(CXX_STANDARD_REQUIRED 20)
set(CMAKE_CXX_COMPILER g++)
# file
set(vFileLoc "${PROJECT_SOURCE_DIR}/..")
set(vFileDirSrc "${vFileLoc}/src")
file(GLOB vFileSetSrc CMAKE_CONFIGURE_DEPENDS
    "${vFileDirSrc}/*.cxx"
    "${vFileDirSrc}/*/*.cxx"
    ) # file
set(vFileDirGen "${vFileLoc}/gen")
set(RUNTIME_OUTPUT_DIRECTORY ${vFileDirGen}/run)
set(LIBRARY_OUTPUT_DIRECTORY ${vFileDirGen}/lib)
set(ARCHIVE_OUTPUT_DIRECTORY ${vFileDirGen}/lib)
# make
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)
# set_property()
add_executable(${vProjName})
##target_link_libraries(${vProjName} PUBLIC)
target_link_options(${vProjName} PUBLIC
    -lstdc++
    ) # target_link_options
target_compile_options(${vProjName} PRIVATE
    -O0 -g
    -fpermissive
    -Wno-class-conversion
    -Wno-error=narrowing -Wno-narrowing
    ) # target_compile_options
target_compile_features(${vProjName} PUBLIC
    cxx_std_20
    cxx_constexpr
    cxx_variadic_templates
    ) # target_compile_features
target_include_directories(${vProjName} PRIVATE
    "${vFileDirSrc}"
    "${vFileDirGen}"
    ) # target_include_directories
target_compile_definitions(${vProjName} PUBLIC
    _NAME=${vProjName} _NAME_STR=\"${vProjName}\"
    _VNUM=${vProjVnum} _VNUM_STR=\"${vProjVnum}\"
    _TYPE_${vProjType} _TYPE_STR=\"${vProjType}\"
    _CONF_${vProjConf} _CONF_STR=\"${vProjConf}\"
    ) # target_definitions
target_sources(${vProjName} PUBLIC ${vFileSetSrc})
target_precompile_headers(${vProjName} PRIVATE ${vFileDirSrc}/head.hxx)
