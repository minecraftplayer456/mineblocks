#include "RenderMaster.hpp"

namespace Mineblocks {
    const float vertices[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};

    void RenderMaster::Init()
    {
        LOG_DEBUG(Render, "Initializing render master");

        glGenBuffers(1, &vao);
        glBindBuffer(GL_ARRAY_BUFFER, vao);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }

    void RenderMaster::Render()
    {
        shader.UseShader();
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
} // namespace Mineblocks