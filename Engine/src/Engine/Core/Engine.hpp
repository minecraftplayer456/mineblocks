#pragma once

#include "Engine/Core/Application.hpp"
#include "Engine/Core/Event.hpp"
#include "Engine/Maths/Time.hpp"

namespace Engine {
    class Engine {
      public:
        explicit Engine(std::unique_ptr<Application> app);

        auto Run() -> int;
        void RequestClose();

        [[nodiscard]] auto GetApplication() -> std::unique_ptr<Application>&;

        [[nodiscard]] auto GetModuleManager() -> ModuleManager&;

        void SetUpsLimit(float ups);
        void SetFpsLimit(float fps);

        [[nodiscard]] auto GetDeltaUpdate() const -> const Time&;
        [[nodiscard]] auto GetDeltaRender() const -> const Time&;
        [[nodiscard]] auto GetUps() const -> uint32_t;
        [[nodiscard]] auto GetFps() const -> uint32_t;

      private:
        void Init();
        void Loop();
        void Cleanup();

        bool running = false;

        std::unique_ptr<Application> app;

        float upsLimit = 20.0f, fpsLimit = 60.0f;
        DeltaTime deltaUpdate, deltaRender;
        ElapsedTime elapsedUpdate, elapsedRender;
        ChangePerSecond upsCounter, fpsCounter;
    };
} // namespace Engine