#pragma once

#include <memory>

#include <spdlog/spdlog.h>

#include "devices/window.hpp"
#include "maths/time.hpp"
#include "state/game_state.hpp"

namespace mineblocks {
    class Application {
      public:
        Application();

        void run();

        template <typename T,
                  typename = std::enable_if<std::is_convertible<T, GameState>::value>>
        void updateGameState();

        std::shared_ptr<GameState> getGameState();

        [[nodiscard]] Window getWindow() const;

        [[nodiscard]] bool isRunning() const;
        void requestStop();

        void setUpsLimit(float ups);
        void setFpsLimit(float fps);

        [[nodiscard]] const Time& getDeltaUpdate() const;
        [[nodiscard]] const Time& getRenderUpdate() const;
        [[nodiscard]] uint32_t getUps() const;
        [[nodiscard]] uint32_t getFps() const;

      private:
        bool m_running = false;

        Window m_window;

        std::shared_ptr<GameState> m_currentState;

        DeltaTime m_deltaUpdate, m_deltaRender;
        ElapsedTime m_elapsedUpdate, m_elapsedRender;
        ChangePerSecond m_ups, m_fps;

        void init();
        void loop();
        void cleanup();

        void input();
        void update();
        void render();
    };

    template <typename T, typename>
    void Application::updateGameState()
    {
        spdlog::debug("Update game state");
        m_currentState->cleanup();
        m_currentState = std::make_shared<T>(this);
        m_currentState->init();
    }
} // namespace mineblocks
