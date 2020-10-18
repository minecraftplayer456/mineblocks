#include "test_module.hpp"

#include <spdlog/spdlog.h>

namespace engine::test {
    TestModule::TestModule()
    {
        m_stages = {core::Stage::init, core::Stage::input, core::Stage::update,
                    core::Stage::render, core::Stage::cleanup};
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
} // namespace engine::test