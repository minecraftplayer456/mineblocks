#pragma once

namespace Mineblocks {
    class RenderMaster;
    class Application;

    class GameState {
      public:
        GameState(Application* app)
            : application(app)
        {
        }
        virtual ~GameState() = default;

        virtual void OnPush() = 0;
        virtual void Input() = 0;
        virtual void Update() = 0;
        virtual void Render(const std::unique_ptr<RenderMaster>& renderMaster) = 0;
        virtual void OnPop() = 0;

      protected:
        Application* application;
    };
} // namespace Mineblocks