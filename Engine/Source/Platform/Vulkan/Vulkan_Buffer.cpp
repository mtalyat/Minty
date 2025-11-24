#include "pch.h"
#include "Vulkan_Buffer.h"
#include "Platform/Vulkan/Vulkan_Renderer.h"
#include "Platform/Vulkan/Vulkan_RenderManager.h"

using namespace Minty;

Minty::Vulkan_Buffer::Vulkan_Buffer(BufferBuilder const& builder)
	: Buffer(builder)
	, m_buffer(VK_NULL_HANDLE)
	, m_memory(VK_NULL_HANDLE)
	, m_size(static_cast<VkDeviceSize>(builder.size))
	, mp_mappedMemory(nullptr)
{
	MINTY_ASSERT(builder.size > 0, "Attempting to create a buffer with a size of 0.");
	MINTY_ASSERT(builder.usage != BufferUsage::Undefined, "Attempting to create a buffer with an undefined usage.");

	Vulkan_RenderManager& renderManager = Vulkan_RenderManager::get_singleton();

	int extraUsageFlags;
	VkMemoryPropertyFlags memoryPropertyFlags;
	if (is_frequent())
	{
		extraUsageFlags = 0;
		memoryPropertyFlags = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
	}
	else
	{
		extraUsageFlags = VK_BUFFER_USAGE_TRANSFER_DST_BIT;
		memoryPropertyFlags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
	}

	m_buffer = Vulkan_Renderer::create_buffer(renderManager.get_device(), builder.size, Vulkan_Renderer::to_vulkan(builder.usage) | extraUsageFlags);
	m_memory = Vulkan_Renderer::allocate_buffer_memory(renderManager.get_device(), renderManager.get_physical_device(), m_buffer, memoryPropertyFlags);

	// if frequent, map memory indefinitely
	if (is_frequent())
	{
		mp_mappedMemory = Vulkan_Renderer::map_memory(renderManager.get_device(), m_memory, 0, builder.size);
	}

	// if given initial data, set it
	if (builder.data)
	{
		set_data(builder.data);
	}
}

Minty::Vulkan_Buffer::~Vulkan_Buffer()
{
	Vulkan_RenderManager& renderManager = Vulkan_RenderManager::get_singleton();
	if (mp_mappedMemory)
	{
		Vulkan_Renderer::unmap_memory(renderManager.get_device(), m_memory);
	}
	Vulkan_Renderer::destroy_buffer(renderManager.get_device(), m_buffer);
	Vulkan_Renderer::free_memory(renderManager.get_device(), m_memory);
}

void* Minty::Vulkan_Buffer::get_data() const
{
	MINTY_ASSERT(is_frequent(), "Attempting to get data from a non-frequent buffer.");

	return mp_mappedMemory;
}

void Minty::Vulkan_Buffer::set_data(void const* const data)
{
	MINTY_ASSERT(data, "Attempting to set data to nullptr.");

	Vulkan_RenderManager& renderManager = Vulkan_RenderManager::get_singleton();

	if (is_frequent())
	{
		// copy memory to buffer
		memcpy(mp_mappedMemory, data, get_size());
	}
	else
	{
		// create staging buffer
		VkBuffer stagingBuffer = Vulkan_Renderer::create_buffer(renderManager.get_device(), get_size(), VK_BUFFER_USAGE_TRANSFER_SRC_BIT);
		VkDeviceMemory stagingBufferMemory = Vulkan_Renderer::allocate_buffer_memory(renderManager.get_device(), renderManager.get_physical_device(), stagingBuffer, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

		// copy data to staging buffer
		void* mappedMemory = Vulkan_Renderer::map_memory(renderManager.get_device(), stagingBufferMemory, 0, get_size());
		memcpy(mappedMemory, data, get_size());
		Vulkan_Renderer::unmap_memory(renderManager.get_device(), stagingBufferMemory);

		// copy from staging buffer to buffer
		VkCommandBuffer commandBuffer = Vulkan_Renderer::start_command_buffer_single(renderManager.get_device(), renderManager.get_command_pool());
		Vulkan_Renderer::copy_buffer_to_buffer(commandBuffer, renderManager.get_graphics_queue(), stagingBuffer, m_buffer, get_size());
		Vulkan_Renderer::finish_command_buffer_single(renderManager.get_device(), renderManager.get_command_pool(), commandBuffer, renderManager.get_graphics_queue());

		// destroy staging buffer
		Vulkan_Renderer::destroy_buffer(renderManager.get_device(), stagingBuffer);
		Vulkan_Renderer::free_memory(renderManager.get_device(), stagingBufferMemory);
	}
}
