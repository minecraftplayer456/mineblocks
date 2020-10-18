#pragma once

#include <string>
#include <vector>

#include "version.hpp"

namespace engine::utils {
    struct AppInfo {
        std::string m_appName = "mineblocks";
        Version m_appVersion = Version(0, 1, 0);

        bool m_vulkanDebug = true;

        std::vector<const char*> m_vulkanValidationLayers = {"VK_LAYER_LUNARG_api_dump"};
    };
} // namespace engine::utils