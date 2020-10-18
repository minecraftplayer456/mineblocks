#pragma once

#include <vulkan/vulkan.hpp>

#include "../../utils/app_info.hpp"

namespace engine::devices::graphics {
    class VulkanDebug {
      public:
        void create(const utils::AppInfo& appInfo);

        void destroy(const VkInstance& instance);

        void setupDebugExtension(const VkInstance& instance);

        VkDebugUtilsMessengerCreateInfoEXT* getDebugCreateInfo();

      private:
        VkDebugUtilsMessengerCreateInfoEXT m_debugCreateInfo;
        VkDebugUtilsMessengerEXT m_debugExtension;
    };
} // namespace engine::devices::graphics
