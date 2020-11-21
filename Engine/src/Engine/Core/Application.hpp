#pragma once

#include "Engine/Core/Module.hpp"
#include "Engine/Util/Version.hpp"

namespace Engine {
    class Engine;

    class Application {
      public:
        Application(const char* name, const Version& version);

        [[nodiscard]] const char* GetName() const;
        [[nodiscard]] const Version& GetVersion() const;

        virtual void Init(Engine* engine) = 0;
        virtual void Cleanup(Engine* engine) = 0;

      private:
        const char* Name;
        Version Version;
    };

    Application* CreateApplication();
} // namespace Engine
