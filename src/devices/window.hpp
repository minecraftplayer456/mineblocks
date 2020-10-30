#pragma once

#include <string>

#include <GLFW/glfw3.h>

namespace mineblocks {
    class Application;

    const unsigned int WINDOW_WIDTH = 900;
    const unsigned int WINDOW_HEIGHT = 700;
    const std::string WINDOW_TITLE = "Mineblocks";

    class Window {
      public:
        void init();
        void input(Application* app);
        void cleanup();

        GLFWwindow* getWindow();

      private:
        GLFWwindow* m_window = nullptr;
    };
} // namespace mineblocks