#pragma once

#include <engine/core/app.hpp>

namespace mineblocks::core {
    class Mineblocks : public engine::core::App {
      public:
        Mineblocks();

      private:
        std::vector<engine::core::Stage> setupStages() override;

        void init() override;
    };
} // namespace mineblocks::core