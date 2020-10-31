#pragma once

#include "graphics/commands/command_pool.hpp"

namespace mineblocks {
    class CommandBuffer {
      public:
        CommandBuffer(const LogicalDevice* logicalDevice, const CommandPool* commandPool,
                      bool begin = true,
                      VkQueueFlagBits queueType = VK_QUEUE_GRAPHICS_BIT,
                      VkCommandBufferLevel bufferLevel = VK_COMMAND_BUFFER_LEVEL_PRIMARY);
        ~CommandBuffer();

        void begin(VkCommandBufferUsageFlags usage =
                       VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT);

        void end();

        void submitIdle();

        void submit(const VkSemaphore& waitSemaphore = VK_NULL_HANDLE,
                    const VkSemaphore& signalSemaphore = VK_NULL_HANDLE,
                    const VkFence& fence = VK_NULL_HANDLE);

        [[nodiscard]] const VkCommandBuffer& getCommandBuffer() const;

        [[nodiscard]] bool isRunning() const;

      private:
        const LogicalDevice* m_logicalDevice;
        const CommandPool* m_commandPool;

        bool m_running = false;

        const VkQueue* m_queue;

        VkCommandBuffer m_commandBuffer;
    };
} // namespace mineblocks