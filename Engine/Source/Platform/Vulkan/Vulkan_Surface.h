#pragma once
#include "Minty/Render/Surface.h"
#include "Minty/Library/Vulkan.h"
#include "Minty/Render/Format.h"

namespace Minty
{
	class Vulkan_RenderManager;
	struct Vulkan_QueueFamilyIndices;

	// surface and swapchain
	class Vulkan_Surface
		: public Surface
	{
#pragma region Variables

	private:
		VkSurfaceKHR m_surface;

		VkSwapchainKHR m_swapchain;
		VkExtent2D m_extent;
		Format m_format;
		uint32_t m_index;
		Vector<Ref<Image>> m_images;

#pragma endregion

#pragma region Constructors

	public:
		// special constructor to create the initial surface
		Vulkan_Surface(SurfaceBuilder const& builder, VkSurfaceKHR const surface, Vulkan_RenderManager& renderManager, Vulkan_QueueFamilyIndices const& queueFamilyIndices);

		Vulkan_Surface(SurfaceBuilder const& builder);

		~Vulkan_Surface() override;

#pragma endregion

#pragma region Get Set

	public:
		UInt2 get_size() const override { return UInt2(m_extent.width, m_extent.height); }

		inline VkSurfaceKHR get_surface() const { return m_surface; }
		inline VkSwapchainKHR get_swapchain() const { return m_swapchain; }
		inline VkExtent2D get_extent() const { return m_extent; }
		inline uint32_t& get_current_image_index_ref() { return m_index; }


		Format get_format() const override { return m_format; }
		UInt get_current_image_index() const override { return m_index; }
		Ref<Image> const& get_current_image() const override { return m_images.at(m_index); }
		Vector<Ref<Image>> const& get_images() const override { return m_images; }

#pragma endregion

#pragma region Methods

	private:
		void initialize_swapchain(Format const targetFormat, Vulkan_RenderManager& renderManager, Vulkan_QueueFamilyIndices const& queueFamilyIndices);

		void dispose_swapchain();

	public:
		void refresh() override;

#pragma endregion

	};
}