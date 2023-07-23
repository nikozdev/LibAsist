cmake_minimum_required(VERSION 3.20)
# mods
include(dCmake.dir/mHelpRegex.cmake)
include(dCmake.dir/mHelpOpt.cmake)
# proj
project(LibAsist
    VERSION 0.0.0
    DESCRIPTION "core library assistant of nikozdev"
    ) # project
enable_language(CXX)
set(vProjName ${PROJECT_NAME})
set(vProjNameLib "l${vProjName}")
set(vProjNameExe "e${vProjName}")
set(vProjVnum ${PROJECT_VERSION})
set(vProjDesc ${PROJECT_DESCRIPTION})
# lang
set(vLangVnum 23)
set(CMAKE_CXX_STANDARD ${vLangVnum})
set(CMAKE_CXX_STANDARD_REQUIRED ${vLangVnum})
# file
set(vFdirLoc ${PROJECT_SOURCE_DIR}/..)
set(vFdirSrcRoot ${vFdirLoc}/src)
set(vFdirSrcBase ${vFdirSrcRoot}/d${vProjName}.dir)
set(vFdirGen ${vFdirLoc}/gen)
set(RUNTIME_OUTPUT_DIRECTORY ${vFdirGen}/dExe.dir)
set(LIBRARY_OUTPUT_DIRECTORY ${vFdirGen}/dLib.dir)
set(ARCHIVE_OUTPUT_DIRECTORY ${vFdirGen}/dLib.dir)
# make
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
##conf
set(oProjConf "Work")
set(vProjConfList "Play;Work;")
fOptEnum(oProjConf vProjConfList "project configuration")
if(oProjConf STREQUAL "")
    message("project configuration is not defined")
elseif(oProjConf STREQUAL "Play")
    set(CMAKE_BUILD_TYPE Release)
elseif(oProjConf STREQUAL "Work")
    set(CMAKE_BUILD_TYPE Debug)
else()
    message("project configuration is not handled")
endif(oProjConf STREQUAL "")
##type
set(oProjType "Hol")
set(vProjTypeList "Exe;Hol;Dll;Sll")
fOptEnum(oProjType vProjTypeList "project type")
if(oProjType STREQUAL "")
    message("project type is not defined")
elseif(oProjType STREQUAL "Exe")
elseif(oProjType STREQUAL "Hol")
elseif(oProjType STREQUAL "Dll")
elseif(oProjType STREQUAL "Sll")
else()
    message("project type is not handled")
endif(oProjType STREQUAL "")
## lib
add_library(${vProjNameLib} INTERFACE)
set(vMakeDirsLib ${vFdirSrcRoot})
set(vMakeDefsLib
    "$<$<CXX_COMPILER_ID:MSVC>:>"
    "$<$<CXX_COMPILER_ID:GNU,Clang>:>"
    "d${vProjName}ProjName=\"${vProjName}\"" "dProjName=\"${vProjName}\""
    "d${vProjName}ProjVnum=\"${vProjVnum}\"" "dProjVnum=\"${vProjVnum}\""
    "d${vProjName}ProjDesc=\"${vProjDesc}\"" "dProjDesc=\"${vProjDesc}\""
    "d${vProjName}ProjConf${oProjConf}" "dProjConf${oProjConf}"
    "d${vProjName}ProjType${oProjType}" "dProjType${oProjConf}"
    ) # vMakeDefsLib
set(vMakeFeatLib
    cxx_std_23
    cxx_constexpr
    cxx_variadic_templates
    ) # vMakeFeatLib
set(vMakeOptsLib
    -fpermissive
    -Wno-class-conversion
    -Wno-error=narrowing -Wno-narrowing
    ) # vMakeOptsLib
### libs
set(oLibsFormat "Fmt")
set(vLibsListFormat "Std;Fmt;")
fOptEnum(oLibsFormat vLibsListFormat  "library for formatting")
if(oLibsFormat STREQUAL "")
    message(WARNING "library for format is not defined")
