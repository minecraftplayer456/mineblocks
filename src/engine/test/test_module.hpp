#pragma once

#include <engine/core/module.hpp>

namespace engine::test {
    class TestModule : public core::Module {
      public:
        TestModule();

        void init();
        void input();
        void update();
        void render();
        void cleanup();
    };

    class TestModule2 : public core::Module {
      public:
        TestModule2();

        void init();
        void input();
        void update();
        void render();
        void cleanup();
    };

    class TestModule3 : public core::Module {
      public:
        TestModule3();

        void init();
        void input();
        void update();
        void render();
        void cleanup();
    };

    class TestModule4 : public core::Module {
      public:
        TestModule4();

        void init();
        void input();
        void update();
        void render();
        void cleanup();
    };
} // namespace engine::test