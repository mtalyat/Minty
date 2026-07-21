#pragma once

/**
 * @file Vulkan_SwapchainSupportDetails.hpp
 * @brief Header file defining the Vulkan_SwapchainSupportDetails struct.
 * @author Mitchell Talyat
 */

#include "Library/Vulkan/Vulkan.hpp"
#include "Core/Data/Vector.hpp"

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