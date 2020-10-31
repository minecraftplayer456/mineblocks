cmake_minimum_required(VERSION 3.17)
project(mineblocks)

set(CMAKE_CXX_STANDARD 20)

include(conan/conanbuildinfo.cmake)
conan_basic_setup()

find_package(Vulkan)

add_executable(mineblocks
        src/core/application.cpp

        src/devices/instance.cpp
        src/devices/logical_device.cpp
        src/devices/physical_device.cpp
        src/devices/window.cpp

        src/graphics/graphics.cpp
        src/graphics/master_renderer.cpp

        src/maths/time.cpp

        src/state/game_state.cpp
        src/state/playing_state.cpp

        src/main.cpp)

set(DEPENDENCIES Vulkan::Vulkan ${CONAN_LIBS})
set(INCLUDES ${CMAKE_SOURCE_DIR}/src)

target_include_directories(mineblocks PRIVATE ${INCLUDES})

target_link_libraries(mineblocks ${DEPENDENCIES})