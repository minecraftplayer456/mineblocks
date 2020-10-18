#include "vulkan_debug.hpp"

#include <spdlog/spdlog.h>

#include "graphics/graphics.hpp"

namespace engine::devices::graphics {
    static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
        VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
        VkDebugUtilsMessageTypeFlagsEXT messageType,
        const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData)
    {
        spdlog::level::level_enum level;

        switch (messageSeverity) {
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
                level = spdlog::level::debug;
                break;
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
                level = spdlog::level::info;
                break;
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
                level = spdlog::level::warn;
                break;
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
                level = spdlog::level::err;
                break;
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_FLAG_BITS_MAX_ENUM_EXT:
                level = spdlog::level::debug;
                break;
        }

        spdlog::log(level, std::string(pCallbackData->pMessage));

        return VK_FALSE;
    }

    void VulkanDebug::create(const utils::AppInfo& appInfo)
    {
        m_debugCreateInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
        m_debugCreateInfo.messageSeverity =
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT |
            VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT;
        m_debugCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                                        VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                                        VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
        m_debugCreateInfo.pfnUserCallback = debugCallback;
    }

    void VulkanDebug::destroy(const VkInstance& instance)
    {
        auto destroyDebugUtilsMessengerEXTDispatcher =
            reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(
                vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT"));

        destroyDebugUtilsMessengerEXTDispatcher(instance, m_debugExtension, nullptr);
    }

    void VulkanDebug::setupDebugExtension(const VkInstance& instance)
    {
        auto createDebugUtilsMessengerEXTDispatcher =
            reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(
                vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT"));

        if (!createDebugUtilsMessengerEXTDispatcher) {
            throw std::runtime_error("Could not load vkDestroyDebugUtilsMessengerEXT");
        }

        createDebugUtilsMessengerEXTDispatcher(instance, &m_debugCreateInfo, nullptr,
                                               &m_debugExtension);
    }

    VkDebugUtilsMessengerCreateInfoEXT* VulkanDebug::getDebugCreateInfo()
    {
        return &m_debugCreateInfo;
    }
} // namespace engine::devices::graphics