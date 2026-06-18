#pragma once

/**
 * @file Vulkan_SwapchainSupportDetails.h
 * @brief Header file defining the Vulkan_SwapchainSupportDetails struct.
 * @author Mitchell Talyat
 */

#include "Library/Vulkan/Vulkan.h"
#include "Core/Data/Vector.h"

namespace Minty
{
	/**
	 * @brief Information about the swapchain.
	 */
	struct Vulkan_SwapchainSupportDetails
	{
		VkSurfaceCapabilitiesKHR capabilities = {};
		Vector<VkSurfaceFormatKHR> formats = {};
		Vector<VkPresentModeKHR> presentModes = {};
	};
}