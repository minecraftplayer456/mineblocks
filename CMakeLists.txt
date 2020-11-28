cmake_minimum_required(VERSION 3.17)

project(mineblocks CXX)
set(CMAKE_CXX_STANDARD 20)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(COMPILER_NAME "clang")
else ()
    set(COMPILER_NAME "gcc")
endif ()

include(conan/${COMPILER_NAME}/conanbuildinfo.cmake)
conan_basic_setup()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("Debug")
    add_compile_definitions(ENGINE_MODE_DEBUG)
endif ()

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    message("Release")
    add_compile_definitions(ENGINE_MODE_RELEASE)
endif ()

add_subdirectory(Engine)
add_subdirectory(Mineblocks)