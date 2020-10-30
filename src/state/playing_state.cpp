#include "playing_state.hpp"

#include "core/application.hpp"

namespace mineblocks {
    PlayingState::PlayingState(Application* app)
        : GameState(app)
    {
    }

    void PlayingState::init()
    {
    }

    void PlayingState::cleanup()
    {
    }

    void PlayingState::input()
    {
        GameState::input();
    }

    void PlayingState::update()
    {
    }

    void PlayingState::render()
    {
        m_app->getMasterRenderer().render(m_app);
    }
} // namespace mineblocks