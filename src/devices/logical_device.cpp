#include "logical_device.hpp"

#include <spdlog/spdlog.h>

namespace mineblocks {
    const std::vector<const char*> LogicalDevice::deviceExtensions = {
        VK_KHR_SWAPCHAIN_EXTENSION_NAME};

    LogicalDevice::LogicalDevice(const Instance* instance,
                                 const PhysicalDevice* physicalDevice,
                                 const Surface* surface)
        : m_instance(instance)
        , m_physicalDevice(physicalDevice)
        , m_surface(surface)
    {
        spdlog::debug("Create logical vulkan device");

        // Queues
        uint32_t queueFamilyCount;
        vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevice->getDevice(),
                                                 &queueFamilyCount, nullptr);
        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(m_physicalDevice->getDevice(),
                                                 &queueFamilyCount, queueFamilies.data());

        for (uint32_t i = 0; i < queueFamilyCount; i++) {
            if (queueFamilies[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                m_graphicsFamily = i;
            }

            VkBool32 presentSupport;
            vkGetPhysicalDeviceSurfaceSupportKHR(m_physicalDevice->getDevice(), i,
                                                 m_surface->getSurface(),
                                                 &presentSupport);

            if (queueFamilies[i].queueCount > 0 && presentSupport) {
                m_presentFamily = i;
            }

            if (queueFamilies[i].queueFlags & VK_QUEUE_COMPUTE_BIT) {
                m_computeFamily = i;
            }

            if (queueFamilies[i].queueFlags & VK_QUEUE_TRANSFER_BIT) {
                m_transferFamily = i;
            }

            if (m_graphicsFamily != -1 && m_presentFamily != -1 &&
                m_computeFamily != -1 && m_transferFamily != -1) {
                break;
            }
        }

        if (m_graphicsFamily == -1) {
            throw std::runtime_error("Could not find queue family supporting graphics");
        }

        // Logical device
        auto physicalDeviceFeatures = m_physicalDevice->getFeatures();

        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        float queuePriorities[1] = {0.0f};

        if (m_graphicsFamily != -1) {
            VkDeviceQueueCreateInfo createInfo = {};
            createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            createInfo.queueFamilyIndex = m_graphicsFamily;
            createInfo.queueCount = 1;
            createInfo.pQueuePriorities = queuePriorities;
            queueCreateInfos.emplace_back(createInfo);
        }
        else {
            m_graphicsQueue = VK_NULL_HANDLE;
        }

        if (m_computeFamily != -1 && m_computeFamily != m_graphicsFamily) {
            VkDeviceQueueCreateInfo createInfo = {};
            createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            createInfo.queueFamilyIndex = m_computeFamily;
            createInfo.queueCount = 1;
            createInfo.pQueuePriorities = queuePriorities;
            queueCreateInfos.emplace_back(createInfo);
        }
        else {
            m_computeFamily = m_graphicsFamily;
        }

        if (m_transferFamily != -1 && m_transferFamily != m_graphicsFamily &&
            m_transferFamily != m_computeFamily) {
            VkDeviceQueueCreateInfo createInfo = {};
            createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            createInfo.queueFamilyIndex = m_transferFamily;
            createInfo.queueCount = 1;
            createInfo.pQueuePriorities = queuePriorities;
            queueCreateInfos.emplace_back(createInfo);
        }
        else {
            m_transferFamily = m_graphicsFamily;
        }

        VkPhysicalDeviceFeatures enabledFeatures = {};

        // TODO Add features

        VkDeviceCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;

        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        createInfo.pQueueCreateInfos = queueCreateInfos.data();

        auto instanceValidationLayers = m_instance->getValidationLayers();
        if (!instanceValidationLayers.empty()) {
            createInfo.enabledLayerCount =
                static_cast<uint32_t>(instanceValidationLayers.size());
            createInfo.ppEnabledLayerNames = instanceValidationLayers.data();
        }

        createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
        createInfo.ppEnabledExtensionNames = deviceExtensions.data();
        createInfo.pEnabledFeatures = &enabledFeatures;

        Graphics::checkVk(vkCreateDevice(physicalDevice->getDevice(), &createInfo,
                                         nullptr, &m_logicalDevice));

        vkGetDeviceQueue(m_logicalDevice, m_graphicsFamily, 0, &m_graphicsQueue);
        vkGetDeviceQueue(m_logicalDevice, m_presentFamily, 0, &m_presentQueue);
        vkGetDeviceQueue(m_logicalDevice, m_computeFamily, 0, &m_computeQueue);
        vkGetDeviceQueue(m_logicalDevice, m_transferFamily, 0, &m_transferQueue);
    }

    LogicalDevice::~LogicalDevice()
    {
        spdlog::debug("Destroy vulkan logical device");

        Graphics::checkVk(vkDeviceWaitIdle(m_logicalDevice));
        vkDestroyDevice(m_logicalDevice, nullptr);
    }

    const VkDevice& LogicalDevice::getDevice() const
    {
        return m_logicalDevice;
    }

    const VkPhysicalDeviceFeatures& LogicalDevice::getEnabledFeatures() const
    {
        return m_enabledFeatures;
    }

    const VkQueue& LogicalDevice::getGraphicsQueue() const
    {
        return m_graphicsQueue;
    }

    const VkQueue& LogicalDevice::getPresentQueue() const
    {
        return m_presentQueue;
    }

    const VkQueue& LogicalDevice::getComputeQueue() const
    {
        return m_computeQueue;
    }

    const VkQueue& LogicalDevice::getTransferQueue() const
    {
        return m_transferQueue;
    }

    uint32_t LogicalDevice::getGraphicsFamily() const
    {
        return m_graphicsFamily;
    }

    uint32_t LogicalDevice::getPresentFamily() const
    {
        return m_presentFamily;
    }

    uint32_t LogicalDevice::getComputeFamily() const
    {
        return m_computeFamily;
    }

    uint32_t LogicalDevice::getTransferFamily() const
    {
        return m_transferFamily;
    }
} // namespace mineblocks