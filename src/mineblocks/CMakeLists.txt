#Add engine library
add_executable(mineblocks
        core/mineblocks.cpp

        main.cpp)

#Link dependencies to engine
target_link_libraries(mineblocks engine)