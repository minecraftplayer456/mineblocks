#include "App.hpp"

namespace Mineblocks {
    App::App()
        : Engine::Application("Mineblocks", Engine::Version(0, 1, 0))
    {
    }

    void App::Init(Engine::Engine* engine)
    {
        engine->GetModuleManager().PushModule<AppModule>();
    }

    void App::Cleanup(Engine::Engine* engine)
    {
    }

    void AppModule::Init()
    {
    }

    void AppModule::Cleanup()
    {
    }
} // namespace Mineblocks

Engine::Application* Engine::CreateApplication()
{
    return new Mineblocks::App();
}