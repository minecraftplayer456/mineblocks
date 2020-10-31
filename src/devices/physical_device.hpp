#pragma once

#include "devices/instance.hpp"

namespace mineblocks {
    class PhysicalDevice {
      public:
        explicit PhysicalDevice(const Instance* instance);

        [[nodiscard]] const VkPhysicalDevice& getDevice() const;
        [[nodiscard]] const VkPhysicalDeviceProperties& getProperties() const;
        [[nodiscard]] const VkPhysicalDeviceFeatures& getFeatures() const;
        [[nodiscard]] const VkPhysicalDeviceMemoryProperties& getMemoryProperties() const;

      private:
        const Instance* m_instance;

        VkPhysicalDevice m_physicalDevice = VK_NULL_HANDLE;
        VkPhysicalDeviceProperties m_properties{};
        VkPhysicalDeviceFeatures m_features{};
        VkPhysicalDeviceMemoryProperties m_memoryProperties{};
    };
} // namespace mineblocks
