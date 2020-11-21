#pragma once

#include "Engine/Core/Application.hpp"
#include "Engine/Core/Event.hpp"

namespace Engine {
    class Engine {
      public:
        explicit Engine(Application* p_app);

        void Run();
        void RequestClose();

        [[nodiscard]] Application* GetApplication() const;

        [[nodiscard]] ModuleManager& GetModuleManager();

      private:
        void init();
        void loop();
        void cleanup();

        bool Running = false;

        ModuleManager ModuleManager;

        Application* App = nullptr;
    };
} // namespace Engine