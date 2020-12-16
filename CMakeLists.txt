cmake_minimum_required(VERSION 3.18)
project(mineblocks)

set(CMAKE_CXX_STANDARD 20)

include("${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake")
conan_basic_setup()

set(SOURCE_FILES
        src/Main.cpp
        src/Mineblocks/Application.cpp
        src/Mineblocks/Common/Log.cpp)

add_executable(mineblocks ${SOURCE_FILES})
target_include_directories(mineblocks PUBLIC src)
target_precompile_headers(mineblocks PUBLIC src/Pch.cpp)
target_link_libraries(mineblocks ${CONAN_LIBS})