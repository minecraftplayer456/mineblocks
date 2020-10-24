#include "engine.hpp"

#include <spdlog/spdlog.h>

namespace engine::core {
    Engine::Engine(App* app)
        : m_app(app) {}

    void Engine::run()
    {
        try {
            runLoop();
        }
        catch (const std::exception& e) {
            spdlog::critical("Fatal exception: " + std::string(e.what()));
        }
    }

    void Engine::runLoop()
    {
        m_running = true;

        spdlog::set_level(spdlog::level::trace);

        spdlog::info("Starting " + m_app->getName() + " " +
                     m_app->getVersion().toString());

        m_moduleManager.registerModule(m_app);

        spdlog::debug("Initializing modules");

        m_moduleManager.init();
        m_moduleManager.callStage(ModuleLifecycle::Init);

        spdlog::debug("Initialized modules");

        while (m_running) {
            m_elapsedUpdate.setInterval(maths::Time::seconds(1.0f / m_upsLimit));
            m_elapsedRender.setInterval(maths::Time::seconds(1.0f / m_fpsLimit));

            auto elapsedUpdate = m_elapsedUpdate.getElapsed();
            if (elapsedUpdate != 0) {
                static int updates = 0;

                m_ups.update(maths::Time::now());

                m_moduleManager.callStage(ModuleLifecycle::Input);
                m_moduleManager.callStage(ModuleLifecycle::Update);

                m_deltaUpdate.update();

                if (updates >= 128) {
                    spdlog::trace("Ups Delta: " + std::to_string(m_deltaUpdate.change.asMilliSeconds()));
                    spdlog::trace("Ups: " + std::to_string(m_ups.value));
                    spdlog::trace("Fps Delta: " + std::to_string(m_deltaRender.change.asMilliSeconds()));
                    spdlog::trace("Fps: " + std::to_string(m_fps.value));
                    updates = 0;
                    requestStop();
                }

                updates++;
            }

            auto elapsedRender = m_elapsedRender.getElapsed();
            if (elapsedRender != 0) {
                m_fps.update(maths::Time::now());

                m_moduleManager.callStage(ModuleLifecycle::Render);

                m_deltaRender.update();
            }
        }

        spdlog::info("Stopping");
        spdlog::debug("Cleaning up");

        m_moduleManager.callStage(ModuleLifecycle::Cleanup);

        spdlog::debug("Cleaned up");
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