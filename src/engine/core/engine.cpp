#include "engine.hpp"

#include <utility>

#include "engine/test/test_module.hpp"

namespace engine::core {
    Engine::Engine(App* app)
        : m_app(std::shared_ptr<App>(app))
    {
        m_moduleRegistry.registerModule(m_app);

        m_moduleRegistry.registerModule(new engine::test::TestModule);
    }

    void Engine::run()
    {
        m_running = true;

        m_moduleRegistry.sortRequirements();

        m_moduleRegistry.callStage(Stage::Init);

        while (m_running) {
            m_moduleRegistry.callStage(Stage::Input);
            m_moduleRegistry.callStage(Stage::Update);
            m_moduleRegistry.callStage(Stage::Render);

            static int i = 0;

            if (i >= 1000) {
                requestStop();
            }

            i++;
        }

        m_moduleRegistry.callStage(Stage::Cleanup);
    }

    void Engine::requestStop()
    {
        m_running = false;
    }

    std::shared_ptr<App> Engine::getApp() const
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