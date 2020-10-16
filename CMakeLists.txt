#Set minimal cmake version
cmake_minimum_required(VERSION 3.17)

#Set project information
project(mineblocks)
set(CMAKE_CXX_STANDARD 20)

#Add conan package manager
include(conan/conanbuildinfo.cmake)
conan_basic_setup()

#Find dependencies not from conan
find_package(Vulkan REQUIRED)

#Set dependencies
set(DEPENDENCIES Vulkan::Vulkan ${CONAN_LIBS})

#Add executable
add_executable(mineblocks
        src/devices/graphics/instance.cpp
        src/devices/window/glfw.cpp
        src/devices/window/window.cpp

        src/graphics/graphics.cpp

        src/utils/version.cpp

        src/app.cpp
        src/main.cpp)

#Set include directory
target_include_directories(mineblocks PUBLIC ${CMAKE_SOURCE_DIR}/src)

#Link dependencies to executable
target_link_libraries(mineblocks ${DEPENDENCIES})