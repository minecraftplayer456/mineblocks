#Add engine library
add_library(engine
        core/engine.cpp)

#Set include directory
target_include_directories(engine PUBLIC ${INCLUDE_DIRS})

#Link dependencies to executable
target_link_libraries(engine ${DEPENDENCIES})