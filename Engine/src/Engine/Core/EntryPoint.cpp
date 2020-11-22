#include "EntryPoint.hpp"

auto main([[maybe_unused]] int argc, [[maybe_unused]] char** argv) -> int
{
    auto engine = Engine::Engine(Engine::CreateApplication());

    return engine.Run();
}