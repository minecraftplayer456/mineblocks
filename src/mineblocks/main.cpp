#include <spdlog/spdlog.h>

#include <engine/core/engine.hpp>
#include <engine/core/module.hpp>
#include <engine/test/test_module.hpp>

#include "core/mineblocks.hpp"

int main(int argc, char** argv)
{
    // mineblocks::core::Mineblocks mineblocks;

    // engine::core::Engine engine(&mineblocks);

    // engine.run();

    engine::core::ModuleRegistry moduleRegistry;

    spdlog::info("Register Modules");

    moduleRegistry.registerModule(new engine::test::TestModule);
    moduleRegistry.registerModule(new engine::test::TestModule2);

    spdlog::info("Sort Stages");

    moduleRegistry.sortStages();

    spdlog::info("Sorted Stages");

    moduleRegistry.callStage(engine::core::Stage::Init);
    moduleRegistry.callStage(engine::core::Stage::Input);
    moduleRegistry.callStage(engine::core::Stage::Update);
    moduleRegistry.callStage(engine::core::Stage::Render);
    moduleRegistry.callStage(engine::core::Stage::Cleanup);

    return 0;
}