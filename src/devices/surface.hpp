#pragma once

#include "devices/instance.hpp"
#include "devices/physical_device.hpp"
#include "devices/window.hpp"

namespace mineblocks {
    class Surface {
      public:
        Surface(Instance* instance, PhysicalDevice* physicalDevice, Window* window);
        ~Surface();

        [[nodiscard]] const VkSurfaceKHR& getSurface() const;
        [[nodiscard]] VkSurfaceCapabilitiesKHR getCapabilities() const;
        [[nodiscard]] VkSurfaceFormatKHR getFormat() const;

      private:
        Instance* m_instance;

        VkSurfaceKHR m_surface = VK_NULL_HANDLE;
        VkSurfaceCapabilitiesKHR m_capabilities{};
        VkSurfaceFormatKHR m_format{};
    };
} // namespace mineblocks
