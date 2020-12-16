set(ENGINE_SOURCE_FILES
        src/Engine/Common/Scheduler.cpp
        src/Engine/Common/Log.cpp

        src/Engine.cpp)

add_library(Engine ${ENGINE_SOURCE_FILES})
target_include_directories(Engine PUBLIC src)
target_precompile_headers(Engine PUBLIC src/EnginePch.hpp)
target_link_libraries(Engine ${CONAN_LIBS})

set(ENGINE_TEST_SOURCE_FILES
        test/Engine/Common/LogTest.cpp
        test/Engine/Common/SchedulerTest.cpp

        test/Util/TestBase.cpp

        test/TestMain.cpp
        )

add_executable(EngineTest ${ENGINE_TEST_SOURCE_FILES})
target_include_directories(EngineTest PUBLIC src)
target_precompile_headers(Engine PUBLIC test/EngineTestPch.hpp)
target_link_libraries(EngineTest Engine)
add_test(NAME engine_test COMMAND EngineTest)