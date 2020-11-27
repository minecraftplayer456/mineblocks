#pragma once

#include <Engine/Core/EntryPoint.hpp>

namespace Mineblocks {
    class App : public Engine::Application {
      public:
        App();

        void Init() override;
        void Cleanup() override;
    };

    class AppModule : public Engine::Module::Registrar<AppModule> {
      public:
        inline static const bool Registered = Register();

        [[nodiscard]] auto GetName() const -> const char* override
        {
            return "mineblocks module";
        }

        void Init() override;
        void Cleanup() override;
    };
} // namespace Mineblocks