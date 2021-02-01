#include "PlayingState.hpp"

#include "Mineblocks/Render/RenderMaster.hpp"

namespace Mineblocks {
    PlayingState::PlayingState(Application* app)
        : GameState(app)
    {
    }

    void PlayingState::OnPush()
    {
    }

    void PlayingState::Input()
    {
    }

    void PlayingState::Update()
    {
    }

    void PlayingState::Render(const std::unique_ptr<RenderMaster>& renderMaster)
    {
        renderMaster->Render();
    }

    void PlayingState::OnPop()
    {
    }
} // namespace Mineblocks