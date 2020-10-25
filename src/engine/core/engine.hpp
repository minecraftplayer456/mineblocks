#pragma once

#include "engine/core/app.hpp"
#include "engine/core/module.hpp"
#include "engine/maths/time.hpp"

namespace engine::core {
    class Engine {
      public:
        static Engine* get();

        void run(App* app);

        ModuleManager* getModuleManager();

      private:
        ModuleManager m_moduleManager;
    };

    class EngineModule : public Module{
      public:
        EngineModule(App* app, ModuleManager* moduleManager);

        void run();

        void requestStop();

        [[nodiscard]] App* getApp() const;

        [[nodiscard]] bool isRunning() const;

        void setUpsLimit(float ups);
        void setFpsLimit(float fps);

        [[nodiscard]] const maths::Time& getDeltaUpdate() const;
        [[nodiscard]] const maths::Time& getDeltaRender() const;
        [[nodiscard]] uint32_t getUps() const;
        [[nodiscard]] uint32_t getFps() const;

      private:
        App* m_app;
        ModuleManager* m_moduleManager;

        bool m_running = false;

        float m_upsLimit = 20.0f, m_fpsLimit = 60.0f;
        maths::DeltaTime m_deltaUpdate, m_deltaRender;
        maths::ElapsedTime m_elapsedUpdate, m_elapsedRender;
        maths::ChangePerSecond m_ups, m_fps;
    };
} // namespace engine::core