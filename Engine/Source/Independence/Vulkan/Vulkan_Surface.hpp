#pragma once

/**
 * @file Vulkan_Surface.h
 * @brief Header file defining the Vulkan_Surface class.
 * @author Mitchell Talyat
 */

#include "Library/Vulkan/Vulkan.hpp"
#include "Core/Data/Vector.hpp"
#include "Core/Type/Handle.hpp"
#include "Render/Type/Handle.hpp"
#include "Window/Type/Handle.hpp"

namespace Minty
{
	class ImageResource;

	struct Vulkan_SurfaceData
	{
		WindowHandle window;
		VkSurfaceKHR surface;
		VkSwapchainKHR swapchain;
		VkExtent2D extent;
		VkFormat format;
		uint32_t index;
		Vector<TextureHandle> images;
	};
}