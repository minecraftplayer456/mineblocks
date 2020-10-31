#pragma once

#include "devices/logical_device.hpp"

namespace mineblocks {
    class Image {
      public:
        static void createImageView(const LogicalDevice* logicalDevice,
                                    const VkImage& image, VkImageView& imageView,
                                    VkImageViewType type, VkFormat format,
                                    VkImageAspectFlags imageAspect, uint32_t mipLevels,
                                    uint32_t baseMipLevel, uint32_t layerCount,
                                    uint32_t baseArrayLayer);
    };
} // namespace mineblocks