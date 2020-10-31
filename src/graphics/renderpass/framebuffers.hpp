#pragma once

#include "graphics/renderpass/renderpass.hpp"

namespace mineblocks {
    class Framebuffers {
      public:
        Framebuffers(const LogicalDevice* logicalDevice, const Renderpass* renderpass,
                     const Swapchain* swapchain);
        ~Framebuffers();

        [[nodiscard]] const std::vector<VkFramebuffer>& getFramebuffers() const;

      private:
        const LogicalDevice* m_logicalDevice;

        std::vector<VkFramebuffer> m_framebuffers;
    };
} // namespace mineblocks
