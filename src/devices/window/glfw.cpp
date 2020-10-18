#include "glfw.hpp"

#include <memory>
#include <stdexcept>

namespace engine::devices::window {
    void callbackError(int32_t error, const char* description)
    {
        Glfw::assertGlfwResult(error);
    }

    void Glfw::init()
    {
        glfwSetErrorCallback(callbackError);

        if (glfwInit() != GLFW_TRUE) {
            throw std::runtime_error("GLFW failed to initialize!");
        }

        if (glfwVulkanSupported() != GLFW_TRUE) {
            throw std::runtime_error("GLFW failed to support vulkan");
        }

        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_STENCIL_BITS, 8);
        glfwWindowHint(GLFW_STEREO, GLFW_FALSE);
    }

    void Glfw::update()
    {
        glfwPollEvents();
    }

    void Glfw::destroy()
    {
        glfwTerminate();
    }

    std::shared_ptr<Window> Glfw::createWindow(int width, int height,
                                               const std::string& title)
    {
        auto id = m_windows.size() + 1;
        auto window = std::make_shared<Window>(id, width, height, title);
        m_windows.insert(std::make_pair(id, window));
        return window;
    }

    void Glfw::destroyWindow(int id)
    {
        auto window = m_windows[id];
        window->destroy();
        m_windows.erase(id);
    }

    std::shared_ptr<Window> Glfw::getWindow(int id) const
    {
        return m_windows.at(id);
    }

    std::string Glfw::stringifyGlfwResult(int32_t result)
    {
        switch (result) {
            case GLFW_TRUE:
                return "Success";
            case GLFW_NOT_INITIALIZED:
                return "GLFW has not been initialized";
            case GLFW_NO_CURRENT_CONTEXT:
                return "No context is current for this thread";
            case GLFW_INVALID_ENUM:
                return "One of the arguments to the function was an invalid enum value";
            case GLFW_INVALID_VALUE:
                return "One of the arguments to the function was an invalid value";
            case GLFW_OUT_OF_MEMORY:
                return "A memory allocation failed";
            case GLFW_API_UNAVAILABLE:
                return "GLFW could not find support for the requested API on the system";
            case GLFW_VERSION_UNAVAILABLE:
                return "The requested OpenGL or OpenGL ES version is not available";
            case GLFW_PLATFORM_ERROR:
                return "A platform-specific error occurred that does not match any of "
                       "the more specific categories";
            case GLFW_FORMAT_UNAVAILABLE:
                return "The requested format is not supported or available";
            case GLFW_NO_WINDOW_CONTEXT:
                return "The specified window does not have an OpenGL or OpenGL ES "
                       "context";
            default:
                return &"Unknown glfw error: "[result];
        }
    }

    void Glfw::assertGlfwResult(int32_t result)
    {
        if (result == GLFW_TRUE)
            return;

        throw std::runtime_error("Glfw error: " + stringifyGlfwResult(result));
    }

    std::vector<const char*> Glfw::getGlfwVulkanExtensions()
    {
        uint32_t glfwExtensionCount = 0;
        const char** glfwExtensions =
            glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        return std::vector<const char*>(glfwExtensions,
                                        glfwExtensions + glfwExtensionCount);
    }
} // namespace engine::devices::window