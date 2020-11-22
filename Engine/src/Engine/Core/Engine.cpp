#include "Engine.hpp"

namespace Engine {
    Engine::Engine(Application* app)
        : app(app)
    {
    }

    void Engine::Run()
    {
        Init();
        Loop();
        Cleanup();
    }

    void Engine::Init()
    {
        ENGINE_CORE_INFO("Running {} v{}", app->GetName(), app->GetVersion().ToString());

        app->Init(this);

        moduleManager.CallStage(Module::Stage::Init);
        eventBus.NotifyStage(Event::Stage::Init);
    }

    void Engine::RequestClose()
    {
        ENGINE_CORE_DEBUG("Request close");
        running = false;
    }

    void Engine::Loop()
    {
        ENGINE_CORE_DEBUG("Run gameloop");

        running = true;

        while (running) {
            elapsedUpdate.SetInterval(Time::Seconds(1.0f / upsLimit));
            elapsedRender.SetInterval(Time::Seconds(1.0f / fpsLimit));

            uint32_t updateTime = elapsedUpdate.GetElapsed();
            if (updateTime != 0) {
                static int updates = 0;

                ups.Update(Time::Now());

                moduleManager.CallStage(Module::Stage::Input);
                eventBus.NotifyStage(Event::Stage::Input);

                moduleManager.CallStage(Module::Stage::Update);
                eventBus.NotifyStage(Event::Stage::Update);

                deltaUpdate.Update();

                if (updates >= 128) {
                    ENGINE_CORE_DEV_DEBUG(
                        "Ups delta: {}; Ups: {}; Fps Delta: {}; Fps: {}",
                        deltaUpdate.change.AsMilliSeconds(), ups.value,
                        deltaRender.change.AsMilliSeconds(), fps.value);
                    updates = 0;
                }

                updates++;
            }

            uint32_t renderTime = elapsedRender.GetElapsed();
            if (renderTime != 0) {
                fps.Update(Time::Now());

                moduleManager.CallStage(Module::Stage::Render);
                eventBus.NotifyStage(Event::Stage::Render);

                deltaRender.Update();
            }
        }
    }

    void Engine::Cleanup()
    {
        ENGINE_CORE_INFO("Closing");

        moduleManager.CallStage(Module::Stage::Cleanup);
        eventBus.NotifyStage(Event::Stage::Cleanup);

        app->Cleanup(this);
    }

    Application* Engine::GetApplication() const
    {
        return app;
    }

    ModuleManager& Engine::GetModuleManager()
    {
        return moduleManager;
    }

    EventBus& Engine::GetEventBus()
    {
        return eventBus;
    }

    void Engine::SetUpsLimit(float ups)
    {
        upsLimit = ups;
    }

    void Engine::SetFpsLimit(float fps)
    {
        fpsLimit = fps;
    }

    const Time& Engine::GetDeltaUpdate() const
    {
        return deltaUpdate.change;
    }

    const Time& Engine::GetDeltaRender() const
    {
        return deltaRender.change;
    }

    uint32_t Engine::GetUps() const
    {
        return ups.value;
    }

    uint32_t Engine::GetFps() const
    {
        return fps.value;
    }
} // namespace Engine