#pragma once

#include <engine/core/module.hpp>

namespace engine::test {
    class TestModule : public core::Module {
      public:
        TestModule();

        void init();
    };

    class TestModule2 : public core::Module {
      public:
        TestModule2();

        void init();
    };

    class TestModule3 : public core::Module {
      public:
        TestModule3();

        void init();
    };

    class TestModule4 : public core::Module {
      public:
        TestModule4();

        void init();
    };
} // namespace engine::test