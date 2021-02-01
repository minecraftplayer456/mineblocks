#pragma once

#include <glad/glad.h>

namespace Mineblocks {
    // EXCEPTION(Exception, ShaderException);

    class ShaderLoader {
      public:
        static auto CompileShader(const GLchar* source, GLenum shaderType) -> GLuint;
        static auto LinkProgramme(GLuint vertexShaderId, GLuint fragmentShaderId)
            -> GLuint;
        static auto LoadShaders(const std::string& vertexShader,
                                const std::string& fragmentShader) -> GLuint;
    };
} // namespace Mineblocks