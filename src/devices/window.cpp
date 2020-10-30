#include "window.hpp"

#include <stdexcept>

#include <spdlog/spdlog.h>

#include "core/application.hpp"

namespace mineblocks {
    void Window::init()
    {
        spdlog::debug("Create window}");

        if (!glfwInit()) {
            throw std::runtime_error("Could not initialize glfw");
        }

        m_window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE.c_str(),
                                    nullptr, nullptr);

        if (!m_window) {
            throw std::runtime_error("Could not create glfw window");
        }

        glfwShowWindow(m_window);
    }

    void Window::input(Application* app)
    {
        glfwPollEvents();

        if (glfwWindowShouldClose(m_window)) {
            app->requestStop();
        }
    }

    void Window::cleanup()
    {
        glfwDestroyWindow(m_window);
    }

    GLFWwindow* Window::getWindow()
    {
        return m_window;
    }
} // namespace mineblocks