#Set minimal cmake version
cmake_minimum_required(VERSION 3.17)

#Set project information
project(mineblocks)
set(CMAKE_CXX_STANDARD 20)

#Add executable
add_executable(mineblocks src/main.cpp)