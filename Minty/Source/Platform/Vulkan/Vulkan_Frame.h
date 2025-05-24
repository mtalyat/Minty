#pragma once

namespace Minty
{
	/// <summary>
	/// Holds the data for one frame in the flight.
	/// </summary>
	struct Vulkan_Frame
	{
		VkCommandBuffer commandBuffer = VK_NULL_HANDLE;

		VkSemaphore imageAvailableSemaphore = VK_NULL_HANDLE;
		VkSemaphore renderFinishedSemaphore = VK_NULL_HANDLE;
		VkFence inFlightFence = VK_NULL_HANDLE;
	};
}