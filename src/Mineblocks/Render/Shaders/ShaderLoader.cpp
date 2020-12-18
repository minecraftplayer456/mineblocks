#include "ShaderLoader.hpp"

#include "Mineblocks/Util/FileUtil.hpp"

namespace Mineblocks {
    auto ShaderLoader::CompileShader(const GLchar* source, GLenum shaderType) -> GLuint
    {
        auto shaderId = glCreateShader(shaderType);

        glShaderSource(shaderId, 1, &source, nullptr);
        glCompileShader(shaderId);

        GLint success = 0;
        GLchar infoLog[512];

        glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);

        if (!success) {
            glGetShaderInfoLog(shaderId, 512, nullptr, infoLog);
            THROW_ARGS(ShaderException, "Unable to load shader: {}; Type: {}; Code: {}",
                       infoLog, shaderType, source);
        }

        return shaderId;
    }

    auto ShaderLoader::LinkProgramme(GLuint vertexShaderId, GLuint fragmentShaderId)
        -> GLuint
    {
        auto id = glCreateProgram();

        glAttachShader(id, vertexShaderId);
        glAttachShader(id, fragmentShaderId);

        glLinkProgram(id);

        return id;
    }

    auto ShaderLoader::LoadShaders(const std::string& vertexShader,
                                   const std::string& fragmentShader) -> GLuint
    {
        auto vertexSource =
            FileUtil::GetFileContents("Shaders/" + vertexShader + ".vert");
        auto fragmentSource =
            FileUtil::GetFileContents("Shaders/" + fragmentShader + ".frag");

        auto vertexShaderId = CompileShader(vertexSource.c_str(), GL_VERTEX_SHADER);
        auto fragmentShaderId = CompileShader(fragmentSource.c_str(), GL_FRAGMENT_SHADER);

        auto shaderId = LinkProgramme(vertexShaderId, fragmentShaderId);

        glDeleteShader(vertexShaderId);
        glDeleteShader(fragmentShaderId);

        return shaderId;
    }
} // namespace Mineblocks