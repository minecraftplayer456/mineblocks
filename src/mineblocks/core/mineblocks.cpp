#include "mineblocks.hpp"

#include <engine/devices/glfw.hpp>

namespace mineblocks::core {
    Mineblocks::Mineblocks()
        : App("Mineblocks", {0, 1, 0})
    {
        addSubmodule<engine::devices::Glfw>();
    }
} // namespace mineblocks::core