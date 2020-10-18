#include "engine.hpp"

#include "engine/test/test_module.hpp"

namespace engine::core {
    Engine::Engine(App app)
        : m_app(std::move(app))
    {
        m_moduleRegistry.registerModule(new engine::test::TestModule());
    }

    void Engine::run()
    {
        m_moduleRegistry.callStage(Stage::init);
    }
} // namespace engine::core