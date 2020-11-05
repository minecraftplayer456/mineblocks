#pragma once

#include "Engine/Core/Application.hpp"
#include "Engine/Core/Event.hpp"

namespace Engine {
    class Engine {
      public:
        explicit Engine(Application* p_app);

        void Run();

        [[nodiscard]] const ModuleManager& GetModuleManager() const;

        [[nodiscard]] Application* GetApplication() const;

      private:
        void init();
        void loop();
        void cleanup();

        bool m_Running = false;

        ModuleManager m_ModuleManager;
        Application* m_App = nullptr;
    };
} // namespace Engine