#include "Application.hpp"

#include "Mineblocks/State/PlayingState.hpp"

namespace Mineblocks {
    Application::Application()
    {
        PushState<PlayingState>();
    }

    void Application::Run()
    {
        try {
            Init();
            Loop();
            Cleanup();
        }
        catch (const std::exception& e) {
            LOG_CRITICAL(Application, "Shutting down. Unhandled exception occurred: {}",
                         e.what());
        }
    }

    void Application::RequestClose()
    {
        LOG_INFO(Application, "Requested closing");

        running = false;
    }

    void Application::Init()
    {
        LOG_INFO(Application, "Initializing mineblocks");

        LOG_INFO(Application, "Initialized mineblocks");
    }

    void Application::Loop()
    {
        running = true;
        while (running) {
            elapsedUpdate.SetInterval(Time::Seconds(1.0F / upsLimit));
            elapsedRender.SetInterval(Time::Seconds(1.0F / fpsLimit));

            if (popState) {
                auto& oldState = states.front();
                states.pop_back();
                oldState->OnPop();
            }

            auto& state = states.front();

            if (elapsedUpdate.GetElapsed() != 0) {
                ups.Update(Time::Now());

                Input(state);
                Update(state);

                deltaUpdate.Update();
            }

            if (elapsedRender.GetElapsed() != 0) {
                fps.Update(Time::Now());

                Render(state);

                deltaRender.Update();
            }
        }
    }

    void Application::Input(std::unique_ptr<GameState>& state)
    {
        state->Input();
    }

    void Application::Update(std::unique_ptr<GameState>& state)
    {
        static int updates = 0;

        state->Update();

        if (updates >= 64) {
            LOG_DEBUG(Application,
                      "Fps: {}; Ups: {}; Render Delta: {}ms; Update Delta {}ms",
                      fps.value, ups.value, deltaRender.change.AsMilliseconds(),
                      deltaUpdate.change.AsMilliseconds());
            updates = 0;
        }
        updates++;
    }

    void Application::Render(std::unique_ptr<GameState>& state)
    {
        state->Render();
    }

    void Application::Cleanup()
    {
        LOG_INFO(Application, "Cleaning up mineblocks");

        LOG_INFO(Application, "Cleaned up mineblocks");
    }

    auto Application::IsRunning() const -> bool
    {
        return running;
    }

    void Application::PopState()
    {
        LOG_DEBUG(Application, "Pop current game state");
        popState = true;
    }

    void Application::SetUpsLimit(float upsLimit)
    {
        this->upsLimit = upsLimit;
    }

    void Application::SetFpsLimit(float fpsLimit)
    {
        this->fpsLimit = fpsLimit;
    }

    auto Application::GetUps() const -> uint32_t
    {
        return ups.value;
    }

    auto Application::GetFps() const -> uint32_t
    {
        return fps.value;
    }

    auto Application::GetDeltaUpdate() const -> const Time&
    {
        return deltaUpdate.change;
    }

    auto Application::GetDeltaRender() const -> const Time&
    {
        return deltaRender.change;
    }
} // namespace Mineblocks