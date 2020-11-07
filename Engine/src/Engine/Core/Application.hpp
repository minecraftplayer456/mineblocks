#pragma once

#include "Engine/Core/Lifecycle.hpp"
#include "Engine/Util/Version.hpp"

namespace Engine {
    class Application {
      public:
        Application(const char* p_name, const Version& p_version);

        [[nodiscard]] const char* GetName() const;
        [[nodiscard]] const Version& GetVersion() const;

      private:
        const char* m_name;
        Version m_version;
    };

    Application* CreateApplication();
} // namespace Engine
