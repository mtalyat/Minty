#pragma once
#include "Minty/Core/Types.h"
#include "Minty/Data/Vector.h"
#include "Minty/Library/Vulkan.h"

namespace Minty
{
	// information about the swap chain
	struct Vulkan_SwapchainSupportDetails
	{
		VkSurfaceCapabilitiesKHR capabilities = {};
		Vector<VkSurfaceFormatKHR> formats;
		Vector<VkPresentModeKHR> presentModes;
	};
}