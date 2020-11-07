#pragma once

#include "Engine/Core/Application.hpp"
#include "Engine/Core/Event.hpp"

namespace Engine {
    class Engine {
      public:
        explicit Engine(Application* p_app);

        void Run();

        [[nodiscard]] Application* GetApplication() const;

      private:
        void init();
        void loop();
        void cleanup();

        bool m_Running = false;

        LifecycleManager m_LifecycleManager;

        Application* m_App = nullptr;
    };
} // namespace Engine