#pragma once

#include "Engine/Core/Module.hpp"
#include "Engine/Util/Version.hpp"

namespace Engine {
    class Application : public Module {
      public:
        Application(const char* p_name, const Version& p_version);

        [[nodiscard]] const char* GetName() const override;
        [[nodiscard]] const Version& GetVersion() const;

      private:
        const char* m_name;
        Version m_version;
    };

    Application* CreateApplication();
} // namespace Engine
