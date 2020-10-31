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