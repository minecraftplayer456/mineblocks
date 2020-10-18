#pragma once

#include <engine/core/module.hpp>

namespace engine::test {
    class TestModule : public core::Module {
      public:
        TestModule();

        void init() override;
        void input() override;
        void update() override;
        void render() override;
        void cleanup() override;
    };
} // namespace engine::test