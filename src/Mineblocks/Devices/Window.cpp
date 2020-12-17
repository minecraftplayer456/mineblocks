#include "Window.hpp"

#include "Mineblocks/Application.hpp"

namespace Mineblocks {
    EXCEPTION(Exception, GlfwException)

    void glfwFramebufferSizeCallback(GLFWwindow* window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    Window::Window(Application* app)
        : app(app)
        , width(900)
        , height(700)
        , title("Mineblocks")
    {
        LOG_DEBUG(Devices, "Creating game window");

        if (glfwInit() == GLFW_FALSE) {
            THROW(GlfwException, "Could not initialize glfw");
        }

        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
        // glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_STENCIL_BITS, 8);
        glfwWindowHint(GLFW_STEREO, GLFW_FALSE);

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        window = glfwCreateWindow(width, height, title, nullptr, nullptr);

        if (!window) {
            glfwTerminate();
            THROW(GlfwException, "Could not create window")
        }

        glfwMakeContextCurrent(window);

        glfwSetFramebufferSizeCallback(window, glfwFramebufferSizeCallback);

        auto videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        uint32_t x = (videoMode->width - width) / 2;
        uint32_t y = (videoMode->height - height) / 2;

        glfwSetWindowPos(window, x, y);

        glfwShowWindow(window);
    }

    Window::~Window()
    {
        LOG_DEBUG(Devices, "Destroying game window");

        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void Window::Input()
    {
        glfwPollEvents();
        if (glfwWindowShouldClose(window) == GLFW_TRUE) {
            LOG_DEBUG(Devices, "Game window requested closing");
            app->RequestClose();
        }
    }

    void Window::Render()
    {
        glfwSwapBuffers(window);
    }

    auto Window::GetWindow() -> GLFWwindow*
    {
        return window;
    }

    auto Window::GetWidth() const -> uint32_t
    {
        return width;
    }

    auto Window::GetHeight() const -> uint32_t
    {
        return height;
    }

    auto Window::GetTitle() const -> const char*
    {
        return title;
    }
} // namespace Mineblocks