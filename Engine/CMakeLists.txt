add_library(Engine
        src/Engine.cpp
        )

target_include_directories(Engine PUBLIC src/)

target_precompile_headers(Engine PUBLIC src/enginepch.hpp)

target_link_libraries(Engine ${CONAN_LIBS})