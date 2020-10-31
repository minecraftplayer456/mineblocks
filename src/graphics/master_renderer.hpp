#pragma once

#include <memory>

#include "graphics/renderpass/swapchain.hpp"

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
        Swampchain m_swapchain;
    };
} // namespace mineblocks