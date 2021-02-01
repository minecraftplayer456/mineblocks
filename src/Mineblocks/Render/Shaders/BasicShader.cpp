#include "BasicShader.hpp"

namespace Mineblocks {
    BasicShader::BasicShader()
        : Shader("Basic", "Basic")
    {
        GetUniforms();
    }

    void BasicShader::LoadPosVector(const glm::vec3& posVec)
    {
        LoadVector3(posLocation, posVec);
    }

    void BasicShader::GetUniforms()
    {
        UseShader();
        posLocation = glGetUniformLocation(id, "pos");
    }
} // namespace Mineblocks