#pragma once

#include <GLFW/glfw3.h>

#include "engine/core/module.hpp"

namespace engine::devices {
    class Glfw : public core::Module {
      public:
        Glfw();

        void init();
        void input();
        void cleanup();

        static std::string glfwResultToString(int32_t result);
        static void checkGlfw(int32_t result, const std::string& message);
    };
} // namespace engine::devices