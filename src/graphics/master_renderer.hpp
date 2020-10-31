#pragma once

#include <memory>

#include "devices/logical_device.hpp"

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
    };
} // namespace mineblocks