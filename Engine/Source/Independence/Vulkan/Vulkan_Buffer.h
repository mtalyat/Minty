#pragma once

/**
 * @file Vulkan_Buffer.h
 * @brief Vulkan_BufferData struct definition.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.h"
#include "Library/Vulkan/Vulkan.h"

namespace Minty
{
    struct Vulkan_BufferData
    {
        VkBuffer buffer = VK_NULL_HANDLE;
        VkDeviceMemory memory = VK_NULL_HANDLE;
        VkDeviceSize size = 0;
        Pointer mapped = nullptr;
    };
}