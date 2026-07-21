#pragma once

/**
 * @file Vulkan_Texture.hpp
 * @brief Vulkan_TextureData struct definition.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include "Library/Vulkan/Vulkan.hpp"
#include "Resource/Type/Handle.hpp"

namespace Minty
{
    struct Vulkan_TextureData
    {
        // Image Data
        VkImage image = VK_NULL_HANDLE;
        VkFormat format = VK_FORMAT_UNDEFINED;
        VkDeviceMemory memory = VK_NULL_HANDLE;
        VkImageLayout layout = VK_IMAGE_LAYOUT_UNDEFINED;
        VkImageUsageFlags usage = 0;
        VkExtent2D size = {0, 0};
        
        // Texture Data
        VkImageView view = VK_NULL_HANDLE;
        VkSampler sampler = VK_NULL_HANDLE;
    };
}