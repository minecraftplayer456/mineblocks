#pragma once

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Mineblocks {
    class Application;

    class Window {
      public:
        Window(Application* app);
        ~Window();

        void Input();

        void Render();

        [[nodiscard]] auto GetWidth() const -> uint32_t;
        [[nodiscard]] auto GetHeight() const -> uint32_t;
        [[nodiscard]] auto GetTitle() const -> const char*;

        [[nodiscard]] auto GetWindow() -> GLFWwindow*;

      private:
        Application* app;

        uint32_t width;
        uint32_t height;
        const char* title;

        GLFWwindow* window;
    };
} // namespace Mineblocks