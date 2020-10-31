#pragma once

#include "graphics/pipelines/shader.hpp"
#include "graphics/renderpass/renderpass.hpp"

namespace mineblocks {
    class GraphicsPipeline {
      public:
        GraphicsPipeline(const LogicalDevice* logicalDevice, const Swapchain* swapchain,
                         const Renderpass* renderpass);
        ~GraphicsPipeline();

        [[nodiscard]] const VkPipeline& getPipeline() const;
        [[nodiscard]] const VkPipelineLayout& getPipelineLayout() const;

      private:
        const LogicalDevice* m_logicalDevice;

        VkPipeline m_pipeline;
        VkPipelineLayout m_pipelineLayout;
    };
} // namespace mineblocks