#include "App.hpp"

namespace Mineblocks {
    App::App()
        : Engine::Application("Mineblocks", Engine::Version(0, 1, 0))
    {
    }

    void App::Init()
    {
        Engine::ModuleManager::Get()->PushModule<AppModule>();
    }

    void App::Cleanup()
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