#pragma once

#include "GameState.hpp"

namespace Mineblocks {
    class PlayingState : public GameState {
      public:
        PlayingState(Application* app);
        ~PlayingState() override = default;

        void OnPush() override;
        void Input() override;
        void Update() override;
        void Render(const std::unique_ptr<RenderMaster>& renderMaster) override;
        void OnPop() override;
    };
} // namespace Mineblocks