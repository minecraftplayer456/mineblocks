#pragma once

#include <string>

#include "utils/version.hpp"

namespace engine {
    class App {
      public:
        App(std::string name, const utils::Version& version);

        [[nodiscard]] std::string getName() const;

        [[nodiscard]] utils::Version getVersion() const;

      private:
        std::string m_name;
        utils::Version m_version;
    };
} // namespace engine