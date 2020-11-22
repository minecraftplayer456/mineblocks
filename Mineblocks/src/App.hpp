#pragma once

#include <Engine/Core/EntryPoint.hpp>

namespace Mineblocks {
    class App : public Engine::Application {
      public:
        App();

        void Init(Engine::Engine* engine) override;
        void Cleanup(Engine::Engine* engine) override;
    };

    class AppModule : public Engine::Module::Registrar<AppModule> {
      public:
        inline static const bool Registered = Register();

        const char* GetName() const override
        {
            return "mineblocks module";
        }

        void Init() override;
        void Cleanup() override;
    };
} // namespace Mineblocks