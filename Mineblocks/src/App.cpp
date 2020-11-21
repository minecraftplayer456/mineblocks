#include "App.hpp"

namespace Mineblocks {
    App::App()
        : Engine::Application("Mineblocks", Engine::Version(0, 1, 0))
    {
    }

    void App::Init(Engine::Engine* engine)
    {
        ENGINE_DEBUG("Init mineblocks");

        engine->GetModuleManager().PushModule<AppModule>();
    }

    void App::Cleanup(Engine::Engine* engine)
    {
        ENGINE_DEBUG("Cleanup mineblocks");
    }

    void AppModule::Init()
    {
        ENGINE_DEBUG("Init mineblocks module");
    }

    void AppModule::Cleanup()
    {
        ENGINE_DEBUG("Cleanup mineblocks module");
    }
} // namespace Mineblocks

Engine::Application* Engine::CreateApplication()
{
    return new Mineblocks::App();
}