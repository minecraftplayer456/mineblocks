#include "App.hpp"

namespace Mineblocks {
    App::App()
        : Engine::Application("Mineblocks", Engine::Version(0, 1, 0))
    {
        m_InitFunction = [this]() { Init(); };
    }

    void App::Init()
    {
        ENGINE_INFO("Init");
    }
} // namespace Mineblocks

Engine::Application* Engine::CreateApplication()
{
    return new Mineblocks::App();
}