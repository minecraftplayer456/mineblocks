#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include <GLFW/glfw3.h>

#include "window.hpp"

namespace engine::devices::window {
    void callbackError(int32_t error, const char* description);

    class Glfw {
      public:
        void init();

        void update();

        void destroy();

        std::shared_ptr<Window> createWindow(int width, int height,
                                             const std::string& title);

        void destroyWindow(int id);

        std::shared_ptr<Window> getWindow(int id) const;

        static std::string stringifyGlfwResult(int32_t result);
        static void assertGlfwResult(int32_t result);

      private:
        std::unordered_map<int, std::shared_ptr<Window>> m_windows;
    };
} // namespace engine::devices::window