#pragma once

#include <Engine/Core/EntryPoint.hpp>

namespace Mineblocks {
    class App : public Engine::Application {
      public:
        App();

        void Init();
    };
} // namespace Mineblocks