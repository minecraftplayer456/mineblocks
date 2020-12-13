set(ENGINE_SOURCE_FILES
        src/Engine/Common/Test.cpp

        src/Engine.cpp)

add_library(Engine ${ENGINE_SOURCE_FILES})
target_include_directories(Engine PUBLIC src)
target_precompile_headers(Engine PUBLIC src/EnginePch.hpp)
target_link_libraries(Engine ${CONAN_LIBS})

set(ENGINE_TEST_SOURCE_FILES
        test/Engine/Common/TestTest.cpp)

add_executable(EngineTest ${ENGINE_TEST_SOURCE_FILES})
target_include_directories(EngineTest PUBLIC src)
target_precompile_headers(Engine PUBLIC test/EngineTestPch.hpp)
target_link_libraries(EngineTest Engine)
add_test(NAME engine_test COMMAND EngineTest)