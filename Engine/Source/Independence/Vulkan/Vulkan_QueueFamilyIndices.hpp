#pragma once

/**
 * @file Vulkan_QueueFamilyIndices.h
 * @brief Header file defining the Vulkan_QueueFamilyIndices struct.
 * @author Mitchell Talyat
 */

#include "Core/Data/Optional.hpp"

namespace Minty
{
	/**
	 * @brief Struct to hold the indices of the queue families used by the renderer.
	 * The graphics family is used for rendering commands, while the present family is used for presenting images to the surface. These may be the same or different queue families depending on the hardware.
	 */
	struct Vulkan_QueueFamilyIndices
	{
		Optional<UInt32> graphicsFamily;
		Optional<UInt32> presentFamily;

		/**
		 * @brief Checks if all queue family indices have been found.
		 * @return True if all queue family indices are valid, false otherwise.
		 */
		Bool is_complete() const
		{
			return graphicsFamily.is_valid() && presentFamily.is_valid();
		}
	};
}