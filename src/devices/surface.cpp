#include "surface.hpp"

#include <spdlog/spdlog.h>

namespace mineblocks {
    Surface::Surface(Instance* instance, PhysicalDevice* physicalDevice, Window* window)
        : m_instance(instance)
    {
        spdlog::debug("Create vulkan surface");

        Graphics::checkVk(
            window->createSurface(m_instance->getInstance(), nullptr, &m_surface));
        Graphics::checkVk(vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
            physicalDevice->getDevice(), m_surface, &m_capabilities));

        uint32_t formatCount;
        vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice->getDevice(), m_surface,
                                             &formatCount, nullptr);
        std::vector<VkSurfaceFormatKHR> formats(formatCount);
        vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice->getDevice(), m_surface,
                                             &formatCount, formats.data());

        if (formatCount == 1 && formats[0].format == VK_FORMAT_UNDEFINED) {
            m_format.format = VK_FORMAT_B8G8R8A8_UNORM;
            m_format.colorSpace = formats[0].colorSpace;
        }
        else {
            bool found_B8G8R8A8_UNORM = false;

            for (auto& surfaceFormat : formats) {
                if (surfaceFormat.format == VK_FORMAT_B8G8R8A8_UNORM) {
                    m_format.format = surfaceFormat.format;
                    m_format.colorSpace = surfaceFormat.colorSpace;
                    found_B8G8R8A8_UNORM = true;
                    break;
                }
            }

            if (!found_B8G8R8A8_UNORM) {
                m_format.format = formats[0].format;
                m_format.colorSpace = formats[0].colorSpace;
            }
        }
    }

    Surface::~Surface()
    {
        vkDestroySurfaceKHR(m_instance->getInstance(), m_surface, nullptr);
    }

    const VkSurfaceKHR& Surface::getSurface() const
    {
        return m_surface;
    }

    VkSurfaceCapabilitiesKHR Surface::getCapabilities() const
    {
        return m_capabilities;
    }

    VkSurfaceFormatKHR Surface::getFormat() const
    {
        return m_format;
    }
} // namespace mineblocks