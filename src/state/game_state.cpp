#include "game_state.hpp"

#include "core/application.hpp"

namespace mineblocks {
    GameState::GameState(Application* app)
        : m_app(app)
    {
    }

    void GameState::init()
    {
    }

    void GameState::input()
    {
        m_app->getWindow().input(m_app);
    }

    void GameState::update()
    {
    }

    void GameState::render()
    {
    }

    void GameState::cleanup()
    {
    }
} // namespace mineblocks