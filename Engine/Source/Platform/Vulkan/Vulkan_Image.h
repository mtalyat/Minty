#pragma once
#include "Minty/Library/Vulkan.h"
#include "Minty/Render/Image.h"

namespace Minty
{
	class Vulkan_Image
		: public Image
	{
#pragma region Variables

	private:
		VkImage m_image;
		VkDeviceMemory m_memory;
		VkImageView m_view;
		VkImageLayout m_layout;

		// if owner, dispose of resources on destruction
		Bool m_owner;

#pragma endregion

#pragma region Constructors

	public:
		Vulkan_Image(ImageInfo const& info);

		Vulkan_Image(ImageInfo const& info, VkImage const image);

		Vulkan_Image(ImageInfo const& info, VkImage const image, VkDeviceMemory const memory, VkImageView const imageView);

		~Vulkan_Image();

#pragma endregion

#pragma region Accessors

	public:
		Any get_native() const override { return m_image; }

		void set_pixels(AnyConst const data, Size const size) override;

		void get_pixels(Any const outData, Size const size) const override;

		VkImage get_image() const { return m_image; }

		VkDeviceMemory get_memory() const { return m_memory; }

		VkImageView get_view() const { return m_view; }

		VkImageLayout get_layout() const { return m_layout; }

#pragma endregion

#pragma region Methods

	private:
		void initialize();

		void dispose();

		// returns true if layout is a visible layout (image is used for rendering)
		Bool is_visible() const;

	public:
		void transition_layout(VkCommandBuffer const commandBuffer, VkImageLayout const newLayout);

#pragma endregion
	};
}