#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include "spdlog/spdlog.h"

const int WINDOW_HEIGHT = 700;
const int WINDOW_WIDTH = 900;
const char* WINDOW_TITLE = "Mineblocks";

auto compileShaders(const char* path, GLuint shaderType) -> GLuint
{
    GLuint id = glCreateShader(shaderType);

    std::string code;
    std::ifstream codeStream(path, std::ios::in);

    if (codeStream.is_open()) {
        std::stringstream sstr;
        sstr << codeStream.rdbuf();
        code = sstr.str();
        codeStream.close();
    }
    else {
        spdlog::critical("Could not open shader {}", path);
        throw std::runtime_error("Could not open shader");
    }

    spdlog::debug("Compiling shader {}", path);

    int logLength;
    const char* sourcePtr = code.c_str();

    glShaderSource(id, 1, &sourcePtr, nullptr);
    glCompileShader(id);

    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        GLchar errorMsg = 0;
        glGetShaderInfoLog(id, logLength, nullptr, &errorMsg);
        spdlog::error("Shader compilation error: {}", errorMsg);
    }

    return id;
}

auto linkShaders(const char* vertexPath, const char* fragmentPath) -> GLuint
{
    GLuint vertexId = compileShaders(vertexPath, GL_VERTEX_SHADER);
    GLuint fragmentId = compileShaders(fragmentPath, GL_FRAGMENT_SHADER);

    spdlog::debug("Linking vertex shader {} and fragement shader {}", vertexPath,
                  fragmentPath);

    GLuint id = glCreateProgram();
    glAttachShader(id, vertexId);
    glAttachShader(id, fragmentId);
    glLinkProgram(id);

    int logLength = 0;
    glGetProgramiv(id, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        GLchar errorMsg = 0;
        glGetShaderInfoLog(id, logLength, nullptr, &errorMsg);
        spdlog::error("Shader linking error: {}", errorMsg);
    }

    glDetachShader(id, vertexId);
    glDetachShader(id, fragmentId);

    glDeleteShader(vertexId);
    glDeleteShader(fragmentId);

    return id;
}

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

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

    glfwShowWindow(window);

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};

    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    GLuint programId = linkShaders("shaders/basic.vert", "shaders/basic.frag");
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(programId);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}
