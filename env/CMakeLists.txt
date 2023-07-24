cmake_minimum_required(VERSION 3.20)
include_guard(GLOBAL)
# mods
include(dCmake.dir/dHelp.dir/fRegex.cmake)
include(dCmake.dir/dHelp.dir/fOpt.cmake)
# proj
project(LibAsist
    VERSION 0.0.0
    DESCRIPTION "core library assistant of nikozdev"
    ) # project
enable_language(CXX)
set(vProjName ${PROJECT_NAME})
set(vProjNameLib "l${vProjName}")
set(vProjNameExe "e${vProjName}")
set(vProjNameDir "d${vProjName}.dir")
set(vProjNameDst "p${vProjName}")
set(vProjVnum ${PROJECT_VERSION})
set(vProjVnumMajor ${PROJECT_VERSION_MAJOR})
set(vProjVnumMinor ${PROJECT_VERSION_MINOR})
set(vProjVnumMicro ${PROJECT_VERSION_PATCH})
set(vProjDesc ${PROJECT_DESCRIPTION})
# lang
set(vLangVnum 23)
set(CMAKE_CXX_STANDARD ${vLangVnum})
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
# file
set(vFdirLocRoot "${PROJECT_SOURCE_DIR}/..")
set(vFdirSrcRoot "${vFdirLocRoot}/src")
set(vFdirSrcBase "${vFdirSrcRoot}/${vProjNameDir}")
set(vFdirGenRoot "${vFdirLocRoot}/gen")
set(vFdirEnvRoot "${vFdirLocRoot}/env")
set(vFdirDocRoot ${vFdirLocRoot}/doc)
set(vFdirDstRoot "${CMAKE_INSTALL_PREFIX}")
set(vFdirDstBins "${vFdirDstRoot}/bin")
set(vFdirDstLibs "${vFdirDstRoot}/lib")
set(vFdirDstHead "${vFdirDstRoot}/include")
set(CMAKE_INSTALL_PREFIX "${vFdirDst}")
# make
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
##type
set(oProjTypePick "Hol")
set(vProjTypeList "Exe;Hol;Dll;Sll")
fOptEnum(oProjTypePick vProjTypeList "project type")
if(oProjTypePick STREQUAL "")
    message("project type is not defined")
elseif(oProjTypePick STREQUAL "Exe")
elseif(oProjTypePick STREQUAL "Hol")
elseif(oProjTypePick STREQUAL "Dll")
elseif(oProjTypePick STREQUAL "Sll")
else()
    message("project type is not handled")
