#pragma once

#include "Engine/Util/Version.hpp"

namespace Engine {
    class Application {
      public:
        Application(std::string p_name, const Version& p_version);

        [[nodiscard]] const std::string& GetName() const;
        [[nodiscard]] const Version& GetVersion() const;

      private:
        std::string m_name;
        Version m_version;
    };

    Application* CreateApplication();
} // namespace Engine
