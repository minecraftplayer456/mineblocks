#include "image.hpp"

namespace mineblocks {
    void Image::createImageView(const LogicalDevice* logicalDevice, const VkImage& image,
                                VkImageView& imageView, VkImageViewType type,
                                VkFormat format, VkImageAspectFlags imageAspect,
                                uint32_t mipLevels, uint32_t baseMipLevel,
                                uint32_t layerCount, uint32_t baseArrayLayer)
    {
        VkImageViewCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
        createInfo.image = image;
        createInfo.viewType = type;
        createInfo.format = format;
        createInfo.components = {VK_COMPONENT_SWIZZLE_R, VK_COMPONENT_SWIZZLE_G,
                                 VK_COMPONENT_SWIZZLE_B, VK_COMPONENT_SWIZZLE_A};
        createInfo.subresourceRange.aspectMask = imageAspect;
        createInfo.subresourceRange.baseMipLevel = baseMipLevel;
        createInfo.subresourceRange.levelCount = mipLevels;
        createInfo.subresourceRange.baseArrayLayer = baseArrayLayer;
        createInfo.subresourceRange.layerCount = layerCount;
        Graphics::checkVk(vkCreateImageView(logicalDevice->getDevice(), &createInfo,
                                            nullptr, &imageView));
    }
} // namespace mineblocks