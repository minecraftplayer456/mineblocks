#pragma once

namespace Mineblocks {
    class Application;

    class GameState {
      public:
        GameState(Application* app)
            : application(app)
        {
        }

        virtual void OnPush() = 0;
        virtual void Input() = 0;
        virtual void Update() = 0;
        virtual void Render() = 0;
        virtual void OnPop() = 0;

      protected:
        Application* application;
    };
} // namespace Mineblocks