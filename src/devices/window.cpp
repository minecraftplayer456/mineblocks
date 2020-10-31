#include "window.hpp"

#include <stdexcept>

#include <spdlog/spdlog.h>

#include "core/application.hpp"

namespace mineblocks {
    void glfwWindowSizeCallback(GLFWwindow* window, int width, int height)
    {
        auto win = static_cast<Window*>(glfwGetWindowUserPointer(window));
        win->m_size = {width, height};
    }

    void Window::init()
    {
        spdlog::debug("Create window}");

        if (!glfwInit()) {
            throw std::runtime_error("Could not initialize glfw");
        }

        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

        m_window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE.c_str(),
                                    nullptr, nullptr);

        if (!m_window) {
            throw std::runtime_error("Could not create glfw window");
        }

        m_size = {WINDOW_WIDTH, WINDOW_HEIGHT};

        glfwSetWindowUserPointer(m_window, this);

        glfwShowWindow(m_window);

        glfwSetWindowSizeCallback(m_window, glfwWindowSizeCallback);
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

    const glm::uvec2& Window::getSize() const
    {
        return m_size;
    }

    std::pair<const char**, uint32_t> Window::getExtensions()
    {
        uint32_t glfwExtensionCount;
        auto glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        return std::make_pair(glfwExtensions, glfwExtensionCount);
    }

    VkResult Window::createSurface(VkInstance const& instance,
                                   const VkAllocationCallbacks* allocator,
                                   VkSurfaceKHR* surface) const
    {
        return glfwCreateWindowSurface(instance, m_window, allocator, surface);
    }
} // namespace mineblocks