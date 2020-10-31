#pragma once

#include "devices/instance.hpp"
#include "devices/physical_device.hpp"
#include "devices/window.hpp"

namespace mineblocks {
    class Surface {
      public:
        Surface(const Instance* instance, const PhysicalDevice* physicalDevice,
                const Window* window);
        ~Surface();

        [[nodiscard]] const VkSurfaceKHR& getSurface() const;
        [[nodiscard]] VkSurfaceCapabilitiesKHR getCapabilities() const;
        [[nodiscard]] VkSurfaceFormatKHR getFormat() const;

      private:
        const Instance* m_instance;

        VkSurfaceKHR m_surface = VK_NULL_HANDLE;
        VkSurfaceCapabilitiesKHR m_capabilities{};
        VkSurfaceFormatKHR m_format{};
    };
} // namespace mineblocks
