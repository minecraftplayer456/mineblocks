#pragma once

#include "Shader.hpp"

namespace Mineblocks {
    class BasicShader : public Shader {
      public:
        BasicShader();

        void LoadPosVector(const glm::vec3& posVec);

        void GetUniforms() override;

      private:
        GLuint posLocation;
    };
} // namespace Mineblocks