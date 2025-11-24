#include "pch.h"
#include "Minty/Core/Format.h"
#include "Vulkan_Image.h"
#include "Vulkan_Renderer.h"
#include "Vulkan_RenderManager.h"
#include "Vulkan_Buffer.h"

using namespace Minty;

Minty::Vulkan_Image::Vulkan_Image(ImageInfo const& info)
	: Image(info)
	, m_image(VK_NULL_HANDLE)
	, m_memory(VK_NULL_HANDLE)
	, m_view(VK_NULL_HANDLE)
	, m_layout(VK_IMAGE_LAYOUT_UNDEFINED)
	, m_owner(true)
{
	MINTY_ASSERT((info.pixelData != nullptr) == (info.pixelDataSize > 0), "Invalid pixel data for Image.");

	// automatically add TransferDst usage if pixel data is given
	if (info.pixelData)
	{
		m_usage = m_usage | ImageUsage::TransferDst;
	}

	initialize();

	// set the pixel data, if given any
	if (info.pixelData)
	{
		// set pixels and transition to read only layout
		set_pixels(info.pixelData, info.pixelDataSize);
	}
}

Minty::Vulkan_Image::Vulkan_Image(ImageInfo const& info, VkImage const image)
	: Image(info)
	, m_image(image)
	, m_memory(VK_NULL_HANDLE)
	, m_view(VK_NULL_HANDLE)
	, m_layout(VK_IMAGE_LAYOUT_UNDEFINED)
	, m_owner(false)
{
	m_view = Vulkan_Renderer::create_image_view(Vulkan_RenderManager::get_singleton().get_device(), m_image, Vulkan_Renderer::to_vulkan(info.format), Vulkan_Renderer::to_vulkan(info.aspect));
}

Minty::Vulkan_Image::Vulkan_Image(ImageInfo const& info, VkImage const image, VkDeviceMemory const memory, VkImageView const imageView)
	: Image(info)
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

static VkImageLayout usage_to_layout(Minty::ImageUsage const usage)
{
	if ((usage & ImageUsage::Sampled) != ImageUsage::Undefined)
	{
		return VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
	}
	else if ((usage & ImageUsage::Color) != ImageUsage::Undefined)
	{
		return VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
	}
	else if ((usage & ImageUsage::DepthStencil) != ImageUsage::Undefined)
	{
		return VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
	}
	else if ((usage & ImageUsage::TransferDst) != ImageUsage::Undefined)
	{
		return VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
	}
	else if ((usage & ImageUsage::TransferSrc) != ImageUsage::Undefined)
	{
		return VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
	}
	else
	{
		return VK_IMAGE_LAYOUT_GENERAL;
	}
}

