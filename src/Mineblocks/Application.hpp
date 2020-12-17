#pragma once

#include "Mineblocks/Maths/Time.hpp"

namespace Mineblocks {
    class Application {
      public:
        void Run();
        void RequestClose();

        void SetUpsLimit(float upsLimit);
        void SetFpsLimit(float fpsLimit);

        [[nodiscard]] auto GetUps() const -> uint32_t;
        [[nodiscard]] auto GetFps() const -> uint32_t;

        [[nodiscard]] auto GetDeltaUpdate() const -> const Time&;
        [[nodiscard]] auto GetDeltaRender() const -> const Time&;

      private:
        bool running;

        Delta deltaUpdate, deltaRender;
        ElapsedTime elapsedUpdate, elapsedRender;
        ChangePerSecond ups, fps;
        float upsLimit = 20.0F, fpsLimit = 60.0F;

        void Init();
        void Loop();
        void Input();
        void Update();
        void Render();
        void Cleanup();

        [[nodiscard]] auto IsRunning() const -> bool;
    };
} // namespace Mineblocks
