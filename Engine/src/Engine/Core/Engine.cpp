#include "Engine.hpp"

namespace Engine {
    Engine::Engine(Application* app)
        : App(app)
    {
    }

    void Engine::Run()
    {
        init();
        loop();
        cleanup();
    }

    void Engine::init()
    {
        ENGINE_CORE_INFO("Running {} v{}", App->GetName(), App->GetVersion().ToString());

        App->Init(this);

        ModuleManager.CallStage(Module::Stage::Init);
        EventBus.NotifyStage(Event::Stage::Init);
    }

    void Engine::RequestClose()
    {
        ENGINE_CORE_DEBUG("Request close");
        Running = false;
    }

    void Engine::loop()
    {
        ENGINE_CORE_DEBUG("Run gameloop");

        Running = true;

        while (Running) {
            ModuleManager.CallStage(Module::Stage::Input);
            EventBus.NotifyStage(Event::Stage::Input);
            ModuleManager.CallStage(Module::Stage::Update);
            EventBus.NotifyStage(Event::Stage::Update);
            ModuleManager.CallStage(Module::Stage::Render);
            EventBus.NotifyStage(Event::Stage::Render);

            RequestClose();
        }
    }

    void Engine::cleanup()
    {
        ENGINE_CORE_INFO("Closing");

        ModuleManager.CallStage(Module::Stage::Cleanup);
        EventBus.NotifyStage(Event::Stage::Cleanup);

        App->Cleanup(this);
    }

    Application* Engine::GetApplication() const
    {
        return App;
    }

    ModuleManager& Engine::GetModuleManager()
    {
        return ModuleManager;
    }

    EventBus& Engine::GetEventBus()
    {
        return EventBus;
    }
} // namespace Engine