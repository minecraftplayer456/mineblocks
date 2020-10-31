#include "application.hpp"

#include <stdexcept>

#include "state/playing_state.hpp"

namespace mineblocks {
    Application::Application()
    {
        m_currentState = std::make_shared<PlayingState>(this);
    }

    void Application::run()
    {
        try {
            init();
            loop();
            cleanup();
        }
        catch (const std::exception& e) {
            spdlog::critical("Exception: {}", std::string(e.what()));
        }
    }

    void Application::init()
    {
        spdlog::set_level(spdlog::level::trace);

        spdlog::info("Initialize mineblocks");

        m_window.init();

        m_masterRenderer = std::make_shared<MasterRenderer>(&m_window);
        m_masterRenderer->init();

        m_currentState->init();
    }

    void Application::loop()
    {
        m_running = true;

        spdlog::info("Running mineblocks");

        while (m_running) {
            auto elapsedUpdate = m_elapsedUpdate.getElapsed();
            if (elapsedUpdate != 0) {
                m_ups.update(Time::now());

                m_currentState->input();
                m_currentState->update();

                m_deltaUpdate.update();
            }

            auto elapsedRender = m_elapsedRender.getElapsed();
            if (elapsedRender != 0) {
                m_fps.update(Time::now());

                render();

                m_deltaRender.update();
            }
        }
    }

    void Application::cleanup()
    {
        spdlog::info("Cleanup mineblocks");

        m_currentState->cleanup();
        m_masterRenderer->cleanup();
        m_window.cleanup();
    }

    void Application::input()
    {
    }

    void Application::update()
    {
    }

    void Application::render()
    {
    }

    std::shared_ptr<GameState> Application::getGameState()
    {
        return m_currentState;
    }

    Window Application::getWindow() const
    {
        return m_window;
    }

    std::shared_ptr<MasterRenderer> Application::getMasterRenderer() const
    {
        return m_masterRenderer;
    }

    bool Application::isRunning() const
    {
        return m_running;
    }

    void Application::requestStop()
    {
        spdlog::info("Request stop");
        m_running = false;
    }

    void Application::setUpsLimit(float ups)
    {
        m_elapsedUpdate.setInterval(Time::seconds(1.0f / ups));
    }

    void Application::setFpsLimit(float fps)
    {
        m_elapsedRender.setInterval(Time::seconds(1.0f / fps));
    }

    const Time& Application::getDeltaUpdate() const
    {
        return m_deltaUpdate.change;
    }

    const Time& Application::getRenderUpdate() const
    {
        return m_deltaRender.change;
    }

    uint32_t Application::getUps() const
    {
        return m_ups.value;
    }

    uint32_t Application::getFps() const
    {
        return m_fps.value;
    }
} // namespace mineblocks