#pragma once

#include "state/game_state.hpp"

namespace mineblocks {
    class PlayingState : public GameState {
      public:
        explicit PlayingState(Application* app);

        void init() override;
        void cleanup() override;

        void input() override;
        void update() override;
        void render() override;
    };
} // namespace mineblocks