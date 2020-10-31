#pragma once

#include <memory>
#include <vector>

#include <vulkan/vulkan.h>

#include "devices/window.hpp"
#include "graphics/graphics.hpp"

namespace mineblocks {
    const std::string APP_NAME = "Mineblocks";
    const uint32_t APP_VERSION = VK_MAKE_VERSION(0, 1, 0);
    const std::string ENGINE_NAME = "Engine";
    const uint32_t ENGINE_VERSION = VK_MAKE_VERSION(0, 1, 0);

    const bool enableValidationLayers = true;
    const std::vector<const char*> validationLayerNames = {"VK_LAYER_KHRONOS_validation"};

    VkResult
    fVkCreateDebugUtilsMessengerEXT(VkInstance instance,
                                    const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
                                    const VkAllocationCallbacks* pAllocator,
                                    VkDebugUtilsMessengerEXT* pDebugMessenger);
    void fVkDestroyDebugUtilsMessengerEXT(VkInstance instance,
                                          VkDebugUtilsMessengerEXT messenger,
                                          const VkAllocationCallbacks* pAllocator);

    class Instance {
      public:
        Instance();

        ~Instance();

        [[nodiscard]] VkInstance getInstance() const;

        [[nodiscard]] std::vector<const char*> getValidationLayers() const;

      private:
        std::vector<const char*> m_validationLayers;

        VkInstance m_instance{};

        VkDebugUtilsMessengerCreateInfoEXT m_debugCreateInfo{};
        VkDebugUtilsMessengerEXT m_debugMessenger{};
    };
} // namespace mineblocks
