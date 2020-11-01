add_library(Engine
        src/Engine.cpp
        )

target_include_directories(Engine PUBLIC ${CMAKE_CURRENT_LIST_DIR}/src)
target_link_libraries(Engine ${CONAN_LIBS})
