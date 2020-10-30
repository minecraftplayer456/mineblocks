#pragma once

namespace mineblocks {
    class Application;

    class MasterRenderer {
      public:
        void init();
        void render(Application* app);
        void cleanup();
    };
} // namespace mineblocks