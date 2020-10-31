#include "command_pool.hpp"

#include <spdlog/spdlog.h>

namespace mineblocks {
    CommandPool::CommandPool(const LogicalDevice* logicalDevice)
        : m_logicalDevice(logicalDevice)
    {
        spdlog::debug("Create command pool");

        VkCommandPoolCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        createInfo.queueFamilyIndex = logicalDevice->getGraphicsFamily();
        createInfo.flags = 0; // Optional

        Graphics::checkVk(vkCreateCommandPool(m_logicalDevice->getDevice(), &createInfo,
                                              nullptr, &m_commandPool));
    }

    CommandPool::~CommandPool()
    {
        spdlog::debug("Destroy command pool");

        vkDestroyCommandPool(m_logicalDevice->getDevice(), m_commandPool, nullptr);
    }

    const VkCommandPool& CommandPool::getCommandPool() const
    {
        return m_commandPool;
    }
} // namespace mineblocks