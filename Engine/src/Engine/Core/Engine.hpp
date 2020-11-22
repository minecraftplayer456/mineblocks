#pragma once

#include "Engine/Core/Application.hpp"
#include "Engine/Core/Event/Event.hpp"
#include "Engine/Maths/Time.hpp"

namespace Engine {
    class Engine {
      public:
        explicit Engine(Application* p_app);

        void Run();
        void RequestClose();

        [[nodiscard]] Application* GetApplication() const;

        [[nodiscard]] ModuleManager& GetModuleManager();
        [[nodiscard]] EventBus& GetEventBus();

        void SetUpsLimit(float ups);
        void SetFpsLimit(float fps);

        const Time& GetDeltaUpdate() const;
        const Time& GetDeltaRender() const;
        uint32_t GetUps() const;
        uint32_t GetFps() const;

      private:
        void Init();
        void Loop();
        void Cleanup();

        bool running = false;

        Application* app = nullptr;

        ModuleManager moduleManager;
        EventBus eventBus;

        float upsLimit = 20.0f, fpsLimit = 60.0f;
        DeltaTime deltaUpdate, deltaRender;
        ElapsedTime elapsedUpdate, elapsedRender;
        ChangePerSecond ups, fps;
    };
} // namespace Engine