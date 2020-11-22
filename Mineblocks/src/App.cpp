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

    void App::Cleanup([[maybe_unused]] Engine::Engine* engine)
    {
    }

    void AppModule::Init()
    {
    }

    void AppModule::Cleanup()
    {
    }
} // namespace Mineblocks

auto Engine::CreateApplication() -> std::unique_ptr<Application>
{
    return std::make_unique<Mineblocks::App>();
}