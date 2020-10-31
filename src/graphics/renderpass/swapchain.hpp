#pragma once

#include "devices/logical_device.hpp"

namespace mineblocks {
    class Swapchain {
      public:
        Swapchain(const PhysicalDevice* physicalDevice,
                  const LogicalDevice* logicalDevice, const Surface* surface,
                  const VkExtent2D& extent, const Swapchain* oldSwapchain = nullptr);
        ~Swapchain();

        VkResult acquireNextImage(const VkSemaphore& presentSemaphore = VK_NULL_HANDLE,
                                  VkFence fence = VK_NULL_HANDLE);

        VkResult queuePresent(const VkQueue& presentQueue,
                              const VkSemaphore& semaphore = VK_NULL_HANDLE);

        [[nodiscard]] const VkSwapchainKHR& getSwapchain() const;
        [[nodiscard]] const std::vector<VkImage>& getImages() const;
        [[nodiscard]] const std::vector<VkImageView>& getImageViews() const;
        [[nodiscard]] const VkImage& getActiveImage() const;
        [[nodiscard]] uint32_t getImageCount() const;
        [[nodiscard]] uint32_t getActiveImageIndex() const;

      private:
        const LogicalDevice* m_logicalDevice;
        VkSwapchainKHR m_swapChain;

        uint32_t m_imageCount = 0;
        uint32_t m_activeImageIndex;

        std::vector<VkImage> m_images;
        std::vector<VkImageView> m_imageViews;

        VkFence m_imageFence;
    };
} // namespace mineblocks
