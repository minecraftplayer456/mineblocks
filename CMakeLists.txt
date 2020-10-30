cmake_minimum_required(VERSION 3.17)
project(mineblocks)

set(CMAKE_CXX_STANDARD 20)

include(conan/conanbuildinfo.cmake)
conan_basic_setup()

add_executable(mineblocks
        src/core/application.cpp

        src/devices/window.cpp

        src/maths/time.cpp

        src/state/game_state.cpp
        src/state/playing_state.cpp

        src/main.cpp)

set(DEPENDENCIES ${CONAN_LIBS})
set(INCLUDES ${CMAKE_SOURCE_DIR}/src)

target_include_directories(mineblocks PRIVATE ${INCLUDES})

target_link_libraries(mineblocks ${DEPENDENCIES})