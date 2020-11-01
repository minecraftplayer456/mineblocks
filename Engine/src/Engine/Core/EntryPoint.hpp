#pragma once

#include "Engine/Core/Engine.hpp"

extern Engine::Application* Engine::CreateApplication();

int main(int argc, char** argv)
{
    auto* app = Engine::CreateApplication();
    auto* engine = new Engine::Engine(app);

    engine->Run();

    delete engine;
    delete app;
}