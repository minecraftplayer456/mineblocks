#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Shader.hpp"

const int WINDOW_HEIGHT = 700;
const int WINDOW_WIDTH = 900;
const char* WINDOW_TITLE = "Mineblocks";

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

auto main() -> int
{
    spdlog::set_level(spdlog::level::trace);

    spdlog::info("Starting mineblocks");

    if (glfwInit() == GLFW_FALSE) {
        throw std::runtime_error("Could not initialize glfw");
    }

    // glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    // glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    // glfwWindowHint(GLFW_STENCIL_BITS, 8);
    // glfwWindowHint(GLFW_STEREO, GLFW_FALSE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    spdlog::debug("Creating window");

    GLFWwindow* window =
        glfwCreateWindow(WINDOW_HEIGHT, WINDOW_HEIGHT, WINDOW_TITLE, nullptr, nullptr);

    if (window == nullptr) {
        glfwTerminate();
        throw std::runtime_error("Could not create window");
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        spdlog::critical("Could not load glad");
        throw std::runtime_error("Could not load glad");
    }

    const auto* videoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    uint32_t x = (videoMode->width - WINDOW_WIDTH) / 2;
    uint32_t y = (videoMode->height - WINDOW_HEIGHT) / 2;

    glfwSetWindowPos(window, x, y);

    // glfwShowWindow(window);

    // glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    float vertices[] = {
        // positions         // colors
        0.5f,  -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
        0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f  // top

    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then
    // configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                          (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this
    // VAO, but this rarely happens. Modifying other VAOs requires a call to
    // glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's
    // not directly necessary. glBindVertexArray(0);

    // as we only have a single shader, we could also just activate our shader once
    // beforehand if we want to
    Shader shader("shaders/basic.vert", "shaders/basic.frag");

    // glUseProgram(shaderProgram);
    shader.use();

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window)) {
        // input
        // -----
        // processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // render the triangle
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    // glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}
