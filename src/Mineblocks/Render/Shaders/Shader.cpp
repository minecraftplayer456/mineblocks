#include "Shader.hpp"

#include "ShaderLoader.hpp"

namespace Mineblocks {
    Shader::Shader(const std::string& vertexFile, const std::string& fragmentFile)
        : id(ShaderLoader::LoadShaders(vertexFile, fragmentFile))
    {
        UseShader();
    }

    Shader::~Shader()
    {
        glDeleteProgram(id);
    }

    void Shader::UseShader() const
    {
        glUseProgram(id);
    }

    void Shader::LoadInt(GLuint location, int value)
    {
        glUniform1i(location, value);
    }

    void Shader::LoadFloat(GLuint location, float value)
    {
        glUniform1f(location, value);
    }

    void Shader::LoadVector2(GLuint location, const glm::vec2& vec)
    {
        glUniform2f(location, vec.x, vec.y);
    }

    void Shader::LoadVector3(GLuint location, const glm::vec3& vec)
    {
        glUniform3f(location, vec.x, vec.y, vec.z);
    }

    void Shader::LoadVector4(GLuint location, const glm::vec4& vec)
    {
        glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
    }
} // namespace Mineblocks