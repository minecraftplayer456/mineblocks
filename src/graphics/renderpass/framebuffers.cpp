#include "framebuffers.hpp"

#include <spdlog/spdlog.h>

namespace mineblocks {
    Framebuffers::Framebuffers(const LogicalDevice* logicalDevice,
                               const Renderpass* renderpass, const Swapchain* swapchain)
        : m_logicalDevice(logicalDevice)
    {
        spdlog::debug("Create framebuffers");

        const auto& swapchainImageViews = swapchain->getImageViews();

        m_framebuffers.resize(swapchainImageViews.size());

        for (size_t i = 0; i < swapchainImageViews.size(); i++) {
            VkImageView attachments[] = {swapchainImageViews[i]};

            VkFramebufferCreateInfo framebufferInfo{};
            framebufferInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
            framebufferInfo.renderPass = renderpass->getRenderPass();
            framebufferInfo.attachmentCount = 1;
            framebufferInfo.pAttachments = attachments;
            framebufferInfo.width = swapchain->getExtent().width;
            framebufferInfo.height = swapchain->getExtent().height;
            framebufferInfo.layers = 1;

            Graphics::checkVk(vkCreateFramebuffer(logicalDevice->getDevice(),
                                                  &framebufferInfo, nullptr,
                                                  &m_framebuffers[i]));
        }
    }

    Framebuffers::~Framebuffers()
    {
        spdlog::debug("Destroy framebuffers");

        for (const auto& framebuffer : m_framebuffers) {
            vkDestroyFramebuffer(m_logicalDevice->getDevice(), framebuffer, nullptr);
        }
    }

    const std::vector<VkFramebuffer>& Framebuffers::getFramebuffers() const
    {
        return m_framebuffers;
    }
} // namespace mineblocks