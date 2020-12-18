#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace Mineblocks {
    class Shader {
      public:
        Shader(const std::string& vertexFile, const std::string& fragmentFile);
        ~Shader();

        void UseShader() const;

        void LoadInt(GLuint location, int value);
        void LoadFloat(GLuint location, float value);

        void LoadVector2(GLuint location, const glm::vec2& vec);
        void LoadVector3(GLuint location, const glm::vec3& vec);
        void LoadVector4(GLuint location, const glm::vec4& vec);

      protected:
        GLuint id;

        virtual void GetUniforms() = 0;
    };
} // namespace Mineblocks