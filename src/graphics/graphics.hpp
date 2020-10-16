#pragma once

#include <string>

#include <vulkan/vulkan.h>

namespace engine::graphics {
    void assertVkResult(VkResult result);

    std::string stringifyVkResult(VkResult& result);
} // namespace engine::graphics
