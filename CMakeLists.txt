cmake_minimum_required(VERSION 3.18)
project(mineblocks)

set(CMAKE_CXX_STANDARD 20)

include("${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake")
conan_basic_setup()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(CONFIGURATION_DEBUG)
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_compile_definitions(CONFIGURATION_RELEASE)
else ()
    message (FATAL_ERROR "${CMAKE_SYSTEM_NAME} is not supported as build configuration. Only release and debug are!")
endif()

add_compile_definitions(GLFW_INCLUDE_NONE)

set(SOURCE_FILES
        src/Main.cpp)

add_executable(mineblocks ${SOURCE_FILES})
target_include_directories(mineblocks PUBLIC src)
target_precompile_headers(mineblocks PUBLIC src/Pch.cpp)
target_link_libraries(mineblocks ${CONAN_LIBS})