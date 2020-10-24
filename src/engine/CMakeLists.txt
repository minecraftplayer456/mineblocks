#Add engine library
add_library(engine
        core/app.cpp
        core/engine.cpp
        core/module.cpp

        maths/time.cpp

        test/test_module.cpp

        utils/graph.cpp
        utils/type_info.hpp
        utils/version.cpp)

#Set include directory
target_include_directories(engine PUBLIC ${INCLUDE_DIRS})

#Link dependencies to executable
target_link_libraries(engine ${DEPENDENCIES})