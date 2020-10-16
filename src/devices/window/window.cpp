#include "window.hpp"

#include <stdexcept>
#include <utility>

namespace engine::devices::window {
    Window::Window(int id, int width, int height, std::string title)
        : m_id(id)
        , m_width(width)
        , m_height(height)
        , m_title(std::move(title))
    {
        m_window = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);

        if (!m_window) {
            throw std::runtime_error("GLFW failed to create window");
        }

        auto videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());

        glfwSetWindowPos(m_window, (videoMode->width - m_width) / 2,
                         (videoMode->height - m_height) / 2);
    }

    void Window::show()
    {
        if (!m_visible) {
            m_visible = true;
            glfwShowWindow(m_window);
        }
    }

    void Window::hide()
    {
        if (m_visible) {
            m_visible = false;
            glfwHideWindow(m_window);
        }
    }

    void Window::destroy()
    {
        glfwDestroyWindow(m_window);
    }

    void Window::setTitle(std::string title)
    {
        m_title = std::move(title);
        glfwSetWindowTitle(m_window, m_title.c_str());
    }

    void Window::setSize(int width, int height)
    {
        m_width = width;
        m_height = height;
        glfwSetWindowSize(m_window, m_width, m_height);
    }

    int Window::getId() const
    {
        return m_id;
    }

    bool Window::isVisible() const
    {
        return m_visible;
    }

    int Window::getWidth() const
    {
        return m_width;
    }

    int Window::getHeight() const
    {
        return m_height;
    }

    std::string Window::getTitle() const
    {
        return m_title;
    }

    GLFWwindow* Window::getWindow() const
    {
        return m_window;
    }
} // namespace engine::devices::window