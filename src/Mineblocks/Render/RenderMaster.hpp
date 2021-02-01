#pragma once

#include "Mineblocks/Render/Shaders/BasicShader.hpp"

namespace Mineblocks {
    class RenderMaster {
      public:
        void Init();

        void Render();

      private:
        unsigned int vao;

        BasicShader shader;
    };
} // namespace Mineblocks