#pragma once

#include "Engine/Util/Version.hpp"

namespace Engine {
    class Engine;

    class Application : public NonCopyMovable {
      public:
        Application(const char* name, const Version& version);

        [[nodiscard]] auto GetName() const -> const char*;
        [[nodiscard]] auto GetVersion() const -> const Version&;

        virtual void Init() = 0;
        virtual void Cleanup() = 0;

      private:
        const char* name;
        Version version;
    };

    auto CreateApplication() -> Application*;
} // namespace Engine
