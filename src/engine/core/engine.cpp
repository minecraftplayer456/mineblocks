#include "engine.hpp"

#include "engine/devices/glfw.hpp"

namespace engine::core {
    Engine::Engine(App* app)
        : m_app(app)
    {
        addSubmodule<devices::Glfw>();
    }

    void Engine::run()
    {
        m_running = true;

        m_moduleManager.registerModule(m_app);
        m_moduleManager.registerModule(this);

        m_moduleManager.init();

        m_moduleManager.callStage(ModuleLifecycle::Init);

        while (m_running) {
            m_elapsedUpdate.setInterval(maths::Time::seconds(1.0f / m_upsLimit));
            m_elapsedRender.setInterval(maths::Time::seconds(1.0f / m_fpsLimit));

            auto elapsedUpdate = m_elapsedUpdate.getElapsed();
            if (elapsedUpdate != 0) {
                m_ups.update(maths::Time::now());

                m_moduleManager.callStage(ModuleLifecycle::Input);
                m_moduleManager.callStage(ModuleLifecycle::Update);

                m_deltaUpdate.update();
            }

            auto elapsedRender = m_elapsedRender.getElapsed();
            if (elapsedRender != 0) {
                m_fps.update(maths::Time::now());

                m_moduleManager.callStage(ModuleLifecycle::Render);

                m_deltaRender.update();
            }
        }

        m_moduleManager.callStage(ModuleLifecycle::Cleanup);
    }

    void Engine::requestStop()
    {
        m_running = false;
    }

    App* Engine::getApp() const
    {
        return m_app;
    }

    ModuleManager Engine::getModuleManager() const
    {
        return m_moduleManager;
    }

    bool Engine::isRunning() const
    {
        return m_running;
    }

    void Engine::setUpsLimit(float ups)
    {
        m_upsLimit = ups;
    }

    void Engine::setFpsLimit(float fps)
    {
        m_fpsLimit = fps;
    }

    const maths::Time& Engine::getDeltaUpdate() const
    {
        return m_deltaUpdate.change;
    }

    const maths::Time& Engine::getDeltaRender() const
    {
        return m_deltaRender.change;
    }

    uint32_t Engine::getUps() const
    {
        return m_ups.value;
    }

    uint32_t Engine::getFps() const
    {
        return m_fps.value;
    }
} // namespace engine::core