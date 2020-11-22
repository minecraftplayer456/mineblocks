#include "Engine.hpp"

namespace Engine {
    Engine::Engine(std::unique_ptr<Application> app)
        : app(std::move(app))
    {
    }

    auto Engine::Run() -> int
    {
        try {
            Init();
            Loop();
            Cleanup();
            return 0;
        }
        catch (const std::exception& e) {
            ENGINE_CORE_CRITICAL(e.what());
            return 1;
        }
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
            elapsedUpdate.SetInterval(Time::Seconds(1.0F / upsLimit));
            elapsedRender.SetInterval(Time::Seconds(1.0F / fpsLimit));

            uint32_t updateTime = elapsedUpdate.GetElapsed();
            // ENGINE_CORE_DEBUG("Update time: {}", updateTime);
            if (updateTime != 0) {
                static int updates = 0;

                upsCounter.Update(Time::Now());

                moduleManager.CallStage(Module::Stage::Input);
                eventBus.NotifyStage(Event::Stage::Input);

                moduleManager.CallStage(Module::Stage::Update);
                eventBus.NotifyStage(Event::Stage::Update);

                deltaUpdate.Update();

                if (updates >= 16) {
                    ENGINE_CORE_DEBUG(
                        "Ups delta: {}; Ups: {}; Fps Delta: {}; Fps: {}",
                        deltaUpdate.Change.AsMilliSeconds(), upsCounter.Value,
                        deltaRender.Change.AsMilliSeconds(), fpsCounter.Value);
                    updates = 0;
                }

                updates++;
            }

            uint32_t renderTime = elapsedRender.GetElapsed();
            if (renderTime != 0) {
                fpsCounter.Update(Time::Now());

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

    auto Engine::GetApplication() -> std::unique_ptr<Application>&
    {
        return app;
    }

    auto Engine::GetModuleManager() -> ModuleManager&
    {
        return moduleManager;
    }

    auto Engine::GetEventBus() -> EventBus&
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

    auto Engine::GetDeltaUpdate() const -> const Time&
    {
        return deltaUpdate.Change;
    }

    auto Engine::GetDeltaRender() const -> const Time&
    {
        return deltaRender.Change;
    }

    auto Engine::GetUps() const -> uint32_t
    {
        return upsCounter.Value;
    }

    auto Engine::GetFps() const -> uint32_t
    {
        return fpsCounter.Value;
    }
} // namespace Engine