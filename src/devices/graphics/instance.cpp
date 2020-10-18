#include "instance.hpp"

#include <cstring>
#include <string>

#include <spdlog/spdlog.h>

#include "../window/glfw.hpp"
#include "graphics/graphics.hpp"

namespace engine::devices::graphics {
    void Instance::create(const utils::AppInfo& info)
    {
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = info.m_appName.c_str();
        appInfo.applicationVersion = info.m_appVersion.asVkVersion();
        appInfo.pEngineName = engineName.c_str();
        appInfo.engineVersion = engineVersion.asVkVersion();
        appInfo.apiVersion = vkApiVersion;

        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;

        auto extensions = getRequiredExtensions(info);
        createInfo.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
        createInfo.ppEnabledExtensionNames = extensions.data();

        if (info.m_vulkanDebug) {
            m_vulkanDebug.create(info);

            auto validationLayers = getValidationLayers(info);
            createInfo.enabledLayerCount = validationLayers.size();
            createInfo.ppEnabledLayerNames = validationLayers.data();

            createInfo.pNext =
                (VkDebugUtilsMessengerCreateInfoEXT*)m_vulkanDebug.getDebugCreateInfo();
        }
        else {
            createInfo.enabledLayerCount = 0;
            createInfo.pNext = nullptr;
        }

        engine::graphics::assertVkResult(
            vkCreateInstance(&createInfo, nullptr, &m_instance));

        if (info.m_vulkanDebug) {
            m_vulkanDebug.setupDebugExtension(m_instance);
        }
    }

    void Instance::destroy()
    {
        m_vulkanDebug.destroy(m_instance);

        vkDestroyInstance(m_instance, nullptr);
    }

    std::vector<const char*>
    Instance::getRequiredExtensions(const utils::AppInfo& appInfo)
    {
        auto extensions = window::Glfw::getGlfwVulkanExtensions();

        if (appInfo.m_vulkanDebug) {
            extensions.emplace_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        }

        return extensions;
    }

    std::vector<const char*> Instance::getValidationLayers(const utils::AppInfo& appInfo)
    {
        std::vector<const char*> layers = appInfo.m_vulkanValidationLayers;

        uint32_t layerCount;
        vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

        std::vector<VkLayerProperties> availableLayers(layerCount);
        vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

        for (int i = 0; i < layers.size(); i++) {
            auto layerName = layers[i];
            bool layerFound = false;

            for (const auto& layerProperties : availableLayers) {
                if (strcmp(layerName, layerProperties.layerName) == 0) {
                    layerFound = true;
                    break;
                }
            }

            if (!layerFound) {
                spdlog::warn(
                    std::string("Vulkan validation layer not available: ", layerName));
                layers.erase(layers.begin() + i);
            }
        }

        return layers;
    }

    VkInstance Instance::getInstance() const
    {
        return m_instance;
    }
} // namespace engine::devices::graphics