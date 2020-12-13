set(MINEBLOCKS_SOURCE_FILES
        src/Mineblocks/Core/Application.cpp)

add_executable(Mineblocks ${MINEBLOCKS_SOURCE_FILES})

target_include_directories(Mineblocks PUBLIC src)

target_link_libraries(Mineblocks Engine)