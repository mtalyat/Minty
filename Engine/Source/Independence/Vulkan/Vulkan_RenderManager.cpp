#include "Vulkan_RenderManager.h"
#include "Vulkan_Convert.h"
#include "Vulkan_Renderer.h"
#include "Vulkan_SwapchainSupportDetails.h"
#include "Vulkan_QueueFamilyIndices.h"
#include "Core/Debug/Debug.h"
#include "Window/Manager/WindowManager.h"
#include "Render/Manager/RenderManagerInfo.h"
#include "Render/Material/MaterialInfo.h"
#include "Render/Surface/SurfaceInfo.h"
#include "Render/Viewport/ViewportInfo.h"
#include "Render/Texture/TextureInfo.h"
#include "Render/Buffer/BufferInfo.h"
#include "Render/Shader/ShaderInfo.h"
#include "Render/Pipeline/PipelineInfo.h"
#include "Render/RenderView/RenderViewInfo.h"
#include "Core/Tool/Copy.h"
#include "Core/Data/Map.h"
#include "Resource/RenderPass/RenderAttachment.h"
#include "Render/RenderPass/RenderPassInfo.h"
#include "Render/RenderTarget/RenderTargetInfo.h"
#include "Render/Camera/Camera.h"

using namespace Minty;

static WindowHandle get_window(WindowManager const &windowManager, WindowHandle const handle)
{
	if (handle != INVALID_HANDLE)
	{
		return handle;
	}
	else
	{
		return windowManager.get_main();
	}
}

static VkImageLayout usage_to_layout(VkImageUsageFlags const usage)
{
	if ((usage & VK_IMAGE_USAGE_SAMPLED_BIT) != 0)
	{
		return VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
	}
	else if ((usage & VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT) != 0)
	{
		return VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
	}
	else if ((usage & VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT) != 0)
	{
		return VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
	}
	else if ((usage & VK_IMAGE_USAGE_TRANSFER_DST_BIT) != 0)
	{
		return VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
	}
	else if ((usage & VK_IMAGE_USAGE_TRANSFER_SRC_BIT) != 0)
	{
		return VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
	}
	else
	{
		return VK_IMAGE_LAYOUT_GENERAL;
	}
}

Minty::Vulkan_RenderManager::Vulkan_RenderManager(RenderManagerInfo const &info)
	: m_instance(Vulkan_Renderer::create_instance()),
#ifdef MINTY_DEBUG
	  m_debugMessenger(Vulkan_Renderer::create_debug_messenger(m_instance)),
#endif
	  m_targetSurfaceFormat(VK_FORMAT_UNDEFINED),
	  m_physicalDevice(VK_NULL_HANDLE),
	  m_device(VK_NULL_HANDLE),
	  m_graphicsQueue(VK_NULL_HANDLE),
	  m_presentQueue(VK_NULL_HANDLE),
	  m_commandPool(VK_NULL_HANDLE),
	  m_frames(),
	  m_currentFrameIndex(0),
	  m_passesMade(0),
	  m_activeRenderView(INVALID_HANDLE)
{
	// create instance
	m_instance = Vulkan_Renderer::create_instance();

	// set up debugging
#ifdef MINTY_DEBUG
	m_debugMessenger = Vulkan_Renderer::create_debug_messenger(m_instance);
#endif // MINTY_DEBUG

	// get the window to use
	WindowManager const &windowManager = WindowManager::get_instance();
	WindowHandle const windowHandle = get_window(windowManager, info.window);
	Pointer const windowNative = windowManager.get_native(windowHandle);

	// create surface
	VkSurfaceKHR surface = Vulkan_Renderer::create_surface(m_instance, windowNative);

	// get physical device
	m_physicalDevice = Vulkan_Renderer::select_physical_device(m_instance, surface);

	// get queue families
	Vulkan_QueueFamilyIndices queueFamilyIndices = Vulkan_Renderer::find_queue_families(m_physicalDevice, surface);

	// create device
	m_device = Vulkan_Renderer::create_device(m_physicalDevice, queueFamilyIndices);

	// create surface/swapchain object
	SurfaceInfo surfaceInfo{};
	surfaceInfo.format = ImageFormatEnum::Default;
	surfaceInfo.window = windowHandle;
	m_surface = create(surfaceInfo);

	// get queues
	m_graphicsQueue = Vulkan_Renderer::get_device_queue(m_device, queueFamilyIndices.graphicsFamily.get_value());
	m_presentQueue = Vulkan_Renderer::get_device_queue(m_device, queueFamilyIndices.presentFamily.get_value());

	// create command pool
	m_commandPool = Vulkan_Renderer::create_command_pool(m_device, queueFamilyIndices.graphicsFamily.get_value());

	// create depth resources
	create_depth_resources();

	// initialize frames
	for (Size i = 0; i < FRAMES_PER_FLIGHT; ++i)
	{
		create_frame(m_frames.at(i));
	}

	// create defaults
	//     viewport
	Vulkan_SurfaceData const &m_vulkanSurface = m_surfaceDataPool.at(m_surface);
	UInt2 const swapchainSize = {m_vulkanSurface.extent.width, m_vulkanSurface.extent.height};
	ViewportInfo viewportInfo{};
	viewportInfo.viewSize = swapchainSize;
	viewportInfo.scissorSize = swapchainSize;
	m_defaultViewport = create(viewportInfo);
}

Minty::Vulkan_RenderManager::~Vulkan_RenderManager()
{
}

TextureHandle Minty::Vulkan_RenderManager::create(TextureInfo const &textureInfo)
{
	// Image data for convenience
	ImageUsageFlags usage = textureInfo.usage;
	UInt2 const imageSize = textureInfo.size;

	// Create the Vulkan data
	Vulkan_TextureData textureData{};
	textureData.format = Converter<ImageFormat, VkFormat>::from_minty(textureInfo.format);
	textureData.size = {imageSize.x, imageSize.y};

	// If there are pixels, make sure they can be stored on the GPU
	usage.value |= ImageUsageFlagsEnum::TransferDst;
	textureData.usage = Converter<ImageUsageFlags, VkImageUsageFlags>::from_minty(usage);

	// Create the Vulkan image
	textureData.image = Vulkan_Renderer::create_image(
		m_device,
		static_cast<uint32_t>(imageSize.x),
		static_cast<uint32_t>(imageSize.y),
		Converter<ImageType, VkImageType>::from_minty(textureInfo.type),
		textureData.format,
		Converter<ImageTiling, VkImageTiling>::from_minty(textureInfo.tiling),
		Converter<ImageUsageFlags, VkImageUsageFlags>::from_minty(usage));

	// Allocate memory for the image
	VkMemoryPropertyFlags memoryPropertyFlags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
	if (usage.has_flag(ImageUsageFlagsEnum::TransferSrc))
	{
		memoryPropertyFlags |= VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
	}
	textureData.memory = Vulkan_Renderer::allocate_image_memory(
		m_device,
		m_physicalDevice,
		textureData.image,
		memoryPropertyFlags);

	// Bind the memory to the image
	Vulkan_Renderer::bind_image_memory(
		m_device,
		textureData.image,
		textureData.memory);

	if (usage.is_visible())
	{
		// Create the view
		textureData.view = Vulkan_Renderer::create_image_view(
			m_device,
			textureData.image,
			textureData.format,
			Converter<ImageAspectFlags, VkImageAspectFlags>::from_minty(textureInfo.aspect));

		// Create the sampler
		VkFilter const filter = Converter<TextureFilter, VkFilter>::from_minty(textureInfo.filter);
		textureData.sampler = Vulkan_Renderer::create_sampler(
			m_device,
			filter,
			filter,
			Converter<TextureAddressMode, VkSamplerAddressMode>::from_minty(textureInfo.addressMode));
	}

	// Add to pool
	TextureHandle const handle = m_textureDataPool.add(std::move(textureData));

	// Set the pixel data if any given
	if (!textureInfo.data.is_empty())
	{
		set_data(handle, textureInfo.data);
	}

	return handle;
}

