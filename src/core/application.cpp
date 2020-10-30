#include "application.hpp"

#include <stdexcept>
#include <iostream>

namespace mineblocks{
    void Application::run()
    {
        try {
            init();
            loop();
            cleanup();
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }

    void Application::init()
    {

    }

    void Application::loop()
    {
        m_running = true;

        while (m_running){
            auto elapsedUpdate = m_elapsedUpdate.getElapsed();
            if(elapsedUpdate != 0){
                m_ups.update(Time::now());

                m_currentState->input();
                m_currentState->update();

                m_deltaUpdate.update();
            }

            auto elapsedRender = m_elapsedRender.getElapsed();
            if(elapsedRender != 0){
                m_fps.update(Time::now());

                render();

                m_deltaRender.update();
            }
        }
    }

    void Application::cleanup()
    {

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

    template <typename T, typename>
    void Application::setGameState()
    {
        m_currentState->cleanup();
        m_currentState = std::make_shared<T>(this);
        m_currentState->init();
    }

    std::shared_ptr<GameState> Application::getGameState()
    {
        return m_currentState;
    }

    bool Application::isRunning() const
    {
        return m_running;
    }

    void Application::requestStop()
    {
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
}