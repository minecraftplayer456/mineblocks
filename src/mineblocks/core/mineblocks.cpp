#include "mineblocks.hpp"

#include <spdlog/spdlog.h>

namespace mineblocks::core {
    Mineblocks::Mineblocks()
        : App("Mineblocks", {0, 1, 0})
    {
    }

    std::vector<engine::core::Stage> Mineblocks::setupStages()
    {
        return {engine::core::Stage::init};
    }

    void Mineblocks::init()
    {
        spdlog::info("Mineblocks init");
    }
} // namespace mineblocks::core