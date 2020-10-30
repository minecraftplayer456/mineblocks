#pragma once

namespace mineblocks{
    class Application;

    class GameState{
      public:
        explicit GameState(Application* app);

        virtual void init() = 0;
        virtual void cleanup() = 0;

        virtual void input() = 0;
        virtual void update() = 0;
        virtual void render() = 0;

      protected:
        Application* m_app;

    };
}