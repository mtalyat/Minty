#pragma once

/**
 * @file Vulkan_Surface.h
 * @brief Header file defining the Vulkan_Surface class.
 * @author Mitchell Talyat
 */

#include "Library/Vulkan/Vulkan.h"
#include "Core/Data/Vector.h"
#include "Core/Type/Handle.h"
#include "Render/Type/Handle.h"

namespace Minty
{
	class ImageResource;

	struct Vulkan_SurfaceData
	{
		VkSurfaceKHR surface;
		VkSwapchainKHR swapchain;
		VkExtent2D extent;
		VkFormat format;
		uint32_t index;
		Vector<TextureHandle> images;
	};
}