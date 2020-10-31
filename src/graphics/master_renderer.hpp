#pragma once

#include <memory>

#include "graphics/pipelines/graphics_pipeline.hpp"

namespace mineblocks {
    class Application;

    class MasterRenderer {
      public:
        MasterRenderer(Window* window);

        void init();
        void render(Application* app);
        void cleanup();

      private:
        Instance m_instance;
        PhysicalDevice m_physicalDevice;
        Surface m_surface;
        LogicalDevice m_logicalDevice;
        Swapchain m_swapchain;
        Renderpass m_renderpass;
        GraphicsPipeline m_graphicsPipeline;
    };
} // namespace mineblocks