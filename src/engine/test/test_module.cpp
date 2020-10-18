#include "test_module.hpp"

#include <spdlog/spdlog.h>

namespace engine::test {
    TestModule::TestModule()
    {
        m_stages = {core::Stage::init};
    }

    void TestModule::init()
    {
        spdlog::info("Init!");
    }
} // namespace engine::test