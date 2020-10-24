#pragma once

#include "engine/core/app.hpp"
#include "engine/core/module.hpp"
#include "engine/maths/time.hpp"

namespace engine::core {
    class Engine {
      public:
        explicit Engine(App* app);

        void run();

        void requestStop();

        [[nodiscard]] App* getApp() const;
        [[nodiscard]] ModuleRegistry getModuleRegistry() const;

        [[nodiscard]] bool isRunning() const;

        void setUpsLimit(float ups);
        void setFpsLimit(float fps);

        const maths::Time& getDeltaUpdate() const;
        const maths::Time& getDeltaRender() const;
        uint32_t getUps() const;
        uint32_t getFps() const;

      private:
        App* m_app;
        ModuleRegistry m_moduleRegistry;

        bool m_running = false;

        float m_upsLimit = 20.0f, m_fpsLimit = 60.0f;
        maths::DeltaTime m_deltaUpdate, m_deltaRender;
        maths::ElapsedTime m_elapsedUpdate, m_elapsedRender;
        maths::ChangePerSecond m_ups, m_fps;
    };
} // namespace engine::core