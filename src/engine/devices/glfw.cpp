#include "glfw.hpp"

#include <spdlog/spdlog.h>

namespace engine::devices {
    void glfwErrorCallback(int32_t error, const char* description)
    {
        throw std::runtime_error("GLFW error: " + std::string(description) + " : " +
                                 Glfw::glfwResultToString(error));
    }

    Glfw::Glfw()
    {
        addStage(core::ModuleLifecycle::Init, [this] { init(); });
        addStage(core::ModuleLifecycle::Input, [this] { input(); });
        addStage(core::ModuleLifecycle::Cleanup, [this] { cleanup(); });
    }

    void Glfw::init()
    {
        spdlog::debug("Initialize glfw");

        glfwSetErrorCallback(glfwErrorCallback);

        checkGlfw(glfwInit(), "Failed to initialize glfw");
        checkGlfw(glfwVulkanSupported(), "Vulkan is not supported");

        glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        glfwWindowHint(GLFW_STENCIL_BITS, 8);
        glfwWindowHint(GLFW_STEREO, GLFW_FALSE);

        spdlog::trace("Initialized glfw");
    }

    void Glfw::input()
    {
        glfwPollEvents();
    }

    void Glfw::cleanup()
    {
        spdlog::debug("Cleanup glfw");

        glfwTerminate();

        spdlog::trace("Cleaned up glfw");
    }

    std::string Glfw::glfwResultToString(int32_t result)
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
                return "";
        }
    }

    void Glfw::checkGlfw(int32_t result, const std::string& message)
    {
        if (result == GLFW_TRUE)
            return;

        glfwErrorCallback(result, message.c_str());
    }
} // namespace engine::devices