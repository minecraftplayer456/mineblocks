#pragma once

#include <string>

#include <vulkan/vulkan_core.h>

namespace mineblocks {
    class Graphics {
      public:
        static void checkVk(VkResult result);
        static std::string stringifyVkResult(VkResult result);
    };
} // namespace mineblocks