void Minty::Vulkan_Image::set_pixels(void const* const data, Size const size)
{
	MINTY_ASSERT(!m_immutable, "Image is not mutable.");
	MINTY_ASSERT(m_owner, "Image is not owned by this object.");
	MINTY_ASSERT(data != nullptr, "Pixel data must not be null.");
	MINTY_ASSERT(size > 0, "Pixel data size must be greater than 0.");
	MINTY_ASSERT(m_layout == 0 || (m_usage & ImageUsage::TransferDst) != ImageUsage::Undefined, "Image usage must include TransferDst to set pixels.");

	VkFormat format = Vulkan_Renderer::to_vulkan(m_format);

	// create staging buffer, put data into it
	BufferInfo bufferInfo{};
	bufferInfo.usage = BufferUsage::TransferSrc;
	bufferInfo.size = size;
	bufferInfo.data = data;
	bufferInfo.frequent = true;
	Vulkan_Buffer stagingBuffer(bufferInfo);

	// get render manager resources
	Vulkan_RenderManager& renderManager = Vulkan_RenderManager::get_singleton();
	VkQueue graphicsQueue = renderManager.get_graphics_queue();

	// transition image so it can be modified
	VkCommandBuffer commandBuffer = renderManager.start_command_buffer_single();
	transition_layout(commandBuffer, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

	// copy buffer to image
	Vulkan_Renderer::copy_buffer_to_image(commandBuffer, graphicsQueue, stagingBuffer.get_buffer(), m_image, m_size.x, m_size.y);

	// transition image back so it can be used to render
	transition_layout(commandBuffer, usage_to_layout(m_usage));
	renderManager.finish_command_buffer_single(commandBuffer, graphicsQueue);
}

void Minty::Vulkan_Image::get_pixels(void* const outData, Size const size) const
{
	MINTY_ASSERT(m_owner, "Image is not owned by this object.");
	MINTY_ASSERT(outData != nullptr, "Out data buffer must not be null.");
	MINTY_ASSERT(size > 0, "Pixel data size must be greater than 0.");
	MINTY_ASSERT((m_usage & ImageUsage::TransferSrc) != ImageUsage::Undefined, "Image usage must include TransferSrc to get pixels.");

	// Calculate the expected image size
	Size const imageSize = static_cast<Size>(m_size.x) * m_size.y * format_get_size(m_format);

	// Create staging buffer to receive image data
	BufferInfo bufferInfo{};
	bufferInfo.usage = BufferUsage::TransferDst;
	bufferInfo.size = imageSize;
	bufferInfo.data = nullptr; // No initial data
	bufferInfo.frequent = true;
	Vulkan_Buffer stagingBuffer(bufferInfo);

	// Get render manager resources
	Vulkan_RenderManager& renderManager = Vulkan_RenderManager::get_singleton();
	VkQueue graphicsQueue = renderManager.get_graphics_queue();

	// Store current layout to restore later
	VkImageLayout originalLayout = m_layout;

	// Start command buffer for GPU operations
	VkCommandBuffer commandBuffer = renderManager.start_command_buffer_single();

	// Transition image layout to transfer source optimal
	const_cast<Vulkan_Image*>(this)->transition_layout(commandBuffer, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL);

	// Copy image to staging buffer
	Vulkan_Renderer::copy_image_to_buffer(commandBuffer, graphicsQueue, m_image, stagingBuffer.get_buffer(), m_size.x, m_size.y);

	// Transition image back to original layout
	const_cast<Vulkan_Image*>(this)->transition_layout(commandBuffer, originalLayout);

	// Submit and wait for completion
	renderManager.finish_command_buffer_single(commandBuffer, graphicsQueue);

	// Map staging buffer memory and copy to output
	Size const copyAmount = Math::min(size, imageSize);
	memcpy(outData, stagingBuffer.get_data(), copyAmount);
}

void Minty::Vulkan_Image::initialize()
{
	Vulkan_RenderManager& renderManager = Vulkan_RenderManager::get_singleton();
	m_image = Vulkan_Renderer::create_image(renderManager.get_device(), m_size.x, m_size.y, Vulkan_Renderer::to_vulkan(m_type), Vulkan_Renderer::to_vulkan(m_format), Vulkan_Renderer::to_vulkan(m_tiling), Vulkan_Renderer::to_vulkan(m_usage));
	VkMemoryPropertyFlags memoryPropertyFlags;
	memoryPropertyFlags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
	if ((m_usage & ImageUsage::TransferSrc) != ImageUsage::Undefined)
	{
		// if the image is a transfer source, it should be host visible
		memoryPropertyFlags |= VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
	}
	m_memory = Vulkan_Renderer::allocate_image_memory(renderManager.get_device(), renderManager.get_physical_device(), m_image, memoryPropertyFlags);
	Vulkan_Renderer::bind_image_memory(renderManager.get_device(), m_image, m_memory);
	// only create a view if the image is visible (meaning it is used in rendering)
	if (is_visible())
	{
		m_view = Vulkan_Renderer::create_image_view(renderManager.get_device(), m_image, Vulkan_Renderer::to_vulkan(m_format), Vulkan_Renderer::to_vulkan(m_aspect));
	}
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

Bool Minty::Vulkan_Image::is_visible() const
{
	return (m_usage & ~ImageUsage::TransferDst & ~ImageUsage::TransferSrc) != ImageUsage::Undefined;
}

void Minty::Vulkan_Image::transition_layout(VkCommandBuffer const commandBuffer, VkImageLayout const newLayout)
{
	if (m_layout == newLayout)
	{
		// no transition needed
		return;
	}

	Vulkan_Renderer::transition_image_layout(
		commandBuffer,
		m_image,
		Vulkan_Renderer::to_vulkan(m_format),
		m_layout,
		newLayout);
	m_layout = newLayout;
}
