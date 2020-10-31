#pragma once

#include "devices/logical_device.hpp"

namespace mineblocks {
    class CommandPool {
      public:
        CommandPool(const LogicalDevice* logicalDevice);
        ~CommandPool();

        [[nodiscard]] const VkCommandPool& getCommandPool() const;

      private:
        const LogicalDevice* m_logicalDevice;

        VkCommandPool m_commandPool;
    };
} // namespace mineblocks