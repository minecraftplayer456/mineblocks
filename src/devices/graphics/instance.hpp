#pragma once

#include <vulkan/vulkan.h>

#include "app.hpp"

namespace engine::devices::graphics {
    const std::string engineName = "engine";
    const utils::Version engineVersion = utils::Version(0, 1, 0);
    const int vkApiVersion = VK_VERSION_1_2;

    class Instance {
      public:
        void create(const App& app);

        void destroy();

        [[nodiscard]] VkInstance getInstance() const;

      private:
        VkInstance m_instance;
    };
} // namespace engine::devices::graphics