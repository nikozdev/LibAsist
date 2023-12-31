cmake_minimum_required(VERSION 3.3...3.8)
include_guard(GLOBAL)
# mods
include(dCmake.dir/dHelp.dir/fRegex.cmake)
include(dCmake.dir/dHelp.dir/fOpt.cmake)
include(dCmake.dir/dHelp.dir/fPack.cmake)
# proj
project(LibAsist
    VERSION 1.0.3
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
# osys
mark_as_advanced(FORCE CMAKE_OSX_ARCHITECTURES)
mark_as_advanced(FORCE CMAKE_OSX_DEPLOYMENT_TARGET)
mark_as_advanced(FORCE CMAKE_OSX_SYSROOT)
# file
set(vFdirLocRoot "${PROJECT_SOURCE_DIR}/..")
set(vFdirSrcRoot "${vFdirLocRoot}/src")
set(vFdirSrcBase "${vFdirSrcRoot}/${vProjNameDir}")
set(vFdirGenRoot "${vFdirLocRoot}/gen")
set(vFdirEnvRoot "${vFdirLocRoot}/env")
set(vFdirDocRoot ${vFdirLocRoot}/doc)
set(vFdirDstRoot "$ENV{HOME}$ENV{UserProfile}/.local")
set(vFdirDstBins "${vFdirDstRoot}/bin")
set(vFdirDstLibs "${vFdirDstRoot}/lib")
set(vFdirDstHead "${vFdirDstRoot}/include")
set(CMAKE_PREFIX_PATH "${vFdirDstRoot}" CACHE PATH "destination prefix" FORCE)
set(CMAKE_INSTALL_PREFIX "${vFdirDstRoot}" CACHE PATH "install prefix" FORCE)
# conf
set(oProjConfPick "Work")
set(vProjConfList "Work;Play;Dist;")
set(vProjConfDesc "controlled by oProjConfPick")
fOptEnum(oProjConfPick vProjConfList "project configuration")
if(oProjConfPick STREQUAL "")
    message("project configuration is not defined")
elseif(oProjConfPick STREQUAL "Work")
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "${vProjConfDesc}" FORCE)
elseif(oProjConfPick STREQUAL "Play")
    set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "${vProjConfDesc}" FORCE)
elseif(oProjConfPick STREQUAL "Dist")
    set(CMAKE_BUILD_TYPE Release CACHE STRING "${vProjConfDesc}" FORCE)
else()
    message("project configuration is not handled")
endif(oProjConfPick STREQUAL "")
fOptEnum(CMAKE_BUILD_TYPE CMAKE_CONFIGURATION_TYPES ${vProjConfDesc})
mark_as_advanced(FORCE CMAKE_BUILD_TYPE)
# make
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
##tool
set(vMakeToolGnucc "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(vMakeToolMsvcc "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
## lib
add_library(${vProjNameLib} INTERFACE)
set(vMakeDirsLib
    "$<BUILD_INTERFACE:${vFdirSrcRoot}>;"
    "$<INSTALL_INTERFACE:${vFdirDstHead}>;"
    ) # vMakeDirsLib
set(vMakeDefsLib
    "d${vProjName}ProjName=\"${vProjName}\"" "dProjName=\"${vProjName}\""
    "d${vProjName}ProjVnum=\"${vProjVnum}\"" "dProjVnum=\"${vProjVnum}\""
    "d${vProjName}ProjDesc=\"${vProjDesc}\"" "dProjDesc=\"${vProjDesc}\""
    "d${vProjName}ProjConf${oProjConfPick}" "dProjConf${oProjConfPick}"
    ) # vMakeDefsLib
set(vMakeFeatLib
    cxx_std_23
    cxx_constexpr
    cxx_variadic_templates
    ) # vMakeFeatLib
set(vMakeOptsLib
    "$<${vMakeToolGnucc}:-fpermissive;-Wno-macro-redefined;-Wno-class-conversion>"
    "$<${vMakeToolMsvcc}:>"
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
    fPackFind("fmt" "")
    target_link_libraries(${vProjNameLib} INTERFACE fmt::fmt)
    list(APPEND vLibsList "fmt;")
elseif(oLibsPickFormat STREQUAL "Std")
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
## exe
option(oMakeExe "make project executable" 1)
if(oMakeExe)
    add_executable(${vProjNameExe} ${vFdirSrcBase}/fMain.cxx)
    set(vMakeDefsExe "d${vProjName}MakeExe")
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
        mark_as_advanced(FORCE BUILD_TESTING)
    endif(oTestExe)
    # libs
    target_link_libraries(${vProjNameExe} PRIVATE ${vProjNameLib})
    # last
    target_compile_definitions(${vProjNameExe} PRIVATE ${vMakeDefsExe})
endif(oMakeExe)
# pack
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${vFdirDocRoot}/license.md")
set(CPACK_PACKAGE_VERSION_MAJOR "${vProjVnumMajor}")
set(CPACK_PACKAGE_VERSION_MINOR "${vProjVnumMinor}")
set(CPACK_PACKAGE_VERSION_PATCH "${vProjVnumMicro}")
include(CPack)
set(vFdirDstProj "${vFdirDstLibs}/cmake/${vProjNameDst}")
string(APPEND vFdirDstProj "-${vProjVnumMajor}")
string(APPEND vFdirDstProj "-${vProjVnumMinor}")
string(APPEND vFdirDstProj "-${vProjVnumMicro}")
string(APPEND vFdirDstProj ".dir")
include(CMakePackageConfigHelpers)
configure_package_config_file(
    "${vFdirEnvRoot}/dCMake.dir/dPack.dir/fConfig.cmake.in"
    "${vFdirGenRoot}/${vProjNameDst}-Config.cmake"
    INSTALL_DESTINATION "${vFdirDstProj}"
    ) # package Config
write_basic_package_version_file(
    "${vFdirGenRoot}/${vProjNameDst}-ConfigVersion.cmake"
    VERSION ${vProjVnum}
    COMPATIBILITY SameMajorVersion
    ) # package ConfigVersion
install(
    TARGETS ${vProjNameLib} EXPORT ${vProjNameDst}
    FILE_SET HEADERS DESTINATION ${vFdirDstHead}/${vProjNameDir}
    ) # install target with header
install(EXPORT "${vProjNameDst}"
    FILE "${vProjNameDst}.cmake"
    DESTINATION "${vFdirDstProj}"
    NAMESPACE "${vProjNameDst}::"
    ) # install Target
install(FILES
    "${vFdirGenRoot}/${vProjNameDst}-Config.cmake"
    "${vFdirGenRoot}/${vProjNameDst}-ConfigVersion.cmake"
    DESTINATION "${vFdirDstProj}"
    ) # install ConfigVersion
export(EXPORT "${vProjNameDst}"
    FILE "${vFdirGenRoot}/${vProjNameDst}.cmake"
    NAMESPACE "${vProjNameDst}::"
    ) # export Target
