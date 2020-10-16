#pragma once

#include <string>

#include <GLFW/glfw3.h>

namespace engine::devices::window {
    class Window {
      public:
        Window(int id, int width, int height, std::string title);

        void show();

        void hide();

        void destroy();

        void setSize(int width, int height);

        void setTitle(std::string title);

        int getId() const;

        bool isVisible() const;

        int getWidth() const;

        int getHeight() const;

        std::string getTitle() const;

        GLFWwindow* getWindow() const;

      private:
        int m_id;

        bool m_visible = false;

        int m_width;
        int m_height;

        std::string m_title;

        GLFWwindow* m_window = nullptr;
    };
} // namespace engine::devices::window