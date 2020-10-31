#pragma once

#include <memory>

#include "devices/instance.hpp"

namespace mineblocks {
    class Application;

    class MasterRenderer {
      public:
        void init();
        void render(Application* app);
        void cleanup();

      private:
        Instance m_instance;
    };
} // namespace mineblocks