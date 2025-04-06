#pragma once
#include "Minty/Library/Vulkan.h"
#include "Minty/Render/Format.h"

namespace Minty
{
	class Vulkan_RenderManager;
	struct Vulkan_QueueFamilyIndices;

	class Vulkan_Swapchain
	{
#pragma region Variables

	private:
		VkSwapchainKHR m_swapchain;
		VkExtent2D m_extent;
		Format m_targetFormat;
		uint32_t m_index;
		Vector<VkImage> m_images;

#pragma endregion

#pragma region Constructors

	public:
		Vulkan_Swapchain(Vulkan_RenderManager& renderManager, Format const targetFormat, Vulkan_QueueFamilyIndices const& queueFamilyIndices);

		~Vulkan_Swapchain();

#pragma endregion

#pragma region Get Set

	public:
		inline VkSwapchainKHR get_swapchain() const { return m_swapchain; }
		inline VkExtent2D get_extent() const { return m_extent; }
		inline Format get_target_format() const { return m_targetFormat; }
		inline uint32_t& get_index() { return m_index; }
		inline uint32_t get_index() const { return m_index; }
		inline Vector<VkImage> const& get_images() const { return m_images; }

#pragma endregion

	};
}