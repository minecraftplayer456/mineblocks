#pragma once

#include "GameState.hpp"

namespace Mineblocks {
    class PlayingState : public GameState {
      public:
        PlayingState(Application* app);

        void OnPush() override;
        void Input() override;
        void Update() override;
        void Render() override;
        void OnPop() override;
    };
} // namespace Mineblocks