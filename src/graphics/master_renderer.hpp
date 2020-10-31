#pragma once

#include <memory>

#include "devices/instance.hpp"
#include "devices/physical_device.hpp"
#include "devices/surface.hpp"
#include "devices/window.hpp"

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
    };
} // namespace mineblocks