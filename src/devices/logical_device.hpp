#pragma once

#include <vector>

#include "devices/physical_device.hpp"
#include "devices/surface.hpp"

namespace mineblocks {
    class LogicalDevice {
      public:
        static const std::vector<const char*> deviceExtensions;

        LogicalDevice(const Instance* instance, const PhysicalDevice* physicalDevice,
                      const Surface* surface);
        ~LogicalDevice();

        [[nodiscard]] const VkDevice& getDevice() const;
        [[nodiscard]] const VkPhysicalDeviceFeatures& getEnabledFeatures() const;

        [[nodiscard]] const VkQueue& getGraphicsQueue() const;
        [[nodiscard]] const VkQueue& getPresentQueue() const;
        [[nodiscard]] const VkQueue& getComputeQueue() const;
        [[nodiscard]] const VkQueue& getTransferQueue() const;

        [[nodiscard]] uint32_t getGraphicsFamily() const;
        [[nodiscard]] uint32_t getPresentFamily() const;
        [[nodiscard]] uint32_t getComputeFamily() const;
        [[nodiscard]] uint32_t getTransferFamily() const;

      private:
        const Instance* m_instance;
        const PhysicalDevice* m_physicalDevice;
        const Surface* m_surface;

        VkDevice m_logicalDevice;
        VkPhysicalDeviceFeatures m_enabledFeatures{};

        uint32_t m_graphicsFamily = -1;
        uint32_t m_presentFamily = -1;
        uint32_t m_computeFamily = -1;
        uint32_t m_transferFamily = -1;

        VkQueue m_graphicsQueue = VK_NULL_HANDLE;
        VkQueue m_presentQueue = VK_NULL_HANDLE;
        VkQueue m_computeQueue = VK_NULL_HANDLE;
        VkQueue m_transferQueue = VK_NULL_HANDLE;
    };
} // namespace mineblocks