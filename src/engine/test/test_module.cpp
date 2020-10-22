#include "test_module.hpp"

#include <spdlog/spdlog.h>

namespace engine::test {
    TestModule::TestModule()
    {
        addStage<TestModule2>(core::Stage::Init, [this] { init(); });
        addStage(core::Stage::Input, [this] { input(); });
        addStage(core::Stage::Update, [this] { update(); });
        addStage(core::Stage::Render, [this] { render(); });
        addStage(core::Stage::Cleanup, [this] { cleanup(); });
    }

    void TestModule::init()
    {
        spdlog::info("init");
    }

    void TestModule::input()
    {
        spdlog::info("input");
    }

    void TestModule::update()
    {
        spdlog::info("update");
    }

    void TestModule::render()
    {
        spdlog::info("render");
    }

    void TestModule::cleanup()
    {
        spdlog::info("cleanup");
    }

    TestModule2::TestModule2()
    {
        addStage(core::Stage::Init, [this] { init(); });
        addStage(core::Stage::Input, [this] { input(); });
        addStage(core::Stage::Update, [this] { update(); });
        addStage(core::Stage::Render, [this] { render(); });
        addStage(core::Stage::Cleanup, [this] { cleanup(); });
    }

    void TestModule2::init()
    {
        spdlog::info("init2");
    }

    void TestModule2::input()
    {
        spdlog::info("input2");
    }

    void TestModule2::update()
    {
        spdlog::info("update2");
    }

    void TestModule2::render()
    {
        spdlog::info("render2");
    }

    void TestModule2::cleanup()
    {
        spdlog::info("cleanup2");
    }
} // namespace engine::test