#pragma once

#include <engine/core/module.hpp>

namespace engine::test {
    class TestModule : public core::Module {
      public:
        void init() override;
        void input() override;
        void update() override;
        void render() override;
        void cleanup() override;

      private:
        std::vector<core::Stage> setupStages() override;
    };
} // namespace engine::test