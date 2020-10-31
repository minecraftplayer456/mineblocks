#include "physical_device.hpp"

#include <map>
#include <vector>

#include <spdlog/spdlog.h>

#include "devices/logical_device.hpp"

namespace mineblocks {
    PhysicalDevice::PhysicalDevice(Instance* instance)
        : m_instance(instance)
    {
        spdlog::debug("Gather physical devices");

        uint32_t physicalDevicesCount;
        vkEnumeratePhysicalDevices(m_instance->getInstance(), &physicalDevicesCount,
                                   nullptr);
        std::vector<VkPhysicalDevice> physicalDevices(physicalDevicesCount);
        vkEnumeratePhysicalDevices(m_instance->getInstance(), &physicalDevicesCount,
                                   physicalDevices.data());

        std::multimap<uint32_t, VkPhysicalDevice> rankedDevices;
        for (const auto& device : physicalDevices) {
            bool suitable = true;
            uint32_t score = 0;

            uint32_t extensionPropertyCount;
            vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionPropertyCount,
                                                 nullptr);
            std::vector<VkExtensionProperties> extensionProperties(
                extensionPropertyCount);
            vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionPropertyCount,
                                                 extensionProperties.data());

            for (const char* currentExtension : LogicalDevice::deviceExtensions) {
                bool found = false;

                for (const auto& extension : extensionProperties) {
                    if (strcmp(currentExtension, extension.extensionName) == 0) {
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    suitable = false;
                }
            }

            VkPhysicalDeviceProperties physicalDeviceProperties;
            VkPhysicalDeviceFeatures physicalDeviceFeatures;
            vkGetPhysicalDeviceProperties(device, &physicalDeviceProperties);
            vkGetPhysicalDeviceFeatures(device, &physicalDeviceFeatures);

            if (physicalDeviceProperties.deviceType ==
                VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
                score += 1000;

            score += physicalDeviceProperties.limits.maxImageDimension2D;

            if (suitable) {
                rankedDevices.emplace(score, device);
            }
        }

        if (rankedDevices.rbegin()->first > 0) {
            m_physicalDevice = rankedDevices.rbegin()->second;
        }
        else {
            throw std::runtime_error("Could not find suitable device");
        }

        vkGetPhysicalDeviceProperties(m_physicalDevice, &m_properties);
        vkGetPhysicalDeviceFeatures(m_physicalDevice, &m_features);
        vkGetPhysicalDeviceMemoryProperties(m_physicalDevice, &m_memoryProperties);

        spdlog::debug("Found suitable physical device: {}", m_properties.deviceName);
    }

    const VkPhysicalDevice& PhysicalDevice::getDevice() const
    {
        return m_physicalDevice;
    }

    const VkPhysicalDeviceProperties& PhysicalDevice::getProperties() const
    {
        return m_properties;
    }

    const VkPhysicalDeviceFeatures& PhysicalDevice::getFeatures() const
    {
        return m_features;
    }

    const VkPhysicalDeviceMemoryProperties& PhysicalDevice::getMemoryProperties() const
    {
        return m_memoryProperties;
    }
} // namespace mineblocks