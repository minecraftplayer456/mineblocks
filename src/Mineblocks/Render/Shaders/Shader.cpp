#include "Shader.hpp"

#include "Mineblocks/Util/FileUtil.hpp"

namespace Mineblocks {
    Shader::~Shader()
    {
        Destroy();
    }

    auto Shader::CompileShader(const std::string_view& source, GLenum shaderType)
    {
        auto shaderId = glCreateShader(shaderType);

        const GLchar* sourcePtr = source.data();
        const GLint sourceLenght = source.length();

        glShaderSource(shaderId, 1, &sourcePtr, &sourceLenght);
        glCompileShader(shaderId);

        GLint logLength = 0;
        glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);
        if (logLength) {
            std::string infoLog(logLength, 0);
            glGetShaderInfoLog(shaderId, logLength, nullptr, infoLog.data());

            THROW_ARGS(ShaderException, "Could not compile shader: {}", infoLog);
        }

        return shaderId;
    }

    auto Shader::LinkShaders(GLuint vertexShaderId, GLuint fragmentShaderId)
    {
        auto id = glCreateProgram();

        glAttachShader(id, vertexShaderId);
        glAttachShader(id, fragmentShaderId);

        glLinkProgram(id);

        glDetachShader(id, vertexShaderId);
        glDetachShader(id, fragmentShaderId);

        GLint logLength = 0;
        glGetProgramiv(id, GL_INFO_LOG_LENGTH, &logLength);
        if (logLength) {
            std::string infoLog(logLength, 0);
            glGetProgramInfoLog(id, logLength, nullptr, infoLog.data());

            THROW_ARGS(ShaderException, "Could not link shader: {}", infoLog);
        }

        return id;
    }

    void Shader::Create(const std::string_view& vertexFile,
                        const std::string_view& fragmentFile)
    {
        glUseProgram(0);

        auto vertexSource = FileUtil::GetFileContents(vertexFile);
        auto fragmentSource = FileUtil::GetFileContents(fragmentFile);

        auto vertexId = CompileShader(vertexSource, GL_VERTEX_SHADER);
        auto fragmentId = CompileShader(fragmentSource, GL_FRAGMENT_SHADER);

        auto programId = LinkShaders(vertexId, fragmentId);
    }

    void Shader::Destroy()
    {
    }
    void Shader::Bind()
    {
    }

    void Shader::LoadInt(GLuint location, int value)
    {
    }

    void Shader::LoadFloat(GLuint location, float value)
    {
    }

    void Shader::LoadVector2(GLuint location, const glm::vec2& vec)
    {
    }

    void Shader::LoadVector3(GLuint location, const glm::vec3& vec)
    {
    }

    void Shader::LoadVector4(GLuint location, const glm::vec4& vec)
    {
    }

    auto Shader::GetUniformLocation(const char* name)
    {
        return nullptr;
    }

    void Shader::LoadUniforms()
    {
    }
} // namespace Mineblocks