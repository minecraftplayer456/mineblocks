cmake_minimum_required(VERSION 3.17)

project(mineblocks CXX)
set(CMAKE_CXX_STANDARD 20)

include(build/conanbuildinfo.cmake)
conan_basic_setup()

add_subdirectory(Engine)
add_subdirectory(Mineblocks)