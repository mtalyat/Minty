#pragma once

/**
 * @file Vulkan_Frame.h
 * @brief Vulkan_Frame struct definition.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.h"
#include "Library/Vulkan/Vulkan.h"

namespace Minty
{
    /**
     * @brief Struct representing a frame in the Vulkan rendering pipeline, containing synchronization primitives and command buffers for rendering operations.
     */
    struct Vulkan_Frame
    {
        VkCommandBuffer commandBuffer = VK_NULL_HANDLE;

		VkSemaphore imageAvailableSemaphore = VK_NULL_HANDLE;
		VkSemaphore renderFinishedSemaphore = VK_NULL_HANDLE;
		VkFence inFlightFence = VK_NULL_HANDLE;
    };
}