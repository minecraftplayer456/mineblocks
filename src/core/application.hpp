#pragma once

#include <memory>

#include "maths/time.hpp"
#include "state/game_state.hpp"

namespace mineblocks {
    class Application {
      public:
        void run();

        template <typename T, typename = std::enable_if<std::is_convertible<T, GameState>::value>>
        void setGameState();

        std::shared_ptr<GameState> getGameState();

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
} // namespace mineblocks
