#include "engine.hpp"

#include "engine/test/test_module.hpp"

namespace engine::core {
    Engine::Engine(App* app)
        : m_app(app)
    {
        m_moduleRegistry.registerModule(app);
        m_moduleRegistry.registerModule(new engine::test::TestModule());
    }

    void Engine::run()
    {
        m_running = true;

        m_moduleRegistry.callStage(Stage::init);

        while (m_running) {
            m_moduleRegistry.callStage(Stage::input);
            m_moduleRegistry.callStage(Stage::update);
            m_moduleRegistry.callStage(Stage::render);

            static int i = 0;

            if (i >= 10) {
                requestStop();
            }

            i++;
        }

        m_moduleRegistry.callStage(Stage::cleanup);
    }

    void Engine::requestStop()
    {
        m_running = false;
    }

    App* Engine::getApp() const
    {
        return m_app;
    }

    ModuleRegistry Engine::getModuleRegistry() const
    {
        return m_moduleRegistry;
    }

    bool Engine::isRunning() const
    {
        return m_running;
    }
} // namespace engine::core