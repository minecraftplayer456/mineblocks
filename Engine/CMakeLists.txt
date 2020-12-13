set(ENGINE_SOURCE_FILES
        src/Engine.cpp)

add_library(Engine ${ENGINE_SOURCE_FILES})

target_include_directories(Engine PUBLIC src)