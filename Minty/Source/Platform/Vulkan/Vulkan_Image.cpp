#include "pch.h"
#include "Minty/Core/Format.h"
#include "Vulkan_Image.h"
#include "Vulkan_Renderer.h"
#include "Vulkan_RenderManager.h"
#include "Vulkan_Buffer.h"

Minty::Vulkan_Image::Vulkan_Image(ImageBuilder const& builder)
	: Image(builder)
	, m_image(VK_NULL_HANDLE)
	, m_memory(VK_NULL_HANDLE)
	, m_view(VK_NULL_HANDLE)
	, m_layout(VK_IMAGE_LAYOUT_UNDEFINED)
	, m_owner(true)
{
	MINTY_ASSERT((builder.pixelData != nullptr) == (builder.pixelDataSize > 0), "Invalid pixel data for Image.");

	initialize();

	// set the pixel data, if given any
	if (builder.pixelData)
	{
		// set pixels and transition to read only layout
		set_pixels(builder.pixelData, builder.pixelDataSize);
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

void Minty::Vulkan_Image::set_pixels(void const* const data, Size const size)
{
	MINTY_ASSERT(!m_immutable, "Image is not mutable.");
	MINTY_ASSERT(m_owner, "Image is not owned by this object.");
	MINTY_ASSERT(data != nullptr, "Pixel data must not be null.");
	MINTY_ASSERT(size > 0, "Pixel data size must be greater than 0.");

	VkFormat format = Vulkan_Renderer::to_vulkan(m_format);

	// create staging buffer, put data into it
	BufferBuilder bufferBuilder{};
	bufferBuilder.usage = BufferUsage::Transfer;
	bufferBuilder.size = size;
	bufferBuilder.data = data;
	bufferBuilder.frequent = false;
	Vulkan_Buffer stagingBuffer(bufferBuilder);

	// get render manager resources
	Vulkan_RenderManager& renderManager = Vulkan_RenderManager::get_singleton();
	VkQueue graphicsQueue = renderManager.get_graphics_queue();

	// transition image so it can be modified
	VkCommandBuffer commandBuffer = renderManager.start_command_buffer_single();
	transition_layout(commandBuffer, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

	// copy buffer to image
	Vulkan_Renderer::copy_buffer_to_image(commandBuffer, graphicsQueue, stagingBuffer.get_buffer(), m_image, m_size.x, m_size.y);

	// transition image back so it can be used to render
	transition_layout(commandBuffer, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);
	renderManager.finish_command_buffer_single(commandBuffer, graphicsQueue);
}

void Minty::Vulkan_Image::initialize()
{
	Vulkan_RenderManager& renderManager = Vulkan_RenderManager::get_singleton();
	m_image = Vulkan_Renderer::create_image(renderManager.get_device(), m_size.x, m_size.y, Vulkan_Renderer::to_vulkan(m_type), Vulkan_Renderer::to_vulkan(m_format), Vulkan_Renderer::to_vulkan(m_tiling), Vulkan_Renderer::to_vulkan(m_usage) | VK_IMAGE_USAGE_TRANSFER_DST_BIT);
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

void Minty::Vulkan_Image::transition_layout(VkCommandBuffer const commandBuffer, VkImageLayout const newLayout)
{
	Vulkan_Renderer::transition_image_layout(
		commandBuffer, 
		m_image, 
		Vulkan_Renderer::to_vulkan(m_format), 
		m_layout, 
		newLayout);
	m_layout = newLayout;
}
