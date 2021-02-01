#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "spdlog/spdlog.h"

const int WINDOW_HEIGHT = 700;
const int WINDOW_WIDTH = 900;
const char* WINDOW_TITLE = "Mineblocks";

auto main() -> int
{
    spdlog::info("Starting mineblocks");

    spdlog::debug("Init glfw");
    if (glfwInit() == GLFW_FALSE) {
        throw std::runtime_error("Could not initialize glfw");
    }

    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    // glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    glfwWindowHint(GLFW_STENCIL_BITS, 8);
    glfwWindowHint(GLFW_STEREO, GLFW_FALSE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    spdlog::debug("Creating window");

    GLFWwindow* window =
        glfwCreateWindow(WINDOW_HEIGHT, WINDOW_HEIGHT, WINDOW_TITLE, nullptr, nullptr);

    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Could not create window");
    }

    glfwMakeContextCurrent(window);
    gladLoadGL();

    auto videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    uint32_t x = (videoMode->width - WINDOW_WIDTH) / 2;
    uint32_t y = (videoMode->height - WINDOW_HEIGHT) / 2;

    glfwSetWindowPos(window, x, y);

    glfwShowWindow(window);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
    }

    return 0;
}
