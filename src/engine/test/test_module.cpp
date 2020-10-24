#include "test_module.hpp"

#include <spdlog/spdlog.h>

#include <engine/core/engine.hpp>

namespace engine::test {
    TestModule::TestModule()
    {
        // addStage(core::Stage::Init, [this] { init(); });
        // addStage(core::Stage::Input, [this] { input(); });
        addStage(core::Stage::Update, [this] { update(); });
        addStage(core::Stage::Render, [this] { render(); });
        // addStage(core::Stage::Cleanup, [this] { cleanup(); });

        // addSubmodule(new TestModule4);
        // addSubmodule(new TestModule2);
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
        // spdlog::info("update");
        static int i = 0;

        if (i >= 64) {
            spdlog::info("Delta update: " +
                         std::to_string(m_engine->getDeltaUpdate().asMilliSeconds()));
            spdlog::info("Ups:" + std::to_string(m_engine->getUps()));
            i = 0;
        }

        i++;
    }

    void TestModule::render()
    {
        // spdlog::info("render");
        static int i = 0;

        if (i >= 64) {
            spdlog::info("Delta render: " +
                         std::to_string(m_engine->getDeltaRender().asMilliSeconds()));
            spdlog::info("Fps:" + std::to_string(m_engine->getFps()));
            i = 0;
        }

        i++;
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

        require<TestModule>();

        addSubmodule(new TestModule3);
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

    TestModule3::TestModule3()
    {
        addStage(core::Stage::Init, [this] { init(); });
        addStage(core::Stage::Input, [this] { input(); });
        addStage(core::Stage::Update, [this] { update(); });
        addStage(core::Stage::Render, [this] { render(); });
        addStage(core::Stage::Cleanup, [this] { cleanup(); });

        require<TestModule>();
    }

    void TestModule3::init()
    {
        spdlog::info("init3");
    }

    void TestModule3::input()
    {
        spdlog::info("input3");
    }

    void TestModule3::update()
    {
        spdlog::info("update3");
    }

    void TestModule3::render()
    {
        spdlog::info("render3");
    }

    void TestModule3::cleanup()
    {
        spdlog::info("cleanup3");
    }

    TestModule4::TestModule4()
    {
        addStage(core::Stage::Init, [this] { init(); });
        addStage(core::Stage::Input, [this] { input(); });
        addStage(core::Stage::Update, [this] { update(); });
        addStage(core::Stage::Render, [this] { render(); });
        addStage(core::Stage::Cleanup, [this] { cleanup(); });

        require<TestModule2, TestModule3>();
    }

    void TestModule4::init()
    {
        spdlog::info("init4");
    }

    void TestModule4::input()
    {
        spdlog::info("input4");
    }

    void TestModule4::update()
    {
        spdlog::info("update4");
    }

    void TestModule4::render()
    {
        spdlog::info("render4");
        m_engine->requestStop();
    }

    void TestModule4::cleanup()
    {
        spdlog::info("cleanup4");
    }
} // namespace engine::test