endif(oProjTypePick STREQUAL "")
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
## lib
add_library(${vProjNameLib} INTERFACE)
set(vMakeDirsLib
$<BUILD_INTERFACE:${vFdirSrcRoot}>; # do not use " in generator expressions
$<INSTALL_INTERFACE:${vFdirDstHead}>; # i don't know why this shit happens
) # vMakeDirsLib
set(vMakeDefsLib
    $<$<CXX_COMPILER_ID:MSVC>:>
    $<$<CXX_COMPILER_ID:GNU,Clang>:>
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
set(vLibsList "")
#### format
set(oLibsPickFormat "Fmt")
set(vLibsListFormat "Std;Fmt;")
fOptEnum(oLibsPickFormat vLibsListFormat  "library pick for formatting")
if(oLibsPickFormat STREQUAL "")
    message(WARNING "library pick for format is not defined")
elseif(oLibsPickFormat STREQUAL "Fmt")
    find_package(fmt GLOBAL CONFIG REQUIRED)
    target_link_libraries(${vProjNameLib} INTERFACE fmt::fmt)
    list(APPEND vLibsList "fmt;")
elseif(oLibsPickFormat STREQUAL "Std")
    if(NOT oLibsPickFormatStdCompiles)
        set(CMAKE_REQUIRED_FLAGS ${CMAKE_REQUIRED_FLAGS} "--std=c++20")
        check_cxx_source_compiles(
            "#include <format> int main() { return 0; }"
            oLibsPickFormatStdCompiles
            ) # check_cxx_source_compiles
        if(${oLibsPickFormatStdCompiles})
        else()
            message(WARNING
                "std::format does not compile"
                " - choose another library for format"
                ) # message
        endif()
    endif(NOT oLibsPickFormatStdCompiles)
else()
    message(WARNING "library pick for format is not handled")
endif(oLibsPickFormat STREQUAL "")
list(APPEND vMakeDefsLib "d${vProjName}LibsPickFormat${oLibsPickFormat}")
### last
target_compile_options(${vProjNameLib} INTERFACE ${vMakeOptsLib})
target_compile_features(${vProjNameLib} INTERFACE ${vMakeFeatLib})
target_compile_definitions(${vProjNameLib} INTERFACE ${vMakeDefsLib})
target_include_directories(${vProjNameLib} INTERFACE ${vMakeDirsLib})
target_sources(${vProjNameLib}
    INTERFACE FILE_SET HEADERS
    BASE_DIRS "${vFdirSrcBase}"
    FILES
    "${vFdirSrcBase}/fOsys.hxx" "${vFdirSrcBase}/fTool.hxx"
    "${vFdirSrcBase}/fBool.hxx" "${vFdirSrcBase}/fNums.hxx"
    "${vFdirSrcBase}/fMeta.hxx" "${vFdirSrcBase}/fMemo.hxx"
    "${vFdirSrcBase}/fText.hxx" "${vFdirSrcBase}/fTime.hxx"
    "${vFdirSrcBase}/fIpop.hxx" "${vFdirSrcBase}/fDbug.hxx"
    "${vFdirSrcBase}/fExec.hxx"
    "${vFdirSrcBase}/fHead.hxx"
    ) # target_sources
target_precompile_headers(${vProjNameLib} INTERFACE ${vFdirSrcBase}/fHead.hxx)
## exe
option(oMakeExe "make project executable" 0)
if(oMakeExe)
    add_executable(${vProjNameExe} ${vFdirSrcBase}/fMain.cxx)
    set(vMakeDirsExe "")
    set(vMakeDefsExe "d${vProjName}MakeExe")
    set(vMakeFeatExe "")
    set(vMakeOptsExe "")
    # test
    option(oTestExe "test project executable" 0)
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
        set(vTestName "tMeta")
        add_test(NAME ${vTestName}
            COMMAND ${vFdirGen}/${vProjNameExe} ${vTestName}
            ) # add_test
        set(vPassRegex "")
        string(APPEND vPassRegex "[${vTestName}]=(.+")
        string(APPEND vPassRegex "[fGetNequOrLast(1,1,3,4)]=(3).+")
        string(APPEND vPassRegex "[fGetMember(vS,&tS::vI)]=(1).+")
        string(APPEND vPassRegex "[fGetMember(vS,{&tS::vI})]=(1).+")
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
    target_precompile_headers(${vProjNameExe} PRIVATE ${vFdirSrcBase}/fHead.hxx)
endif(oMakeExe)
# pack
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${vFdirDocRoot}/license.md")
set(CPACK_PACKAGE_VERSION_MAJOR "${vProjVnumMajor}")
set(CPACK_PACKAGE_VERSION_MINOR "${vProjVnumMinor}")
set(CPACK_PACKAGE_VERSION_PATCH "${vProjVnumMicro}")
include(CPack)
set(vProjFdirDst "${vFdirDstLibs}/cmake/${vProjNameDst}")
string(APPEND vProjFdirDst "-${vProjVnumMajor}")
string(APPEND vProjFdirDst "-${vProjVnumMinor}")
string(APPEND vProjFdirDst "-${vProjVnumMicro}")
string(APPEND vProjFdirDst ".dir")
include(CMakePackageConfigHelpers)
configure_package_config_file(
    "${vFdirEnvRoot}/dCMake.dir/dPack.dir/fConfig.cmake.in"
    "${vFdirGenRoot}/${vProjNameDst}Config.cmake"
    INSTALL_DESTINATION "${vProjFdirDst}"
    ) # package Config
write_basic_package_version_file(
    "${vFdirGenRoot}/${vProjNameDst}ConfigVersion.cmake"
    VERSION ${vProjVnum}
    COMPATIBILITY SameMajorVersion
    ) # package ConfigVersion
install(
    TARGETS ${vProjNameLib} EXPORT ${vProjNameDst}
    FILE_SET HEADERS DESTINATION ${vFdirDstHead}/${vProjNameDir}
    ) # install target with header
install(EXPORT "${vProjNameDst}"
    FILE "${vProjNameDst}.cmake"
    DESTINATION "${vProjFdirDst}"
    NAMESPACE "${vProjNameDst}::"
    ) # install Target
install(FILES
    "${vFdirGenRoot}/${vProjNameDst}Config.cmake"
    "${vFdirGenRoot}/${vProjNameDst}ConfigVersion.cmake"
    DESTINATION "${vProjFdirDst}"
    ) # install ConfigVersion
export(EXPORT "${vProjNameDst}"
    FILE "${vFdirGenRoot}/${vProjNameDst}.cmake"
    NAMESPACE "${vProjNameDst}::"
    ) # export Target
