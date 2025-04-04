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
		Vulkan_Image(ImageBuilder const& builder);

		Vulkan_Image(ImageBuilder const& builder, VkImage const image);

		Vulkan_Image(ImageBuilder const& builder, VkImage const image, VkDeviceMemory const memory, VkImageView const imageView);

		~Vulkan_Image();

#pragma endregion

#pragma region Get Set

	public:
		void* get_native() const override { return m_image; }

		void set_pixels(Byte const* const data) override;

#pragma endregion

#pragma region Methods

	private:
		void initialize();

		void dispose();

#pragma endregion
	};
}