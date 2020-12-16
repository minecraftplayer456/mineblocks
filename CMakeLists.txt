cmake_minimum_required(VERSION 3.18)
project(mineblocks)

set(CMAKE_CXX_STANDARD 20)

include("${CMAKE_CURRENT_BINARY_DIR}/conanbuildinfo.cmake")
conan_basic_setup()

add_executable(mineblocks src/Main.cpp)
target_include_directories(mineblocks PUBLIC src)
target_precompile_headers(mineblocks PUBLIC src/Pch.cpp)
target_link_libraries(mineblocks ${CONAN_LIBS})