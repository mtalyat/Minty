#include "pch.h"
#include "Vulkan_Image.h"
#include "Vulkan_Renderer.h"
#include "Vulkan_RenderManager.h"

Minty::Vulkan_Image::Vulkan_Image(ImageBuilder const& builder)
	: Image(builder)
	, m_image(VK_NULL_HANDLE)
	, m_memory(VK_NULL_HANDLE)
	, m_view(VK_NULL_HANDLE)
	, m_layout(VK_IMAGE_LAYOUT_UNDEFINED)
	, m_owner(true)
{
	initialize();

	// set the pixel data, if given any
	if (!builder.pixels.is_empty())
	{
		set_pixels(builder.pixels.get_data());
	}
}

Minty::Vulkan_Image::Vulkan_Image(ImageBuilder const& builder, VkImage const image)
	: Image(builder)
	, m_image(image)
	, m_memory(VK_NULL_HANDLE)
	, m_view(VK_NULL_HANDLE)
	, m_layout(VK_IMAGE_LAYOUT_UNDEFINED)
	, m_owner(false)
{
	m_view = Vulkan_Renderer::create_image_view(Vulkan_RenderManager::get_singleton().get_device(), m_image, Vulkan_Renderer::to_vulkan(builder.format), Vulkan_Renderer::to_vulkan(builder.aspect));
}

Minty::Vulkan_Image::Vulkan_Image(ImageBuilder const& builder, VkImage const image, VkDeviceMemory const memory, VkImageView const imageView)
	: Image(builder)
	, m_image(image)
	, m_memory(memory)
	, m_view(imageView)
	, m_layout(VK_IMAGE_LAYOUT_UNDEFINED)
	, m_owner(false)
{
}

Minty::Vulkan_Image::~Vulkan_Image()
{
	dispose();
}

void Minty::Vulkan_Image::set_pixels(Byte const* const data)
{
	MINTY_ASSERT(!m_immutable, "Image is not mutable.");
	MINTY_ASSERT(m_owner, "Image is not owned by this object.");

	VkFormat format = Vulkan_Renderer::to_vulkan(m_format);

	// create staging buffer, put data into it
	
}

void Minty::Vulkan_Image::initialize()
{
	Vulkan_RenderManager& renderManager = Vulkan_RenderManager::get_singleton();
	m_image = Vulkan_Renderer::create_image(renderManager.get_device(), m_size.x, m_size.y, Vulkan_Renderer::to_vulkan(m_type), Vulkan_Renderer::to_vulkan(m_format), Vulkan_Renderer::to_vulkan(m_tiling), Vulkan_Renderer::to_vulkan(m_usage));
	m_memory = Vulkan_Renderer::allocate_image_memory(renderManager.get_device(), renderManager.get_physical_device(), m_image, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);
	Vulkan_Renderer::bind_image_memory(renderManager.get_device(), m_image, m_memory);
	m_view = Vulkan_Renderer::create_image_view(renderManager.get_device(), m_image, Vulkan_Renderer::to_vulkan(m_format), Vulkan_Renderer::to_vulkan(m_aspect));
}

void Minty::Vulkan_Image::dispose()
{
	Vulkan_RenderManager& renderManager = Vulkan_RenderManager::get_singleton();
	if (m_owner && m_image != VK_NULL_HANDLE)
	{
		Vulkan_Renderer::destroy_image(renderManager.get_device(), m_image);
	}
	if (m_memory != VK_NULL_HANDLE)
	{
		Vulkan_Renderer::free_memory(renderManager.get_device(), m_memory);
	}
	if (m_view != VK_NULL_HANDLE)
	{
		Vulkan_Renderer::destroy_image_view(renderManager.get_device(), m_view);
	}
}
