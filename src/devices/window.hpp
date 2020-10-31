#pragma once

#define GLFW_INCLUDE_VULKAN

#include <string>

#include <GLFW/glfw3.h>
#include <glm/vec2.hpp>
#include <vulkan/vulkan.h>

namespace mineblocks {
    class Application;

    const unsigned int WINDOW_WIDTH = 900;
    const unsigned int WINDOW_HEIGHT = 700;
    const std::string WINDOW_TITLE = "Mineblocks";

    class Window {
      public:
        void init();
        void input(Application* app);
        void cleanup();

        GLFWwindow* getWindow();

        const glm::uvec2& getSize() const;

        static std::pair<const char**, uint32_t> getExtensions();
        VkResult createSurface(const VkInstance& instance,
                               const VkAllocationCallbacks* allocator,
                               VkSurfaceKHR* surface) const;

      private:
        glm::uvec2 m_size;

        GLFWwindow* m_window = nullptr;

        friend void glfwWindowSizeCallback(GLFWwindow* window, int width, int height);
    };
} // namespace mineblocks