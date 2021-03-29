#include "Shader.hpp"

#include <glad/glad.h>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
    std::string vertexCode;
    std::string fragmentCode;

    std::ifstream vertexFile;
    std::ifstream fragmentFile;

    vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        vertexFile.open(vertexPath);
        fragmentFile.open(fragmentPath);

        std::stringstream vertexStream;
        std::stringstream fragmentStream;

        vertexStream << vertexFile.rdbuf();
        fragmentStream << fragmentFile.rdbuf();

        vertexFile.close();
        fragmentFile.close();

        vertexCode = vertexStream.str();
        fragmentCode = fragmentStream.str();
    }
    catch (const std::ifstream::failure& e) {
        spdlog::error("Shader file could not be read: {}", e.what());
    }

    unsigned int vertexId;
    unsigned int fragmentId;

    const char* vertexCodeArray = vertexCode.c_str();
    const char* fragmentCodeArray = fragmentCode.c_str();

    vertexId = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexId, 1, &vertexCodeArray, nullptr);
    glCompileShader(vertexId);
    checkCompileError(vertexId);

    fragmentId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentId, 1, &fragmentCodeArray, nullptr);
    glCompileShader(fragmentId);
    checkCompileError(fragmentId);

    id = glCreateProgram();
    glAttachShader(id, vertexId);
    glAttachShader(id, fragmentId);
    glLinkProgram(id);
    checkLinkingError(id);

    glDeleteShader(vertexId);
    glDeleteShader(fragmentId);
}

Shader::~Shader()
{
    glDeleteProgram(id);
}

void Shader::use() const
{
    glUseProgram(id);
}

void Shader::setBool(const char* name, bool value) const
{
    glUniform1i(glGetUniformLocation(id, name), static_cast<GLint>(value));
}

void Shader::setInt(const char* name, bool value) const
{
    glUniform1i(glGetUniformLocation(id, name), value);
}

void Shader::setFloat(const char* name, float value) const
{
    glUniform1f(glGetUniformLocation(id, name), value);
}

void Shader::checkCompileError(unsigned int shaderId)
{
    int success;
    char log[1024];

    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(shaderId, 1024, nullptr, log);
        spdlog::error("Could not compile shader {}: {}", shaderId, log);
    }
}

void Shader::checkLinkingError(unsigned int programmeId)
{
    int success;
    char log[1024];

    glGetProgramiv(programmeId, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(programmeId, 1024, nullptr, log);
        spdlog::error("Could not link shader {}: {}", programmeId, log);
    }
}
