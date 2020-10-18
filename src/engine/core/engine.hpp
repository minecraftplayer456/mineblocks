#pragma once

#include "engine/core/app.hpp"
#include "engine/core/module.hpp"

namespace engine::core {
    class Engine {
      public:
        Engine(App app);

        void run();

      private:
        App m_app;

        ModuleRegistry m_moduleRegistry;
    };
} // namespace engine::core