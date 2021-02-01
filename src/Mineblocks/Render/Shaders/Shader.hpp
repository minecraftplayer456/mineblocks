#pragma once

#include "ShaderLoader.hpp"
#include <glm/glm.hpp>

namespace Mineblocks {
    EXCEPTION(Exception, ShaderException);

    class Shader {
      public:
        Shader() = default;
        ~Shader();

        static auto CompileShader(const std::string_view& source, GLenum shaderType);
        static auto LinkShaders(GLuint vertexShaderId, GLuint fragmentShaderId);

        void Create(const std::string_view& vertexFile,
                    const std::string_view& fragmentFile);
        void Destroy();
        void Bind();

        void LoadInt(GLuint location, int value);
        void LoadFloat(GLuint location, float value);

        void LoadVector2(GLuint location, const glm::vec2& vec);
        void LoadVector3(GLuint location, const glm::vec3& vec);
        void LoadVector4(GLuint location, const glm::vec4& vec);

        auto GetUniformLocation(const char* name);

      protected:
        GLuint handle = 0;

        virtual void LoadUniforms();
    };
} // namespace Mineblocks