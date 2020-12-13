cmake_minimum_required(VERSION 3.18)

#Set basic project information
project(Mineblocks VERSION 0.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)

#Detect compiler name
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(COMPILER_NAME "clang")
    add_compile_definitions(ENGINE_COMPILER_CLANG)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(COMPILER_NAME "gcc")
    add_compile_definitions(ENGINE_COMPILER_GCC)
else ()
    message (FATAL_ERROR "${CMAKE_SYSTEM_NAME} is not supported as c++ compiler. Currently only clang and gcc are!")
endif()

#Detect operating system
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(OS_NAME "windows")
    add_compile_definitions(ENGINE_OS_WIN32)
else()
    message (FATAL_ERROR "${CMAKE_SYSTEM_NAME} is not supported as operating system. Currently only windows is!")
endif()

#Detect compile configuration
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CONFIGURATION_NAME "debug")
    add_compile_definitions(ENGINE_CONFIGURATION_DEBUG)
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CONFIGURATION_NAME "release")
    add_compile_definitions(ENGINE_CONFIGURATION_RELEASE)
else ()
    message (FATAL_ERROR "${CMAKE_SYSTEM_NAME} is not supported as build configuration. Only release and debug are!")
endif()

#Include conan build information
include("conan/${COMPILER_NAME}/conanbuildinfo.cmake")
conan_basic_setup()

enable_testing()

#Include subprojects
add_subdirectory(Engine)
add_subdirectory(Mineblocks)