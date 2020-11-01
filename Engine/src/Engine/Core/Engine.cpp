#include "Engine.hpp"

namespace Engine {
    Engine::Engine(Application* p_app)
    {
        m_app = p_app;
    }

    void Engine::Run()
    {
        init();
        loop();
        cleanup();
    }

    void Engine::init()
    {
    }

    void Engine::loop()
    {
        m_running = true;

        while (m_running) {
        }
    }

    void Engine::cleanup()
    {
    }

    Application* Engine::GetApplication() const
    {
        return m_app;
    }
} // namespace Engine