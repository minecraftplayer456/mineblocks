#include "mineblocks.hpp"

#include <spdlog/spdlog.h>

namespace mineblocks::core {
    Mineblocks::Mineblocks()
        : App("Mineblocks", {0, 1, 0})
    {
    }
} // namespace mineblocks::core