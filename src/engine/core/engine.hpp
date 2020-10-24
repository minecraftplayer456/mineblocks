#pragma once

#include "engine/core/app.hpp"
#include "engine/core/module.hpp"

namespace engine::core {
    class Engine {
      public:
        explicit Engine(App* app);

        void run();

        void requestStop();

        [[nodiscard]] App* getApp() const;

        [[nodiscard]] ModuleRegistry getModuleRegistry() const;

        [[nodiscard]] bool isRunning() const;

      private:
        App* m_app;

        ModuleRegistry m_moduleRegistry;

        bool m_running = false;
    };
} // namespace engine::core