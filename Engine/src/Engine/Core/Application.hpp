#pragma once

#include "Engine/Core/Module.hpp"
#include "Engine/Util/Version.hpp"

namespace Engine {
    class Engine;

    class Application {
      public:
        Application(const char* name, const Version& version);

        [[nodiscard]] auto GetName() const -> const char*;
        [[nodiscard]] auto GetVersion() const -> const Version&;

        virtual void Init(Engine* engine) = 0;
        virtual void Cleanup(Engine* engine) = 0;

      private:
        const char* name;
        Version version;
    };

    auto CreateApplication() -> std::unique_ptr<Application>;
} // namespace Engine
