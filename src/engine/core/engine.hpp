#pragma once

#include "engine/core/app.hpp"
#include "engine/core/module.hpp"

namespace engine::core {
    class Engine {
      public:
        Engine(App app);

        void run();

        void requestStop();

        App getApp() const;

        ModuleRegistry getModuleRegistry() const;

        bool isRunning() const;

      private:
        App m_app;
        ModuleRegistry m_moduleRegistry;

        bool m_running = false;

        void registerModules();
    };
} // namespace engine::core