#pragma once

#include <memory>
#include <string>

#include <vulkan/vulkan.h>

#include "../../utils/app_info.hpp"
#include "vulkan_debug.hpp"

namespace engine::devices::graphics {
    const std::string engineName = "engine";
    const utils::Version engineVersion = utils::Version(0, 1, 0);
    const int vkApiVersion = VK_VERSION_1_2;

    class Instance {
      public:
        void create(const utils::AppInfo& info);

        void destroy();

        [[nodiscard]] VkInstance getInstance() const;

      private:
        VkInstance m_instance;

        VulkanDebug m_vulkanDebug;

        std::vector<const char*> getRequiredExtensions(const utils::AppInfo& appInfo);

        std::vector<const char*> getValidationLayers(const utils::AppInfo& appInfo);
    };
} // namespace engine::devices::graphics