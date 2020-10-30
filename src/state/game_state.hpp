#pragma once

namespace mineblocks {
    class Application;

    class GameState {
      public:
        explicit GameState(Application* app);

        virtual void init();
        virtual void cleanup();

        virtual void input();
        virtual void update();
        virtual void render();

      protected:
        Application* m_app;
    };
} // namespace mineblocks