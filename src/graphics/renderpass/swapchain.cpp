#include "swapchain.hpp"

#include <spdlog/spdlog.h>

#include "graphics/images/image.hpp"

namespace mineblocks {
    static const std::vector<VkCompositeAlphaFlagBitsKHR> COMPOSITE_ALPHA_FLAGS = {
        VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
        VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR,
        VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR,
        VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR,
    };

    Swapchain::Swapchain(const PhysicalDevice* physicalDevice,
                         const LogicalDevice* logicalDevice, const Surface* surface,
                         const VkExtent2D& extent, const Swapchain* oldSwapchain)
        : m_logicalDevice(logicalDevice)
    {
        spdlog::debug("Create swapchain");

        auto surfaceFormat = surface->getFormat();
        auto surfaceCapabilities = surface->getCapabilities();
        auto graphicsFamily = m_logicalDevice->getGraphicsFamily();
        auto presentFamily = m_logicalDevice->getPresentFamily();

        uint32_t physicalPresentModeCount;
        vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice->getDevice(),
                                                  surface->getSurface(),
                                                  &physicalPresentModeCount, nullptr);
        std::vector<VkPresentModeKHR> physicalPresentModes(physicalPresentModeCount);
        vkGetPhysicalDeviceSurfacePresentModesKHR(
            physicalDevice->getDevice(), surface->getSurface(), &physicalPresentModeCount,
            physicalPresentModes.data());

        VkPresentModeKHR presentMode = VK_PRESENT_MODE_FIFO_KHR;

        for (const auto& physicalPresentMode : physicalPresentModes) {
            if (physicalPresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
                presentMode = physicalPresentMode;
            }

            if (presentMode == VK_PRESENT_MODE_IMMEDIATE_KHR) {
                presentMode = physicalPresentMode;
            }
        }

        auto desiredImageCount = surfaceCapabilities.minImageCount + 1;

        if (surfaceCapabilities.maxImageCount > 0 &&
            desiredImageCount > surfaceCapabilities.maxImageCount) {
            desiredImageCount = surfaceCapabilities.maxImageCount;
        }

        auto preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;

        if (surfaceCapabilities.supportedTransforms &
            VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR) {
            preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
        }
        else {
            preTransform = surfaceCapabilities.currentTransform;
        }

        auto compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

        for (const auto& compositeAlphaFlag : COMPOSITE_ALPHA_FLAGS) {
            if (surfaceCapabilities.supportedCompositeAlpha & compositeAlphaFlag) {
                compositeAlpha = compositeAlphaFlag;
                break;
            }
        }

        VkSwapchainCreateInfoKHR swapchainCreateInfo = {};
        swapchainCreateInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
        swapchainCreateInfo.surface = surface->getSurface();
        swapchainCreateInfo.minImageCount = desiredImageCount;
        swapchainCreateInfo.imageFormat = surfaceFormat.format;
        swapchainCreateInfo.imageColorSpace = surfaceFormat.colorSpace;
        swapchainCreateInfo.imageExtent = extent;
        swapchainCreateInfo.imageArrayLayers = 1;
        swapchainCreateInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
        swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
        swapchainCreateInfo.preTransform =
            static_cast<VkSurfaceTransformFlagBitsKHR>(preTransform);
        swapchainCreateInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        swapchainCreateInfo.compositeAlpha = compositeAlpha;
        swapchainCreateInfo.presentMode = presentMode;
        swapchainCreateInfo.clipped = VK_TRUE;
        swapchainCreateInfo.oldSwapchain = VK_NULL_HANDLE;

        if (surfaceCapabilities.supportedUsageFlags & VK_IMAGE_USAGE_TRANSFER_SRC_BIT)
            swapchainCreateInfo.imageUsage |= VK_IMAGE_USAGE_TRANSFER_SRC_BIT;
        if (surfaceCapabilities.supportedUsageFlags & VK_IMAGE_USAGE_TRANSFER_DST_BIT)
            swapchainCreateInfo.imageUsage |= VK_IMAGE_USAGE_TRANSFER_DST_BIT;

        if (oldSwapchain)
            swapchainCreateInfo.oldSwapchain = oldSwapchain->m_swapChain;

        if (graphicsFamily != presentFamily) {
            std::array<uint32_t, 2> queueFamily = {graphicsFamily, presentFamily};
            swapchainCreateInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
            swapchainCreateInfo.queueFamilyIndexCount =
                static_cast<uint32_t>(queueFamily.size());
            swapchainCreateInfo.pQueueFamilyIndices = queueFamily.data();
        }

        Graphics::checkVk(vkCreateSwapchainKHR(
            logicalDevice->getDevice(), &swapchainCreateInfo, nullptr, &m_swapChain));

        Graphics::checkVk(vkGetSwapchainImagesKHR(m_logicalDevice->getDevice(),
                                                  m_swapChain, &m_imageCount, nullptr));
        m_images.resize(m_imageCount);
        m_imageViews.resize(m_imageCount);
        Graphics::checkVk(vkGetSwapchainImagesKHR(
            m_logicalDevice->getDevice(), m_swapChain, &m_imageCount, m_images.data()));

        for (uint32_t i = 0; i < m_imageCount; i++) {
            Image::createImageView(m_logicalDevice, m_images[i], m_imageViews[i],
                                   VK_IMAGE_VIEW_TYPE_2D, surfaceFormat.format,
                                   VK_IMAGE_ASPECT_COLOR_BIT, 1, 0, 1, 0);
        }

        VkFenceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
        vkCreateFence(m_logicalDevice->getDevice(), &createInfo, nullptr, &m_imageFence);
    }

    Swapchain::~Swapchain()
    {
        spdlog::debug("Destroy swapchain");

        vkDestroySwapchainKHR(m_logicalDevice->getDevice(), m_swapChain, nullptr);

        for (const auto& imageView : m_imageViews) {
            vkDestroyImageView(m_logicalDevice->getDevice(), imageView, nullptr);
        }

        vkDestroyFence(m_logicalDevice->getDevice(), m_imageFence, nullptr);
    }

    VkResult Swapchain::acquireNextImage(VkSemaphore const& presentSemaphore,
                                         VkFence fence)
    {
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    VkResult Swapchain::queuePresent(VkQueue const& presentQueue,
                                     VkSemaphore const& semaphore)
    {
        return VK_ERROR_INITIALIZATION_FAILED;
    }

    const VkSwapchainKHR& Swapchain::getSwapchain() const
    {
        return m_swapChain;
    }

    const std::vector<VkImage>& Swapchain::getImages() const
    {
        return m_images;
    }

    const std::vector<VkImageView>& Swapchain::getImageViews() const
    {
        return m_imageViews;
    }

    const VkImage& Swapchain::getActiveImage() const
    {
        return m_images[m_activeImageIndex];
    }

    uint32_t Swapchain::getImageCount() const
    {
        return m_imageCount;
    }

    uint32_t Swapchain::getActiveImageIndex() const
    {
        return m_activeImageIndex;
    }
} // namespace mineblocks