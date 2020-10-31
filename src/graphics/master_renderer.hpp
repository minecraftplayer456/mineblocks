#pragma once

#include <memory>

#include "graphics/renderpass/renderpass.hpp"

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
    };
} // namespace mineblocks