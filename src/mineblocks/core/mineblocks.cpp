#include "mineblocks.hpp"

#include <engine/test/test_module.hpp>

namespace mineblocks::core {
    Mineblocks::Mineblocks()
        : App("Mineblocks", {0, 1, 0})
    {
        addSubmodule<engine::test::TestModule>();
    }
} // namespace mineblocks::core