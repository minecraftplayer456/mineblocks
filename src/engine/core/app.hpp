#pragma once

#include <string>

#include "engine/utils/version.hpp"
#include "module.hpp"

namespace engine::core {
    class App : public Module {
      public:
        explicit App(std::string name = {}, const utils::Version& version = {1, 0, 0});

        [[nodiscard]] std::string getName() const;
        [[nodiscard]] utils::Version getVersion() const;

      private:
        std::string m_name;
        utils::Version m_version;
    };
} // namespace engine::core