#pragma once

#include "graphics/renderpass/swapchain.hpp"

namespace mineblocks {
    class Renderpass {
      public:
        Renderpass(const LogicalDevice* logicalDevice, const Surface* surface);
        ~Renderpass();

        const VkRenderPass& getRenderPass() const;

      private:
        const LogicalDevice* m_logicalDevice;

        VkRenderPass m_renderPass;
    };
} // namespace mineblocks
