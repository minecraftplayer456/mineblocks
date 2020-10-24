#include "test_module.hpp"

#include <spdlog/spdlog.h>

namespace engine::test {
    TestModule::TestModule()
    {
        addStage(core::ModuleLifecycle::Init, [this] { init(); });

        addSubmodule<TestModule2>();
        addSubmodule<TestModule4>();
    }

    void TestModule::init()
    {
        spdlog::info("Init");
    }

    TestModule2::TestModule2()
    {
        addStage(core::ModuleLifecycle::Init, [this] { init(); });

        require<TestModule>();

        addSubmodule<TestModule3>();
    }

    void TestModule2::init()
    {
        auto testModule = getModule<TestModule>();
        testModule->init();

        spdlog::info("Init2");
    }

    TestModule3::TestModule3()
    {
        addStage(core::ModuleLifecycle::Init, [this] { init(); });

        require<TestModule>();
    }

    void TestModule3::init()
    {
        spdlog::info("Init3");
    }

    TestModule4::TestModule4()
    {
        addStage(core::ModuleLifecycle::Init, [this] { init(); });

        require<TestModule2>();
        require<TestModule3>();
    }

    void TestModule4::init()
    {
        spdlog::info("Init4");
    }
} // namespace engine::test