#include "EntryPoint.hpp"

int main(int argc, char** argv)
{
    auto* app = Engine::CreateApplication();
    auto engine = Engine::Engine(app);

    engine.Run();

    delete app;
}