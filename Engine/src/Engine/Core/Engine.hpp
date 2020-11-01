#pragma once

#include "Engine/Core/Application.hpp"

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

        Application* m_app = nullptr;

        bool m_running = false;
    };
} // namespace Engine