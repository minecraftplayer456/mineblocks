#include "MineblocksApp.hpp"

namespace Mineblocks {
    MineblocksApp::MineblocksApp()
        : Engine::Application("Mineblocks", Engine::Version(0, 1, 0))
    {
    }
} // namespace Mineblocks

Engine::Application* Engine::CreateApplication()
{
    return new Mineblocks::MineblocksApp();
}