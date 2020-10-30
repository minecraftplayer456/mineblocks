cmake_minimum_required(VERSION 3.17)
project(mineblocks)

set(CMAKE_CXX_STANDARD 20)

add_executable(mineblocks
        src/core/application.cpp

        src/maths/time.cpp

        src/state/game_state.cpp
        src/state/playing_state.cpp

        src/main.cpp)

target_include_directories(mineblocks PRIVATE src)