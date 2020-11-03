#pragma once

#include "Engine/Core/Engine.hpp"

extern Engine::Application* Engine::CreateApplication();

int main(int argc, char** argv)
{
    auto* app = Engine::CreateApplication();
    auto engine = Engine::Engine(app);

    engine.Run();

    delete app;
}