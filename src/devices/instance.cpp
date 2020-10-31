#include "instance.hpp"

#include <spdlog/spdlog.h>

namespace mineblocks {
    VKAPI_ATTR VkBool32 VKAPI_CALL
    debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                  [[maybe_unused]] VkDebugUtilsMessageTypeFlagsEXT messageTypes,
                  const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
                  [[maybe_unused]] void* pUserData)
    {
        spdlog::level::level_enum level = spdlog::level::debug;
        switch (messageSeverity) {
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
                level = spdlog::level::info;
                break;
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
                level = spdlog::level::warn;
                break;
            case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
                level = spdlog::level::err;
                break;
            default:
                break;
        }

        spdlog::log(level, "Vulkan: {}", pCallbackData->pMessage);
        return VK_SUCCESS;
    }

    VkResult
    fVkCreateDebugUtilsMessengerEXT(VkInstance instance,
                                    const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
                                    const VkAllocationCallbacks* pAllocator,
                                    VkDebugUtilsMessengerEXT* pDebugMessenger)
    {
        auto func = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(
            vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT"));
        if (func)
            return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }

    void fVkDestroyDebugUtilsMessengerEXT(VkInstance instance,
                                          VkDebugUtilsMessengerEXT messenger,
                                          const VkAllocationCallbacks* pAllocator)
    {
        auto func = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(
            vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT"));
        if (func)
            return func(instance, messenger, pAllocator);
    }

    Instance::Instance()
    {
        spdlog::debug("Create vulkan instance");

        VkApplicationInfo appInfo = {};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = ENGINE_NAME.c_str();
        appInfo.applicationVersion = APP_VERSION;
        appInfo.pEngineName = ENGINE_NAME.c_str();
        appInfo.engineVersion = ENGINE_VERSION;
        appInfo.apiVersion = VK_API_VERSION_1_2;

        VkInstanceCreateInfo createInfo = {};

        // Extensions
        auto [glfwExtensions, glfwExtensionsCount] = Window::getExtensions();
        std::vector<const char*> extensions(glfwExtensions,
                                            glfwExtensions + glfwExtensionsCount);

        // Validation Layers
        std::vector<const char*> validationLayers;
        if (enableValidationLayers) {
            // Validation Layers
            extensions.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
            uint32_t layerCount;
            vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
            std::vector<VkLayerProperties> layers(layerCount);
            vkEnumerateInstanceLayerProperties(&layerCount, layers.data());

            validationLayers = validationLayerNames;

            for (int i = 0; i < validationLayers.size(); i++) {
                auto layerName = validationLayers[i];
                bool found = false;
                for (const auto& layer : layers) {
                    if (strcmp(layerName, layer.layerName) == 0) {
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    spdlog::error("Could not find validation layer: {}", layerName);
                    validationLayers.erase(validationLayers.begin() + i);
                }
            }

            // Debug Messenger
            m_debugCreateInfo = {};
            m_debugCreateInfo.sType =
                VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
            m_debugCreateInfo.messageSeverity =
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
            m_debugCreateInfo.messageType =
                VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
            m_debugCreateInfo.pfnUserCallback = &debugCallback;

            createInfo.pNext = &m_debugCreateInfo;
        }

        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();
        createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
        createInfo.ppEnabledLayerNames = validationLayers.data();

        Graphics::checkVk(vkCreateInstance(&createInfo, nullptr, &m_instance));

        // Debug Messenger
        if (enableValidationLayers) {
            Graphics::checkVk(fVkCreateDebugUtilsMessengerEXT(
                m_instance, &m_debugCreateInfo, nullptr, &m_debugMessenger));
        }
    }

    Instance::~Instance()
    {
        spdlog::debug("Destroy vulkan instance");

        fVkDestroyDebugUtilsMessengerEXT(m_instance, m_debugMessenger, nullptr);
        vkDestroyInstance(m_instance, nullptr);
    }

    VkInstance Instance::getInstance() const
    {
        return m_instance;
    }
} // namespace mineblocks