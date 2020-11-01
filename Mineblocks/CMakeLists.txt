add_executable(Mineblocks
        src/mineblocks.cpp
        )

target_include_directories(Mineblocks PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src)
target_link_libraries(Mineblocks Engine)
