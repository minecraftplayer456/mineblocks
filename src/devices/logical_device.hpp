#pragma once

#include <vector>

#include "devices/physical_device.hpp"

namespace mineblocks {
    class LogicalDevice {
      public:
        static const std::vector<const char*> deviceExtensions;

      private:
    };
} // namespace mineblocks