elseif(oLibsFormat STREQUAL "Fmt")
    find_package(fmt CONFIG REQUIRED)
    target_link_libraries(${vProjNameLib} INTERFACE fmt::fmt-header-only)
    list(APPEND vMakeDefsLib "d${vProjName}LibsFormatFmt")
elseif(oLibsFormat STREQUAL "Std")
    if(NOT oLibsFormatStdCompiles)
        set(CMAKE_REQUIRED_FLAGS ${CMAKE_REQUIRED_FLAGS} "--std=c++20")
        check_cxx_source_compiles(
            "#include <format> int main() { return 0; }"
            oLibsFormatStdCompiles
            ) # check_cxx_source_compiles
        if(${oLibsFormatStdCompiles})
        else()
            message(WARNING
                "std::format does not compile"
                " - choose another library for format"
                ) # message
        endif()
    endif(NOT oLibsFormatStdCompiles)
else()
    message(WARNING "library for format is not handled")
endif(oLibsFormat STREQUAL "")
list(APPEND vMakeDefsLib "d${vProjName}LibsFormat${oLibsFormat}")
### last
target_compile_options(${vProjNameLib} INTERFACE ${vMakeOptsLib})
target_compile_features(${vProjNameLib} INTERFACE ${vMakeFeatLib})
target_compile_definitions(${vProjNameLib} INTERFACE ${vMakeDefsLib})
target_include_directories(${vProjNameLib} INTERFACE ${vMakeDirsLib})
target_precompile_headers(${vProjNameLib} INTERFACE ${vFdirSrcBase}/fHead.hxx)
## exe
option(oMakeExe "make project executable" 1)
if(oMakeExe)
    add_executable(${vProjNameExe} ${vFdirSrcBase}/fMain.cxx)
    set(vMakeDirsExe "")
    set(vMakeDefsExe "d${vProjName}MakeExe")
    set(vMakeFeatExe "")
    set(vMakeOptsExe "")
    # test
    option(oTestExe "test project executable" 1)
    if(oTestExe)
        include(CTest)
        enable_testing()
        list(APPEND vMakeDefsExe "d${vProjName}TestExe")
        #
        set(vTestName "tHello")
        add_test(NAME ${vTestName}
            COMMAND ${vFdirGen}/${vProjNameExe}
            ) # add_test
        set(vPassRegex "hello world")
        set_tests_properties(tHello PROPERTIES
            PASS_REGULAR_EXPRESSION ${vPassRegex}
            ) # set_tests_properties
        #
        set(vTestName "tOsys")
        add_test(NAME ${vTestName}
            COMMAND ${vFdirGen}/${vProjNameExe} ${vTestName}
            ) # add_test
        #set(vPassRegex "[${vTestName}]=()=[${vTestName}]")
        set(vPassRegex "")
        string(APPEND vPassRegex "[${vTestName}]=(.+")
        string(APPEND vPassRegex "[Posix]=([flag]=(.+)[mask]=(.+)).+")
        string(APPEND vPassRegex "[Linux]=([flag]=(.+)[mask]=(.+)).+")
        string(APPEND vPassRegex "[Apple]=([flag]=(.+)[mask]=(.+)).+")
        string(APPEND vPassRegex "[Macos]=([flag]=(.+)[mask]=(.+)).+")
        string(APPEND vPassRegex "[Winos]=([flag]=(.+)[mask]=(.+)).+")
        string(APPEND vPassRegex ")=[${vTestName}].+")
        fRegexIgnoreABracket(vPassRegex)
        set_tests_properties(${vTestName} PROPERTIES
            PASS_REGULAR_EXPRESSION ${vPassRegex}
            ) # set_tests_properties
        #
        set(vTestName "tTool")
        add_test(NAME ${vTestName}
            COMMAND ${vFdirGen}/${vProjNameExe} ${vTestName}
            ) # add_test
        set(vPassRegex "")
        string(APPEND vPassRegex "[${vTestName}]=(.+")
        string(APPEND vPassRegex "[Clang]=([flag]=(.+)[mask]=(.+)).+")
        string(APPEND vPassRegex "[Gnucc]=([flag]=(.+)[mask]=(.+)).+")
        string(APPEND vPassRegex "[Msvcc]=([flag]=(.+)[mask]=(.+)).+")
        string(APPEND vPassRegex ")=[${vTestName}].+")
        fRegexIgnoreABracket(vPassRegex)
        set_tests_properties(${vTestName} PROPERTIES
            PASS_REGULAR_EXPRESSION ${vPassRegex}
            ) # set_tests_properties
        #
        set(vTestName "tNums")
        add_test(NAME ${vTestName}
            COMMAND ${vFdirGen}/${vProjNameExe} ${vTestName}
            ) # add_test
        set(vPassRegex "")
        string(APPEND vPassRegex "[${vTestName}]=(.+")
        string(APPEND vPassRegex "[fGetPow(2,2)]=(4).+")
        string(APPEND vPassRegex "[fGetAliUpper(2,8)]=(8).+")
        string(APPEND vPassRegex "[fGetAliLower(7,4)]=(4).+")
        string(APPEND vPassRegex "[fGetAbs(-4200)]=(4200).+")
        string(APPEND vPassRegex "[fGetSign(-420)]=(-1).+")
        string(APPEND vPassRegex "[fGetCount(-42)]=(2).+")
        string(APPEND vPassRegex "[fGetFromL(-123456,3)]=(3).+")
        string(APPEND vPassRegex "[fGetFromR(-123456,3)]=(4).+")
        string(APPEND vPassRegex "[fGetRev(-12345)]=(-54321).+")
        #string(APPEND vPassRegex "[fGetMin(-1,+1)]=(-1).+")
        #string(APPEND vPassRegex "[fGetMax(-1,+1)]=(+1).+")
        #string(APPEND vPassRegex "[fVetISide(0,-1,+1)]=(1).+")
        #string(APPEND vPassRegex "[fVetOSide(2,-1,+1)]=(1).+")
        string(APPEND vPassRegex ")=[${vTestName}].+")
        fRegexIgnoreABracket(vPassRegex)
        set_tests_properties(${vTestName} PROPERTIES
            PASS_REGULAR_EXPRESSION ${vPassRegex}
            ) # set_tests_properties
        #
        set(vTestName "tExec")
        add_test(NAME ${vTestName}
            COMMAND ${vFdirGen}/${vProjNameExe} ${vTestName}
            ) # add_test
        set(vPassRegex "")
        string(APPEND vPassRegex "[${vTestName}]=(.+")
        string(APPEND vPassRegex "[task]=(1).+")
        string(APPEND vPassRegex "[call]=(2).+")
        string(APPEND vPassRegex "[setter]=(3).+")
        string(APPEND vPassRegex "[flowid]=(.+)[icount]=(2000000).+")
        string(APPEND vPassRegex ")=[${vTestName}].+")
        fRegexIgnoreABracket(vPassRegex)
        set_tests_properties(${vTestName} PROPERTIES
            PASS_REGULAR_EXPRESSION ${vPassRegex}
            ) # set_tests_properties
        #
    endif(oTestExe)
    # libs
    target_link_libraries(${vProjNameExe} PRIVATE ${vProjNameLib})
    # last
    target_compile_options(${vProjNameExe} PRIVATE ${vMakeOptsExe})
    target_compile_features(${vProjNameExe} PRIVATE ${vMakeFeatExe})
    target_compile_definitions(${vProjNameExe} PRIVATE ${vMakeDefsExe})
    target_include_directories(${vProjNameExe} PRIVATE ${vMakeDirsExe})
    target_precompile_headers(${vProjNameLib} INTERFACE ${vFdirSrcBase}/fHead.hxx)
endif(oMakeExe)
