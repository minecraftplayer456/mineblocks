#pragma once

#include "Mineblocks/Devices/Window.hpp"
#include "Mineblocks/Maths/Time.hpp"
#include "Mineblocks/State/GameState.hpp"

namespace Mineblocks {
    class Application {
      public:
        Application();

        void Run();
        void RequestClose();

        template <typename T, typename... Args>
        void PushState(Args&&... args)
        {
            LOG_DEBUG(Application, "Push new game state");
            states.push_back(std::make_unique<T>(this, std::forward<Args>(args)...));
            auto& s = states.back();
            s->OnPush();
        }

        void PopState();

        void SetUpsLimit(float upsLimit);
        void SetFpsLimit(float fpsLimit);

        [[nodiscard]] auto GetUps() const -> uint32_t;
        [[nodiscard]] auto GetFps() const -> uint32_t;

        [[nodiscard]] auto GetDeltaUpdate() const -> const Time&;
        [[nodiscard]] auto GetDeltaRender() const -> const Time&;

      private:
        bool running = false;
        bool popState = false;

        Delta deltaUpdate, deltaRender;
        ElapsedTime elapsedUpdate, elapsedRender;
        ChangePerSecond ups, fps;
        float upsLimit = 20.0F, fpsLimit = 60.0F;

        std::vector<std::unique_ptr<GameState>> states;

        std::unique_ptr<Window> window;

        void Init();
        void Loop();
        void Input(std::unique_ptr<GameState>& state);
        void Update(std::unique_ptr<GameState>& state);
        void Render(std::unique_ptr<GameState>& state);
        void Cleanup();

        [[nodiscard]] auto IsRunning() const -> bool;
    };
} // namespace Mineblocks
