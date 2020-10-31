#include "command_buffer.hpp"

#include <spdlog/spdlog.h>

namespace mineblocks {
    CommandBuffer::CommandBuffer(const LogicalDevice* logicalDevice,
                                 const CommandPool* commandPool, bool begin,
                                 VkQueueFlagBits queueType,
                                 VkCommandBufferLevel bufferLevel)
        : m_logicalDevice(logicalDevice)
        , m_commandPool(commandPool)
    {
        spdlog::debug("Create command buffer");

        VkCommandBufferAllocateInfo commandBufferAllocateInfo = {};
        commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        commandBufferAllocateInfo.commandPool = commandPool->getCommandPool();
        commandBufferAllocateInfo.level = bufferLevel;
        commandBufferAllocateInfo.commandBufferCount = 1;

        Graphics::checkVk(vkAllocateCommandBuffers(
            logicalDevice->getDevice(), &commandBufferAllocateInfo, &m_commandBuffer));

        switch (queueType) {
            case VK_QUEUE_GRAPHICS_BIT:
                m_queue = &logicalDevice->getGraphicsQueue();
                break;
            case VK_QUEUE_COMPUTE_BIT:
                m_queue = &logicalDevice->getComputeQueue();
                break;
            default:
                break;
        }

        if (begin) {
            this->begin();
        }
    }

    CommandBuffer::~CommandBuffer()
    {
        spdlog::debug("Destroy command buffer");

        vkFreeCommandBuffers(m_logicalDevice->getDevice(),
                             m_commandPool->getCommandPool(), 1, &m_commandBuffer);
    }

    void CommandBuffer::begin(VkCommandBufferUsageFlags usage)
    {
        if (m_running)
            return;

        VkCommandBufferBeginInfo beginInfo = {};
        beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
        beginInfo.flags = usage;

        Graphics::checkVk(vkBeginCommandBuffer(m_commandBuffer, &beginInfo));

        m_running = true;
    }

    void CommandBuffer::end()
    {
        if (!m_running)
            return;

        Graphics::checkVk(vkEndCommandBuffer(m_commandBuffer));

        m_running = false;
    }

    void CommandBuffer::submitIdle()
    {
        if (m_running) {
            end();
        }

        VkSubmitInfo submitInfo = {};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &m_commandBuffer;

        VkFenceCreateInfo fenceCreateInfo = {};
        fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;

        VkFence fence;
        Graphics::checkVk(vkCreateFence(m_logicalDevice->getDevice(), &fenceCreateInfo,
                                        nullptr, &fence));
        Graphics::checkVk(vkResetFences(m_logicalDevice->getDevice(), 1, &fence));
        Graphics::checkVk(vkQueueSubmit(*m_queue, 1, &submitInfo, fence));
        Graphics::checkVk(vkWaitForFences(m_logicalDevice->getDevice(), 1, &fence,
                                          VK_TRUE, std::numeric_limits<uint64_t>::max()));
        vkDestroyFence(m_logicalDevice->getDevice(), fence, nullptr);
    }

    void CommandBuffer::submit(const VkSemaphore& waitSemaphore,
                               const VkSemaphore& signalSemaphore, const VkFence& fence)
    {
        if (m_running) {
            end();
        }

        VkSubmitInfo submitInfo = {};
        submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
        submitInfo.commandBufferCount = 1;
        submitInfo.pCommandBuffers = &m_commandBuffer;

        if (waitSemaphore != VK_NULL_HANDLE) {
            static VkPipelineStageFlags submitPipelineStages =
                VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

            submitInfo.pWaitDstStageMask = &submitPipelineStages;
            submitInfo.waitSemaphoreCount = 1;
            submitInfo.pWaitSemaphores = &waitSemaphore;
        }

        if (signalSemaphore != VK_NULL_HANDLE) {
            submitInfo.signalSemaphoreCount = 1;
            submitInfo.pSignalSemaphores = &signalSemaphore;
        }

        if (fence != VK_NULL_HANDLE) {
            Graphics::checkVk(vkResetFences(m_logicalDevice->getDevice(), 1, &fence));
        }

        Graphics::checkVk(vkQueueSubmit(*m_queue, 1, &submitInfo, fence));
    }

    const VkCommandBuffer& CommandBuffer::getCommandBuffer() const
    {
        return m_commandBuffer;
    }

    bool CommandBuffer::isRunning() const
    {
        return m_running;
    }
} // namespace mineblocks