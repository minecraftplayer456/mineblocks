#pragma once

#include <engine/core/module.hpp>

namespace engine::test {
    class TestModule : public core::Module {
      public:
        TestModule();

        void init() override;
    };
} // namespace engine::test