void Minty::Vulkan_RenderManager::destroy(TextureHandle const handle)
{
	MINTY_ASSERT(m_textureDataPool.contains(handle), ErrorCodeEnum::Argument_KeyNotFound);
	Vulkan_TextureData const &textureData = m_textureDataPool.at(handle);

	// Destroy the sampler
	Vulkan_Renderer::destroy_sampler(m_device, textureData.sampler);

	// Destroy the view
	Vulkan_Renderer::destroy_image_view(m_device, textureData.view);

	// Destroy the image
	Vulkan_Renderer::destroy_image(m_device, textureData.image);

	// Free the memory
	Vulkan_Renderer::free_memory(m_device, textureData.memory);

	// Remove from pool
	m_textureDataPool.remove(handle);
}

Bool Minty::Vulkan_RenderManager::is_valid(TextureHandle const handle) const
{
	return m_textureDataPool.contains(handle);
}

void Minty::Vulkan_RenderManager::set_data(TextureHandle const handle, Span<Byte> const data)
{
	MINTY_ASSERT(!data.is_empty(), ErrorCodeEnum::Argument_ExpectedNonEmpty);

	// Get the texture data
	Vulkan_TextureData const &textureData = m_textureDataPool.at(handle);
	MINTY_ASSERT(textureData.image != VK_NULL_HANDLE, ErrorCodeEnum::Object_InvalidState);
	MINTY_ASSERT(textureData.memory != VK_NULL_HANDLE, ErrorCodeEnum::Object_InvalidState);

	// Create staging buffer with data
	BufferInfo stagingBufferInfo{};
	stagingBufferInfo.data = data;
	stagingBufferInfo.usage = BufferUsageFlagsEnum::TransferSrc;
	stagingBufferInfo.frequent = true;
	BufferHandle const stagingBufferHandle = create(stagingBufferInfo);
	Vulkan_BufferData const &stagingBufferData = m_bufferDataPool.at(stagingBufferHandle);

	// Transition image so it can be modified
	VkCommandBuffer const commandBuffer = Vulkan_Renderer::start_command_buffer_single(m_device, m_commandPool);
	transition_layout(commandBuffer, handle, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

	// Copy buffer to image
	Vulkan_Renderer::copy_buffer_to_image(
		commandBuffer,
		m_graphicsQueue,
		stagingBufferData.buffer,
		textureData.image,
		textureData.size.width,
		textureData.size.height);

	// Transition image back, using the usage to determine the layout
	VkImageLayout const layout = usage_to_layout(textureData.usage);
	transition_layout(commandBuffer, handle, layout);
	Vulkan_Renderer::finish_command_buffer_single(m_device, m_commandPool, commandBuffer, m_graphicsQueue);
}

SurfaceHandle Minty::Vulkan_RenderManager::create(SurfaceInfo const &surfaceInfo)
{
	// Get the window to use
	WindowManager const &windowManager = WindowManager::get_instance();
	WindowHandle const windowHandle = get_window(windowManager, surfaceInfo.window);
	Pointer const windowNative = windowManager.get_native(windowHandle);
	UInt2 const framebufferSize = windowManager.get_framebuffer_size(windowHandle);

	// Create the Vulkan data
	Vulkan_SurfaceData surfaceData{};

	// Create the surface
	surfaceData.surface = Vulkan_Renderer::create_surface(m_instance, windowNative);

	// Get the queue families
	Vulkan_QueueFamilyIndices queueFamilyIndices = Vulkan_Renderer::find_queue_families(
		m_physicalDevice,
		surfaceData.surface);

	// Get swapchain support details
	Vulkan_SwapchainSupportDetails swapchainSupport = Vulkan_Renderer::query_swapchain_support(
		m_physicalDevice,
		surfaceData.surface);

	// Get size of swapchain
	surfaceData.extent = Vulkan_Renderer::get_swapchain_extent(
		swapchainSupport.capabilities,
		framebufferSize);

	// Get the surface format
	VkSurfaceFormatKHR const surfaceFormat = Vulkan_Renderer::select_swap_surface_format(
		swapchainSupport.formats,
		Converter<ImageFormat, VkFormat>::from_minty(surfaceInfo.format));
	surfaceData.format = surfaceFormat.format;

	// Get the presentation mode
	VkPresentModeKHR const presentMode = Vulkan_Renderer::select_swap_present_mode(
		swapchainSupport.presentModes);

	// Create the swapchain
	surfaceData.swapchain = Vulkan_Renderer::create_swapchain(
		m_device,
		surfaceData.surface,
		swapchainSupport,
		queueFamilyIndices,
		surfaceFormat,
		surfaceData.extent,
		presentMode);

	// Get the swapchain images
	Vector<VkImage> swapchainImages = Vulkan_Renderer::get_swapchain_images(
		m_device,
		surfaceData.swapchain);

	// Create a TextureHandle for each swapchain image
	surfaceData.images.reserve(swapchainImages.get_size());
	for (VkImage const &swapchainImage : swapchainImages)
	{
		Vulkan_TextureData textureData{};
		textureData.image = swapchainImage;
		textureData.format = surfaceData.format;
		textureData.size = surfaceData.extent;

		// Create the view
		textureData.view = Vulkan_Renderer::create_image_view(
			m_device,
			textureData.image,
			textureData.format,
			VK_IMAGE_ASPECT_COLOR_BIT);

		// Add to pool and get handle
		TextureHandle const imageHandle = m_textureDataPool.add(std::move(textureData));
		surfaceData.images.add(imageHandle);
	}

	// Add to pool and return handle
	return m_surfaceDataPool.add(std::move(surfaceData));
}

void Minty::Vulkan_RenderManager::destroy(SurfaceHandle const handle)
{
	MINTY_ASSERT(m_surfaceDataPool.contains(handle), ErrorCodeEnum::Argument_KeyNotFound);
	Vulkan_SurfaceData const &surfaceData = m_surfaceDataPool.at(handle);

	// Destroy the swapchain and surface
	Vulkan_Renderer::destroy_swapchain(m_device, surfaceData.swapchain);
	Vulkan_Renderer::destroy_surface(m_instance, surfaceData.surface);

	// Remove from pool
	m_surfaceDataPool.remove(handle);
}

Bool Minty::Vulkan_RenderManager::is_valid(SurfaceHandle const handle) const
{
	return m_surfaceDataPool.contains(handle);
}

ViewportHandle Minty::Vulkan_RenderManager::create(ViewportInfo const &viewportInfo)
{
	// Create the Vulkan data
	Vulkan_ViewportData viewportData{};
	viewportData.viewport.x = viewportInfo.viewPosition.x;
	viewportData.viewport.y = viewportInfo.viewPosition.y;
	viewportData.viewport.width = viewportInfo.viewSize.x;
	viewportData.viewport.height = viewportInfo.viewSize.y;
	viewportData.viewport.minDepth = viewportInfo.minDepth;
	viewportData.viewport.maxDepth = viewportInfo.maxDepth;
	viewportData.scissor.offset.x = viewportInfo.scissorPosition.x;
	viewportData.scissor.offset.y = viewportInfo.scissorPosition.y;
	viewportData.scissor.extent.width = viewportInfo.scissorSize.x;
	viewportData.scissor.extent.height = viewportInfo.scissorSize.y;

	// Add to pool and return handle
	return m_viewportDataPool.add(std::move(viewportData));
}

void Minty::Vulkan_RenderManager::destroy(ViewportHandle const handle)
{
	MINTY_ASSERT(m_viewportDataPool.contains(handle), ErrorCodeEnum::Argument_KeyNotFound);
	// Vulkan_ViewportData const &viewportData = m_viewportDataPool.at(handle);

	// Remove from pool
	m_viewportDataPool.remove(handle);
}

Bool Minty::Vulkan_RenderManager::is_valid(ViewportHandle const handle) const
{
	return m_viewportDataPool.contains(handle);
}

BufferHandle Minty::Vulkan_RenderManager::create(BufferInfo const &bufferInfo)
{
	// Buffer data for convenience
	VkBufferUsageFlags usage = Converter<BufferUsageFlags, VkBufferUsageFlags>::from_minty(bufferInfo.usage);
	VkMemoryPropertyFlags memoryPropertyFlags;
	VkDeviceSize size = bufferInfo.data.get_size();

	// Create the Vulkan data
	Vulkan_BufferData bufferData{};

	// If frequent, optimize for GPU access. If not, optimize for GPU transfer.
	if (bufferInfo.frequent)
	{
		memoryPropertyFlags = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
	}
	else
	{
		memoryPropertyFlags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
		usage |= VK_BUFFER_USAGE_TRANSFER_DST_BIT;
	}

	// Create the buffer
	bufferData.buffer = Vulkan_Renderer::create_buffer(
		m_device,
		size,
		usage);

	// Allocate the memory
	bufferData.memory = Vulkan_Renderer::allocate_buffer_memory(
		m_device,
		m_physicalDevice,
		bufferData.buffer,
		memoryPropertyFlags);

	// Bind the memory to the buffer
	Vulkan_Renderer::bind_buffer_memory(
		m_device,
		bufferData.buffer,
		bufferData.memory);

	// If frequent, map the memory so it can be written to directly
	if (bufferInfo.frequent)
	{
		bufferData.mapped = Vulkan_Renderer::map_memory(
			m_device,
			bufferData.memory,
			0,
			size);
	}

	// Add to pool
	BufferHandle const handle = m_bufferDataPool.add(std::move(bufferData));

	// Set the initial data
	set_data(handle, bufferInfo.data);

	return handle;
}

void Minty::Vulkan_RenderManager::destroy(BufferHandle const handle)
{
	// Get the buffer data
	MINTY_ASSERT(m_bufferDataPool.contains(handle), ErrorCodeEnum::Argument_KeyNotFound);
	Vulkan_BufferData const &bufferData = m_bufferDataPool.at(handle);

	// Unmap the memory if it was mapped
	if (bufferData.mapped != nullptr)
	{
		Vulkan_Renderer::unmap_memory(m_device, bufferData.memory);
	}

	// Destroy the buffer
	Vulkan_Renderer::destroy_buffer(m_device, bufferData.buffer);

	// Free the memory
	Vulkan_Renderer::free_memory(m_device, bufferData.memory);

	// Remove from pool
	m_bufferDataPool.remove(handle);
}

Bool Minty::Vulkan_RenderManager::is_valid(BufferHandle const handle) const
{
	return m_bufferDataPool.contains(handle);
}

void Minty::Vulkan_RenderManager::set_data(BufferHandle const handle, Span<Byte> const data)
{
	MINTY_ASSERT(!data.is_empty(), ErrorCodeEnum::Argument_ExpectedNonEmpty);

	// Get the buffer data
	Vulkan_BufferData const &bufferData = m_bufferDataPool.at(handle);
	MINTY_ASSERT(bufferData.buffer != VK_NULL_HANDLE, ErrorCodeEnum::Object_InvalidState);
	MINTY_ASSERT(bufferData.memory != VK_NULL_HANDLE, ErrorCodeEnum::Object_InvalidState);

	// If the memory is mapped, write directly to it
	if (bufferData.mapped != nullptr)
	{
		Tool::copy(data.get_data(), bufferData.mapped, data.get_size());
		return;
	}

	// create staging buffer
	VkBuffer stagingBuffer = Vulkan_Renderer::create_buffer(m_device, bufferData.size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT);
	VkDeviceMemory stagingBufferMemory = Vulkan_Renderer::allocate_buffer_memory(m_device, m_physicalDevice, stagingBuffer, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

	// copy data to staging buffer
	Pointer const mappedMemory = Vulkan_Renderer::map_memory(m_device, stagingBufferMemory, 0, bufferData.size);
	Tool::copy(data.get_data(), mappedMemory, data.get_size());
	Vulkan_Renderer::unmap_memory(m_device, stagingBufferMemory);

	// copy from staging buffer to buffer
	VkCommandBuffer commandBuffer = Vulkan_Renderer::start_command_buffer_single(m_device, m_commandPool);
	Vulkan_Renderer::copy_buffer_to_buffer(commandBuffer, m_graphicsQueue, stagingBuffer, bufferData.buffer, bufferData.size);
	Vulkan_Renderer::finish_command_buffer_single(m_device, m_commandPool, commandBuffer, m_graphicsQueue);

	// destroy staging buffer
	Vulkan_Renderer::destroy_buffer(m_device, stagingBuffer);
	Vulkan_Renderer::free_memory(m_device, stagingBufferMemory);
}

ShaderHandle Minty::Vulkan_RenderManager::create(ShaderInfo const &shaderInfo)
{
	// Create the Vulkan data
	Vulkan_ShaderData shaderData{};
	shaderData.stageFlags = Converter<ShaderStage, VkShaderStageFlags>::from_minty(shaderInfo.stage);
	shaderData.entryPoint = shaderInfo.entryPoint;

	// Create the shader module
	shaderData.module = Vulkan_Renderer::create_shader_module(
		m_device,
		shaderInfo.data.get_data(),
		shaderInfo.data.get_size());

	// Add to pool and return handle
	ShaderHandle const handle = m_shaderDataPool.add(std::move(shaderData));
	return handle;
}

void Minty::Vulkan_RenderManager::destroy(ShaderHandle const handle)
{
	// Get the shader data
	MINTY_ASSERT(m_shaderDataPool.contains(handle), ErrorCodeEnum::Argument_KeyNotFound);
	Vulkan_ShaderData const &shaderData = m_shaderDataPool.at(handle);

	// Destroy the shader module
	Vulkan_Renderer::destroy_shader_module(m_device, shaderData.module);

	// Remove from pool
	m_shaderDataPool.remove(handle);
}

Bool Minty::Vulkan_RenderManager::is_valid(ShaderHandle const handle) const
{
	return m_shaderDataPool.contains(handle);
}

PipelineHandle Minty::Vulkan_RenderManager::create(PipelineInfo const &pipelineInfo)
{
	// create a binding for each descriptor and push constant
	Vector<Vulkan_DescriptorSetLayoutData> descriptorSetLayouts;
	Vector<Vulkan_PushConstantData> pushConstants;

	for (PipelineInput const &input : pipelineInfo.inputs)
	{
		// Ignore if undefined
		if (input.type == PipelineInputTypeEnum::Undefined)
		{
			MINTY_WARNING(ErrorCodeEnum::Argument_InvalidType);
			continue;
		}

		// If a push constant, create a push constant range instead of a descriptor binding, since they are separate in Vulkan
		if (input.type == PipelineInputTypeEnum::PushConstant)
		{
			Vulkan_PushConstantData pushConstantRange{};
			pushConstantRange.stageFlags = Converter<ShaderStage, VkShaderStageFlags>::from_minty(input.stage);
			pushConstantRange.offset = static_cast<uint32_t>(input.offset);
			pushConstantRange.size = static_cast<uint32_t>(input.size);
			pushConstants.add(std::move(pushConstantRange));
			continue;
		}

		// Create descriptor binding data
		VkDescriptorSetLayoutBinding descriptorBinding{};
		descriptorBinding.binding = input.binding;
		descriptorBinding.descriptorType = Converter<PipelineInputType, VkDescriptorType>::from_minty(input.type);
		descriptorBinding.descriptorCount = input.count;
		descriptorBinding.stageFlags = Converter<ShaderStage, VkShaderStageFlags>::from_minty(input.stage);

		// Get the index of the descriptor set layout for this set, or create a new one if it doesn't exist yet
		while (descriptorSetLayouts.get_size() <= input.set)
		{
			Vulkan_DescriptorSetLayoutData layoutData{};
			layoutData.id = descriptorSetLayouts.get_size();
			descriptorSetLayouts.add(std::move(layoutData));
		}

		// Add the descriptor binding to the appropriate descriptor set layout
		Vulkan_DescriptorSetLayoutData &descriptorSetLayout = descriptorSetLayouts.at(input.set);
		descriptorSetLayout.bindings.add(input.name, std::move(descriptorBinding));
	}

	// create descriptor set layouts
	for (Size i = 0; i < descriptorSetLayouts.get_size(); ++i)
	{
		// get the layout data
		Vulkan_DescriptorSetLayoutData &descriptorSetLayout = descriptorSetLayouts.at(i);

		// create vector of bindings for this layout
		Vector<VkDescriptorSetLayoutBinding> descriptorSetLayoutBindings;
		for (auto const &[name, binding] : descriptorSetLayout.bindings)
		{
			descriptorSetLayoutBindings.add(binding);
		}

		// create the layout for this descriptor set
		descriptorSetLayout.layout = Vulkan_Renderer::create_descriptor_set_layout(
			m_device,
			descriptorSetLayoutBindings);

		// create allocator data for this layout, using the counts of each type of descriptor used in the pipeline
		Vector<VkDescriptorPoolSize> poolSizes;
		for (auto const &[name, binding] : descriptorSetLayout.bindings)
		{
			VkDescriptorPoolSize poolSize{};
			poolSize.type = binding.descriptorType;
			poolSize.descriptorCount = binding.descriptorCount * MAX_MATERIAL_COUNT * FRAMES_PER_FLIGHT;
			poolSizes.add(std::move(poolSize));
		}
		Vulkan_DescriptorAllocatorData &allocatorData = descriptorSetLayout.allocatorData;
		allocatorData.descriptorPool = Vulkan_Renderer::create_descriptor_pool(
			m_device,
			poolSizes,
			MAX_MATERIAL_COUNT * FRAMES_PER_FLIGHT);
		allocatorData.poolSize = MAX_MATERIAL_COUNT * FRAMES_PER_FLIGHT;
		allocatorData.poolSize = 0;
	}

	// create push constant ranges from the push constant data
	Vector<VkPushConstantRange> pushConstantRanges;
	for (Vulkan_PushConstantData const &pushConstant : pushConstants)
	{
		VkPushConstantRange pushConstantRange{};
		pushConstantRange.stageFlags = pushConstant.stageFlags;
		pushConstantRange.offset = pushConstant.offset;
		pushConstantRange.size = pushConstant.size;
		pushConstantRanges.add(std::move(pushConstantRange));
	}

	// create the pipeline layout
	Vulkan_PipelineLayoutData pipelineLayout{};
	{
		Vector<VkDescriptorSetLayout> descriptorSetLayoutHandles;
		for (Vulkan_DescriptorSetLayoutData const &descriptorSetLayout : descriptorSetLayouts)
		{
			descriptorSetLayoutHandles.add(descriptorSetLayout.layout);
		}
		pipelineLayout.layout = Vulkan_Renderer::create_pipeline_layout(
			m_device,
			descriptorSetLayoutHandles,
			pushConstantRanges);
	}

	// Add layout to pool
	Vulkan_PipelineLayoutHandle const layoutHandle = m_pipelineLayoutDataPool.add(pipelineLayout);

	// create the shader stages for the pipeline
	Vulkan_ShaderData const &vertexShaderData = m_shaderDataPool.at(pipelineInfo.vertexShader);
	Vulkan_ShaderData const &fragmentShaderData = m_shaderDataPool.at(pipelineInfo.fragmentShader);
	Array<VkPipelineShaderStageCreateInfo, 2> shaderStages;
	VkPipelineShaderStageCreateInfo &vertexShaderStage = shaderStages.at(0);
	vertexShaderStage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	vertexShaderStage.stage = VK_SHADER_STAGE_VERTEX_BIT;
	vertexShaderStage.module = vertexShaderData.module;
	vertexShaderStage.pName = vertexShaderData.entryPoint.get_data();
	VkPipelineShaderStageCreateInfo &fragmentShaderStage = shaderStages.at(1);
	fragmentShaderStage.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	fragmentShaderStage.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
	fragmentShaderStage.module = fragmentShaderData.module;
	fragmentShaderStage.pName = fragmentShaderData.entryPoint.get_data();

	// vertex inputs (bindings and attributes)
	VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
	vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;

	Vector<VkVertexInputBindingDescription> bindingDescriptions;
	Vector<VkVertexInputAttributeDescription> attributeDescriptions;
	bindingDescriptions.resize(pipelineInfo.attributes.get_size(), VkVertexInputBindingDescription{});
	for (Size i = 0; i < pipelineInfo.attributes.get_size(); i++)
	{
		PipelineBinding const &binding = pipelineInfo.attributes.at(i);
		VkVertexInputBindingDescription &vertexInputBinding = bindingDescriptions.at(i);
		vertexInputBinding.binding = static_cast<uint32_t>(i);
		vertexInputBinding.inputRate = Converter<PipelineInputRate, VkVertexInputRate>::from_minty(binding.inputRate);

		uint32_t offset = 0;

		// create each attribute as well
		for (Size j = 0; j < binding.attributes.get_size(); j++)
		{
			PipelineAttribute const &attribute = binding.attributes.at(j);
			VkVertexInputAttributeDescription vertexInputAttribute{};

			// treat matrices as multiple vectors
			// all others have their own format
			switch (attribute.type)
			{
			case TypeEnum::Matrix2:
			case TypeEnum::Matrix3:
				MINTY_NOT_IMPLEMENTED();
			case TypeEnum::Matrix4:
			{
				uint32_t typeSize = static_cast<uint32_t>(sizeof(Float4));
				VkFormat const format = Converter<Type, VkFormat>::from_minty(TypeEnum::Float4);

				for (Size k = 0; k < 4; k++)
				{
					vertexInputAttribute.location = static_cast<uint32_t>(j + k);
					vertexInputAttribute.binding = vertexInputBinding.binding;
					vertexInputAttribute.format = format;
					vertexInputAttribute.offset = offset;

					offset += typeSize;

					attributeDescriptions.add(vertexInputAttribute);
				}

				j += 4;

				break;
			}
			default:
			{
				vertexInputAttribute.location = static_cast<uint32_t>(j);
				vertexInputAttribute.binding = vertexInputBinding.binding;
				vertexInputAttribute.format = Converter<Type, VkFormat>::from_minty(attribute.type);
				vertexInputAttribute.offset = offset;

				offset += static_cast<uint32_t>(attribute.type.get_size());

				attributeDescriptions.add(vertexInputAttribute);
				break;
			}
			}
		}

		// final offset is effectively the stride
		vertexInputBinding.stride = offset;
	}

	vertexInputInfo.vertexBindingDescriptionCount = static_cast<uint32_t>(bindingDescriptions.get_size());
	vertexInputInfo.pVertexBindingDescriptions = bindingDescriptions.get_data();
	vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.get_size());
	vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.get_data();

	// topology
	VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo{};
	inputAssemblyInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	inputAssemblyInfo.topology = Converter<PipelinePrimitiveTopology, VkPrimitiveTopology>::from_minty(pipelineInfo.primitiveTopology);
	inputAssemblyInfo.primitiveRestartEnable = VK_FALSE;

	// viewport and scissor
	ViewportHandle const viewportHandle = pipelineInfo.viewport.is_valid() ? pipelineInfo.viewport : m_defaultViewport;
	Vulkan_ViewportData const &viewportData = m_viewportDataPool.at(viewportHandle);
	VkPipelineViewportStateCreateInfo viewportStateInfo{};
	viewportStateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	viewportStateInfo.viewportCount = 1;
	viewportStateInfo.pViewports = &viewportData.viewport;
	viewportStateInfo.scissorCount = 1;
	viewportStateInfo.pScissors = &viewportData.scissor;

	// rasterizer
	VkPipelineRasterizationStateCreateInfo rasterizerInfo{};
	rasterizerInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	rasterizerInfo.depthClampEnable = VK_FALSE;
	rasterizerInfo.rasterizerDiscardEnable = VK_FALSE;
	rasterizerInfo.polygonMode = Converter<PipelinePolygonMode, VkPolygonMode>::from_minty(pipelineInfo.polygonMode);
	rasterizerInfo.lineWidth = pipelineInfo.lineWidth;
	rasterizerInfo.cullMode = Converter<PipelineCullMode, VkCullModeFlags>::from_minty(pipelineInfo.cullMode);
	rasterizerInfo.frontFace = Converter<PipelineFrontFace, VkFrontFace>::from_minty(pipelineInfo.frontFace);
	rasterizerInfo.depthBiasEnable = VK_FALSE;

	// multisampling (disabled for now)
	VkPipelineMultisampleStateCreateInfo multisamplingInfo{};
	multisamplingInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	multisamplingInfo.sampleShadingEnable = VK_FALSE;
	multisamplingInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

	// depth and stencil testing
	VkPipelineDepthStencilStateCreateInfo depthStencilInfo{};
	depthStencilInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
	if (pipelineInfo.depthMode == PipelineDepthStencilModeEnum::None)
	{
		// disable depth testing
		depthStencilInfo.depthTestEnable = VK_FALSE;
	}
	else
	{
		// enable depth testing
		depthStencilInfo.depthTestEnable = VK_TRUE;
		depthStencilInfo.depthWriteEnable = (pipelineInfo.depthMode == PipelineDepthStencilModeEnum::Write) ? VK_TRUE : VK_FALSE;

		// transparent shaders should not write to depth
		MINTY_ASSERT((pipelineInfo.transparency == true && pipelineInfo.depthMode != PipelineDepthStencilModeEnum::Write) || pipelineInfo.depthMode >= PipelineDepthStencilModeEnum::Write, ErrorCodeEnum::Render_ShaderConfiguration); // "Transparent shaders must have depth write disabled."

		// set depth comparison operation
		depthStencilInfo.depthCompareOp = Converter<Conditional, VkCompareOp>::from_minty(pipelineInfo.depthTestOperation);
		// only keep within a specific range (0 to 1 is default)
		depthStencilInfo.depthBoundsTestEnable = VK_FALSE;
		// operations
		depthStencilInfo.stencilTestEnable = VK_FALSE;
	}

	if (pipelineInfo.stencilMode == PipelineDepthStencilModeEnum::None)
	{
		// disable stencil testing
		depthStencilInfo.stencilTestEnable = VK_FALSE;
	}
	else
	{
		// enable stencil testing
		depthStencilInfo.stencilTestEnable = VK_TRUE;

		VkStencilOpState stencilOpState{};
		stencilOpState.failOp = VK_STENCIL_OP_KEEP;
		stencilOpState.depthFailOp = VK_STENCIL_OP_KEEP;
		stencilOpState.compareMask = 0xFF;
		stencilOpState.writeMask = 0xFF;
		stencilOpState.reference = 0; // set dynamically later

		if (pipelineInfo.stencilMode == PipelineDepthStencilModeEnum::Write)
		{
			stencilOpState.passOp = VK_STENCIL_OP_REPLACE;
			stencilOpState.compareOp = VK_COMPARE_OP_ALWAYS;
		}
		else if (pipelineInfo.stencilMode == PipelineDepthStencilModeEnum::Test)
		{
			stencilOpState.passOp = VK_STENCIL_OP_KEEP;
			stencilOpState.compareOp = Converter<Conditional, VkCompareOp>::from_minty(pipelineInfo.stencilTestOperation);
		}

		depthStencilInfo.front = stencilOpState;
		depthStencilInfo.back = stencilOpState;
	}

	// color blending (transparency)
	VkPipelineColorBlendAttachmentState colorBlendAttachment{};
	if (pipelineInfo.transparency)
	{
		colorBlendAttachment.blendEnable = VK_TRUE;
		colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_SRC_ALPHA;
		colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA;
	}
	else
	{
		colorBlendAttachment.blendEnable = VK_FALSE;
		colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE;
		colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO;
	}
	colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD;
	colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE;
	colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO;
	colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD;

	// disable color writing for stencil-write operations
	if (pipelineInfo.stencilMode == PipelineDepthStencilModeEnum::Write)
	{
		colorBlendAttachment.colorWriteMask = 0;
	}
	else
	{
		colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
	}

	// color blending state
	VkPipelineColorBlendStateCreateInfo colorBlendInfo{};
	colorBlendInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	colorBlendInfo.logicOpEnable = VK_FALSE;
	colorBlendInfo.logicOp = VK_LOGIC_OP_COPY;
	colorBlendInfo.attachmentCount = 1;
	colorBlendInfo.pAttachments = &colorBlendAttachment;
	colorBlendInfo.blendConstants[0] = 0.0f;
	colorBlendInfo.blendConstants[1] = 0.0f;
	colorBlendInfo.blendConstants[2] = 0.0f;
	colorBlendInfo.blendConstants[3] = 0.0f;

	VkGraphicsPipelineCreateInfo pipelineInfoCreate{};
	pipelineInfoCreate.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;

	// stages
	pipelineInfoCreate.stageCount = static_cast<uint32_t>(shaderStages.get_size());
	pipelineInfoCreate.pStages = shaderStages.get_data();

	// configuration inputs
	pipelineInfoCreate.pVertexInputState = &vertexInputInfo;
	pipelineInfoCreate.pInputAssemblyState = &inputAssemblyInfo;
	pipelineInfoCreate.pViewportState = &viewportStateInfo;
	pipelineInfoCreate.pRasterizationState = &rasterizerInfo;
	pipelineInfoCreate.pMultisampleState = &multisamplingInfo;
	pipelineInfoCreate.pDepthStencilState = &depthStencilInfo;
	pipelineInfoCreate.pColorBlendState = &colorBlendInfo;
	pipelineInfoCreate.pDynamicState = nullptr; // TODO: dynamic state for viewport/scissor, maybe others?

	// layout of pipeline
	pipelineInfoCreate.layout = pipelineLayout.layout;

	// render passes
	Vulkan_RenderPassData const &renderPassData = m_renderPassDataPool.at(pipelineInfo.renderPass);
	pipelineInfoCreate.renderPass = renderPassData.renderPass;
	pipelineInfoCreate.subpass = 0;

	// base pipeline (for derivatives, not used for now)
	pipelineInfoCreate.basePipelineHandle = VK_NULL_HANDLE;
	pipelineInfoCreate.basePipelineIndex = -1;

	Vulkan_PipelineData pipelineData{};
	pipelineData.layoutHandle = layoutHandle;
	pipelineData.pipeline = Vulkan_Renderer::create_graphics_pipeline(
		m_device,
		pipelineInfoCreate);

	// Add to pool and return handle
	PipelineHandle const handle = m_pipelineDataPool.add(std::move(pipelineData));
	return handle;
}

void Minty::Vulkan_RenderManager::destroy(PipelineHandle const handle)
{
	MINTY_ASSERT(m_pipelineDataPool.contains(handle), ErrorCodeEnum::Argument_KeyNotFound);
	Vulkan_PipelineData const &pipelineData = m_pipelineDataPool.at(handle);

	// Destroy the pipeline
	Vulkan_Renderer::destroy_pipeline(m_device, pipelineData.pipeline);

	// Remove from pool
	m_pipelineDataPool.remove(handle);
}

Bool Minty::Vulkan_RenderManager::is_valid(PipelineHandle const handle) const
{
	return m_pipelineDataPool.contains(handle);
}

RenderPassHandle Minty::Vulkan_RenderManager::create(RenderPassInfo const &renderPassInfo)
{
	MINTY_CHECK(renderPassInfo.attachments.get_size() > 0, ErrorCodeEnum::Argument_ExpectedNonEmpty);

	// Create the Vulkan data
	Vector<VkAttachmentDescription> colorAttachmentDescriptions;
	Vector<VkAttachmentDescription> depthAttachmentDescriptions;

	for (RenderAttachment const &attachment : renderPassInfo.attachments)
	{
		VkAttachmentDescription description{};
		create_attachment_description(attachment, description);

		if (attachment.aspect == ImageAspectFlagsEnum::Color)
		{
			colorAttachmentDescriptions.add(std::move(description));
		}
		else if (attachment.aspect == ImageAspectFlagsEnum::Depth)
		{
			depthAttachmentDescriptions.add(std::move(description));
		}
		else
		{
			MINTY_NOT_SUPPORTED();
		}
	}

	Vulkan_RenderPassData renderPassData{};
	renderPassData.renderPass = Vulkan_Renderer::create_render_pass(
		m_device,
		colorAttachmentDescriptions,
		depthAttachmentDescriptions);
	renderPassData.renderTarget = renderPassInfo.renderTarget;
	renderPassData.viewport = renderPassInfo.viewport == INVALID_HANDLE ? m_defaultViewport : renderPassInfo.viewport;
	renderPassData.clearDepth = renderPassInfo.clearDepth;
	renderPassData.clearStencil = renderPassInfo.clearStencil;
	Float4 const clearColor = renderPassInfo.clearColor.to_linear_float4();
	renderPassData.clearColor.float32[0] = clearColor.x;
	renderPassData.clearColor.float32[1] = clearColor.y;
	renderPassData.clearColor.float32[2] = clearColor.z;
	renderPassData.clearColor.float32[3] = clearColor.w;

	if (renderPassData.renderTarget != INVALID_HANDLE)
	{
		create_render_pass_framebuffers(renderPassData, renderPassData.renderTarget);
	}

	// Add to pool and return handle
	RenderPassHandle const handle = m_renderPassDataPool.add(std::move(renderPassData));
	return handle;
}

void Minty::Vulkan_RenderManager::destroy(RenderPassHandle const handle)
{
	MINTY_ASSERT(m_renderPassDataPool.contains(handle), ErrorCodeEnum::Argument_KeyNotFound);
	Vulkan_RenderPassData &renderPassData = m_renderPassDataPool.at(handle);

	destroy_render_pass_framebuffers(renderPassData);

	if (renderPassData.renderPass != VK_NULL_HANDLE)
	{
		Vulkan_Renderer::destroy_render_pass(m_device, renderPassData.renderPass);
	}

	m_renderPassDataPool.remove(handle);
}

Bool Minty::Vulkan_RenderManager::is_valid(RenderPassHandle const handle) const
{
	return m_renderPassDataPool.contains(handle);
}

MaterialHandle Minty::Vulkan_RenderManager::create(MaterialInfo const &materialInfo)
{
	// Get the pipeline layout for this material's pipeline
	Vulkan_PipelineData const &pipelineData = m_pipelineDataPool.at(materialInfo.pipeline);
	Vulkan_PipelineLayoutData const &pipelineLayoutData = m_pipelineLayoutDataPool.at(pipelineData.layoutHandle);

	// Create descriptor sets for this material based on the pipeline layout
	Vector<VkDescriptorSet> descriptorSets;
	for (Vulkan_DescriptorSetLayoutData const &descriptorSetLayout : pipelineLayoutData.descriptorSetLayouts)
	{
		Array<VkDescriptorSet, FRAMES_PER_FLIGHT> descriptorSetsForFrames = Vulkan_Renderer::allocate_descriptor_sets_for_frames(
			m_device,
			descriptorSetLayout.allocatorData.descriptorPool,
			descriptorSetLayout.layout);
		for (VkDescriptorSet const &descriptorSet : descriptorSetsForFrames)
		{
			descriptorSets.add(descriptorSet);
		}
	}

	Vulkan_MaterialData materialData{};
	materialData.pipelineHandle = materialInfo.pipeline;
	materialData.descriptorSets = std::move(descriptorSets);

	// Add to pool and return handle
	return m_materialDataPool.add(std::move(materialData));
}

void Minty::Vulkan_RenderManager::destroy(MaterialHandle const handle)
{
	MINTY_ASSERT(m_materialDataPool.contains(handle), ErrorCodeEnum::Argument_KeyNotFound);
	Vulkan_MaterialData const &materialData = m_materialDataPool.at(handle);

	// Destroy each descriptor set for this material
	Vulkan_PipelineData const &pipelineData = m_pipelineDataPool.at(materialData.pipelineHandle);
	Vulkan_PipelineLayoutData const &pipelineLayoutData = m_pipelineLayoutDataPool.at(pipelineData.layoutHandle);
	for (Size i = 0; i < materialData.descriptorSets.get_size(); i++)
	{
		Vulkan_DescriptorSetLayoutData const &descriptorSetLayout = pipelineLayoutData.descriptorSetLayouts.at(i);
		Vulkan_Renderer::free_descriptor_sets(
			m_device,
			descriptorSetLayout.allocatorData.descriptorPool,
			materialData.descriptorSets);
	}

	// Remove from pool
	m_materialDataPool.remove(handle);
}

Bool Minty::Vulkan_RenderManager::is_valid(MaterialHandle const handle) const
{
	return m_materialDataPool.contains(handle);
}

RenderTargetHandle Minty::Vulkan_RenderManager::create(RenderTargetInfo const &renderTargetInfo)
{
	MINTY_CHECK(renderTargetInfo.surface != INVALID_HANDLE || renderTargetInfo.images.get_size() > 0, ErrorCodeEnum::Argument_ExpectedNonEmpty);

	// Create the Vulkan data
	Vulkan_RenderTargetData renderTargetData{};

	Span<TextureHandle> imageHandles;
	if (renderTargetInfo.surface == INVALID_HANDLE)
	{
		MINTY_ASSERT(renderTargetInfo.images.get_size() > 0, ErrorCodeEnum::Argument_ExpectedNonEmpty);

		// If this render target does not have a surface, use the provided images as the render target images
		imageHandles = renderTargetInfo.images;
	}
	else
	{
		MINTY_ASSERT(is_valid(renderTargetInfo.surface), ErrorCodeEnum::Argument_InvalidHandle);

		// If this render target has a surface, use the swapchain images for that surface as the render target images
		Vulkan_SurfaceData const &surfaceData = m_surfaceDataPool.at(renderTargetInfo.surface);
		imageHandles = surfaceData.images;
	}

	renderTargetData.images.reserve(imageHandles.get_size());
	for (TextureHandle const &imageHandle : imageHandles)
	{
		renderTargetData.images.add(imageHandle);
	}

	RenderTargetHandle const handle = m_renderTargetDataPool.add(std::move(renderTargetData));

	if (renderTargetInfo.renderPass != INVALID_HANDLE)
	{
		MINTY_ASSERT(m_renderPassDataPool.contains(renderTargetInfo.renderPass), ErrorCodeEnum::Argument_InvalidHandle);
		Vulkan_RenderPassData &renderPassData = m_renderPassDataPool.at(renderTargetInfo.renderPass);
		destroy_render_pass_framebuffers(renderPassData);
		renderPassData.renderTarget = handle;
		create_render_pass_framebuffers(renderPassData, handle);
	}

	return handle;
}

void Minty::Vulkan_RenderManager::destroy(RenderTargetHandle const handle)
{
	MINTY_ASSERT(m_renderTargetDataPool.contains(handle), ErrorCodeEnum::Argument_KeyNotFound);

	for (RenderPassHandle const &renderPassHandle : m_renderPassDataPool.get_handles())
	{
		Vulkan_RenderPassData &renderPassData = m_renderPassDataPool.at(renderPassHandle);
		if (renderPassData.renderTarget == handle)
		{
			destroy_render_pass_framebuffers(renderPassData);
			renderPassData.renderTarget = INVALID_HANDLE;
		}
	}

	// Remove from pool
	m_renderTargetDataPool.remove(handle);
}

Bool Minty::Vulkan_RenderManager::is_valid(RenderTargetHandle const handle) const
{
	return m_renderTargetDataPool.contains(handle);
}

RenderViewHandle Minty::Vulkan_RenderManager::create(RenderViewInfo const &renderViewInfo, Camera const &camera)
{
	// Create the Vulkan data
	Vulkan_RenderViewData renderViewData{};
	renderViewData.position = renderViewInfo.position;

	// Create the projection matrix based on the camera's perspective or orthographic settings
	switch (camera.perspective)
	{
	case CameraPerspectiveEnum::Perspective:
		renderViewData.projectionMatrix = Math::perspective(
			camera.fov,
			camera.aspectRatio,
			camera.nearPlane,
			camera.farPlane);
		break;
	case CameraPerspectiveEnum::Orthographic:
		renderViewData.projectionMatrix = Math::orthographic(
			camera.size,
			camera.aspectRatio,
			camera.nearPlane,
			camera.farPlane);
		break;
	default:
		MINTY_NOT_IMPLEMENTED(); // "Unsupported camera perspective type."
	}

	// Flip Y axis so Y is up in Vulkan's coordinate system
	renderViewData.projectionMatrix[1][1] *= -1.0f;

	// Add to pool
	RenderViewHandle const handle = m_renderViewDataPool.add(std::move(renderViewData));

	// Create the view matrix based on the camera's position and direction
	update_view(handle, renderViewInfo.position, camera.direction);

	// If the active render view is invalid, set it to this one
	if (m_activeRenderView == INVALID_HANDLE)
	{
		m_activeRenderView = handle;
	}

	// Return the handle
	return handle;
}

void Minty::Vulkan_RenderManager::destroy(RenderViewHandle const handle)
{
	MINTY_ASSERT(m_renderViewDataPool.contains(handle), ErrorCodeEnum::Argument_KeyNotFound);

	m_renderViewDataPool.remove(handle);
}

Bool Minty::Vulkan_RenderManager::is_valid(RenderViewHandle const handle) const
{
	return m_renderViewDataPool.contains(handle);
}

void Minty::Vulkan_RenderManager::update_view(RenderViewHandle const handle, Float3 const &position, Float3 const &direction)
{
	MINTY_ASSERT(m_renderViewDataPool.contains(handle), ErrorCodeEnum::Argument_KeyNotFound);

	// get the render view data
	Vulkan_RenderViewData &renderViewData = m_renderViewDataPool.at(handle);

	// create the view matrix based on the position and direction
	renderViewData.viewMatrix = Math::look_at(position, position + direction, Math::UP);
	renderViewData.viewProjectionMatrix = renderViewData.projectionMatrix * renderViewData.viewMatrix;
}

void Minty::Vulkan_RenderManager::set_view(RenderViewHandle const handle)
{
	MINTY_ASSERT(m_renderViewDataPool.contains(handle), ErrorCodeEnum::Argument_KeyNotFound);

	m_activeRenderView = handle;
}

void Minty::Vulkan_RenderManager::create_depth_resources()
{
	// get depth format
	VkFormat depthFormat = Vulkan_Renderer::find_supported_depth_stencil_format(m_physicalDevice);

	// create depth image
	Vulkan_SurfaceData const &surfaceData = m_surfaceDataPool.at(m_surface);
	TextureInfo depthImageInfo{};
	depthImageInfo.mipLevels = 1;
	depthImageInfo.filter = TextureFilterEnum::Default;
	depthImageInfo.addressMode = TextureAddressModeEnum::Default;
	depthImageInfo.normalizeCoordinates = true;
	depthImageInfo.immutable = false;
	depthImageInfo.usage = ImageUsageFlagsEnum::DepthStencil;
	depthImageInfo.size = UInt2(surfaceData.extent.width, surfaceData.extent.height);
	depthImageInfo.aspect = ImageAspectFlagsEnum::Depth;
	depthImageInfo.format = Converter<ImageFormat, VkFormat>::to_minty(depthFormat);
	depthImageInfo.tiling = ImageTilingEnum::Optimal;
	depthImageInfo.type = ImageTypeEnum::D2;
	depthImageInfo.immutable = false;
	m_depthStencilImage = create(depthImageInfo);
}

void Minty::Vulkan_RenderManager::destroy_depth_resources()
{
	// destroy depth image, if there is one
	if (m_depthStencilImage != INVALID_HANDLE)
	{
		destroy(m_depthStencilImage);
		m_depthStencilImage = INVALID_HANDLE;
	}
}

void Minty::Vulkan_RenderManager::recreate_depth_resources()
{
	destroy_depth_resources();
	create_depth_resources();
}

void Minty::Vulkan_RenderManager::create_frame(Vulkan_Frame &frame)
{
	frame.commandBuffer = Vulkan_Renderer::create_command_buffer(
		m_device,
		m_commandPool);

	frame.imageAvailableSemaphore = Vulkan_Renderer::create_semaphore(m_device);
	frame.renderFinishedSemaphore = Vulkan_Renderer::create_semaphore(m_device);
	frame.inFlightFence = Vulkan_Renderer::create_fence(m_device);
}

void Minty::Vulkan_RenderManager::destroy_frame(Vulkan_Frame &frame)
{
	Vulkan_Renderer::destroy_fence(m_device, frame.inFlightFence);
	Vulkan_Renderer::destroy_semaphore(m_device, frame.imageAvailableSemaphore);
	Vulkan_Renderer::destroy_semaphore(m_device, frame.renderFinishedSemaphore);

	Vulkan_Renderer::destroy_command_buffer(
		m_device,
		m_commandPool,
		frame.commandBuffer);
}

void Minty::Vulkan_RenderManager::create_render_pass_framebuffers(Vulkan_RenderPassData &renderPassData, RenderTargetHandle const renderTargetHandle)
{
	MINTY_ASSERT(renderPassData.renderPass != VK_NULL_HANDLE, ErrorCodeEnum::Object_InvalidState);
	MINTY_ASSERT(m_renderTargetDataPool.contains(renderTargetHandle), ErrorCodeEnum::Argument_InvalidHandle);

	Vulkan_RenderTargetData const &renderTargetData = m_renderTargetDataPool.at(renderTargetHandle);
	renderPassData.framebuffers.reserve(renderTargetData.images.get_size());

	for (TextureHandle const &imageHandle : renderTargetData.images)
	{
		Vulkan_TextureData const &textureData = m_textureDataPool.at(imageHandle);

		VkFramebuffer framebuffer = Vulkan_Renderer::create_framebuffer(
			m_device,
			renderPassData.renderPass,
			textureData.size,
			textureData.view,
			m_depthStencilImage != INVALID_HANDLE ? m_textureDataPool.at(m_depthStencilImage).view : VK_NULL_HANDLE);
		renderPassData.framebuffers.add(std::move(framebuffer));
	}
}

void Minty::Vulkan_RenderManager::destroy_render_pass_framebuffers(Vulkan_RenderPassData &renderPassData)
{
	for (VkFramebuffer const &framebuffer : renderPassData.framebuffers)
	{
		Vulkan_Renderer::destroy_framebuffer(m_device, framebuffer);
	}

	renderPassData.framebuffers.clear();
}

void Minty::Vulkan_RenderManager::create_attachment_description(RenderAttachment const &attachment, VkAttachmentDescription &description)
{
	// set format based on the attachment type

	switch (attachment.aspect)
	{
	case ImageAspectFlagsEnum::Color:
	{
		// Color format should be the same as the surface format
		Vulkan_SurfaceData const &surfaceData = m_surfaceDataPool.at(m_surface);
		description.format = surfaceData.format;
		break;
	}
	case ImageAspectFlagsEnum::Depth:
	{
		// Depth format should be the same as the depth image format
		Vulkan_TextureData const &depthTextureData = m_textureDataPool.at(m_depthStencilImage);
		description.format = depthTextureData.format;
		break;
	}
	default:
		MINTY_NOT_IMPLEMENTED(); // "Unsupported render attachment type."
	}
	description.samples = VK_SAMPLE_COUNT_1_BIT;
	description.loadOp = Converter<LoadOperation, VkAttachmentLoadOp>::from_minty(attachment.loadOperation);
	description.storeOp = Converter<StoreOperation, VkAttachmentStoreOp>::from_minty(attachment.storeOperation);
	description.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	description.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	description.initialLayout = Converter<ImageLayout, VkImageLayout>::from_minty(attachment.initialLayout);
	description.finalLayout = Converter<ImageLayout, VkImageLayout>::from_minty(attachment.finalLayout);
	description.flags = 0;
}

void Minty::Vulkan_RenderManager::transition_layout(VkCommandBuffer const commandBuffer, TextureHandle const handle, VkImageLayout const layout)
{
	// Get the texture data
	Vulkan_TextureData &textureData = m_textureDataPool.at(handle);
	MINTY_ASSERT(textureData.image != VK_NULL_HANDLE, ErrorCodeEnum::Object_InvalidState);

	// If the layout is already the same, do nothing
	if (textureData.layout == layout)
	{
		return;
	}

	// Transition the image to the new layout
	Vulkan_Renderer::transition_image_layout(
		commandBuffer,
		textureData.image,
		textureData.format,
		textureData.layout,
		layout);

	// Update the current layout
	textureData.layout = layout;
}
