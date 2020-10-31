#pragma once

#include <memory>

#include "devices/instance.hpp"
#include "devices/physical_device.hpp"

namespace mineblocks {
    class Application;

    class MasterRenderer {
      public:
        MasterRenderer();

        void init();
        void render(Application* app);
        void cleanup();

      private:
        Instance m_instance;
        PhysicalDevice m_physicalDevice;
    };
} // namespace mineblocks