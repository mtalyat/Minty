#include "pch.h"
#include "Vulkan_RenderManager.h"
#include "Minty/Asset/AssetManager.h"
#include "Minty/Core/Format.h"
#include "Minty/Data/Vector.h"
#include "Minty/Debug/Debug.h"
#include "Platform/Vulkan/Vulkan_Renderer.h"

using namespace Minty;

Minty::Vulkan_RenderManager::Vulkan_RenderManager(RenderManagerBuilder const& builder)
	: RenderManager(builder)
	, m_instance(VK_NULL_HANDLE)
#ifdef MINTY_DEBUG
	, m_debugMessenger(VK_NULL_HANDLE)
#endif // MINTY_DEBUG
	, m_targetSurfaceFormat(builder.targetSurfaceFormat)
	, m_surface(VK_NULL_HANDLE)
	, m_physicalDevice(VK_NULL_HANDLE)
	, m_device(VK_NULL_HANDLE)
	, m_graphicsQueue(VK_NULL_HANDLE)
	, m_presentQueue(VK_NULL_HANDLE)
	, m_commandPool(VK_NULL_HANDLE)
{}

void Minty::Vulkan_RenderManager::initialize_frame(Frame& frame)
{
	frame.commandBuffer = Vulkan_Renderer::create_command_buffer(m_device, m_commandPool);

	frame.imageAvailableSemaphore = Vulkan_Renderer::create_semaphore(m_device);
	frame.renderFinishedSemaphore = Vulkan_Renderer::create_semaphore(m_device);
	frame.inFlightFence = Vulkan_Renderer::create_fence(m_device);
}

void Minty::Vulkan_RenderManager::dispose_frame(Frame& frame)
{
	Vulkan_Renderer::destroy_fence(m_device, frame.inFlightFence);
	Vulkan_Renderer::destroy_semaphore(m_device, frame.renderFinishedSemaphore);
	Vulkan_Renderer::destroy_semaphore(m_device, frame.imageAvailableSemaphore);
	Vulkan_Renderer::destroy_command_buffer(m_device, m_commandPool, frame.commandBuffer);
}

void Minty::Vulkan_RenderManager::create_depth_resources()
{
	AssetManager& assetManager = AssetManager::get_singleton();

	// get depth format
	VkFormat depthFormat = Vulkan_Renderer::find_supported_depth_format(m_physicalDevice);

	// create depth image
	VkExtent2D swapchainExtent = m_swapchain->get_extent();
	ImageBuilder depthImageBuilder{};
	depthImageBuilder.id = UUID::create();
	depthImageBuilder.size = UInt2(swapchainExtent.width, swapchainExtent.height);
	depthImageBuilder.aspect = ImageAspect::Depth;
	depthImageBuilder.format = static_cast<Format>(depthFormat);
	depthImageBuilder.tiling = ImageTiling::Optimal;
	depthImageBuilder.type = ImageType::D2;
	depthImageBuilder.usage = ImageUsage::DepthStencil;
	depthImageBuilder.immutable = false;
	m_depthImage = assetManager.create<Image>(depthImageBuilder);
}

void Minty::Vulkan_RenderManager::destroy_depth_resources()
{
	if (m_depthImage == nullptr)
	{
		return;
	}

	AssetManager& assetManager = AssetManager::get_singleton();
	assetManager.unload(m_depthImage->get_id());
	m_depthImage.release();
}

void Minty::Vulkan_RenderManager::recreate_depth_resources()
{
	destroy_depth_resources();
	create_depth_resources();
}

void Minty::Vulkan_RenderManager::initialize()
{
	// create instance
	m_instance = Vulkan_Renderer::create_instance();

	// set up debugging
#ifdef MINTY_DEBUG
	m_debugMessenger = Vulkan_Renderer::create_debug_messenger(m_instance);
#endif // MINTY_DEBUG

	// create surface
	m_surface = Vulkan_Renderer::create_surface(m_instance, get_window());

	// get physical device
	m_physicalDevice = Vulkan_Renderer::select_physical_device(m_instance, m_surface);

	// get queue families
	Vulkan_QueueFamilyIndices queueFamilyIndices = Vulkan_Renderer::find_queue_families(m_physicalDevice, m_surface);

	// create device
	m_device = Vulkan_Renderer::create_device(m_physicalDevice, queueFamilyIndices);

	// get queues
	m_graphicsQueue = Vulkan_Renderer::get_device_queue(m_device, queueFamilyIndices.graphicsFamily.value());
	m_presentQueue = Vulkan_Renderer::get_device_queue(m_device, queueFamilyIndices.presentFamily.value());

	// create swapchain
	m_swapchain = Owner(new Vulkan_Swapchain(*this, m_targetSurfaceFormat, queueFamilyIndices));
	VkExtent2D swapchainExtent = m_swapchain->get_extent();

	// create default viewport
	UInt2 swapchainSize = UInt2(swapchainExtent.width, swapchainExtent.height);
	ViewportBuilder viewportBuilder{};
	viewportBuilder.id = UUID::create();
	viewportBuilder.viewSize = swapchainSize;
	viewportBuilder.maskSize = swapchainSize;
	m_defaultViewport = Viewport::create(viewportBuilder);

	// create command pool
	m_commandPool = Vulkan_Renderer::create_command_pool(m_device, queueFamilyIndices.graphicsFamily.value());

	// create depth resources
	create_depth_resources();

	// initialize frames
	for (Size i = 0; i < FRAMES_PER_FLIGHT; ++i)
	{
		initialize_frame(m_frames.at(i));
	}

	Manager::initialize();
}

void Minty::Vulkan_RenderManager::dispose()
{
	// sync first
	sync();

	// dispose frames
	for (Size i = 0; i < FRAMES_PER_FLIGHT; ++i)
	{
		dispose_frame(m_frames.at(i));
	}

	// destroy depth resources
	destroy_depth_resources();

	// destroy command pool
	Vulkan_Renderer::destroy_command_pool(m_device, m_commandPool);
	m_commandPool = VK_NULL_HANDLE;

	// destroy swapchain
	m_swapchain.release();

	// destroy device
	Vulkan_Renderer::destroy_device(m_device);
	m_device = VK_NULL_HANDLE;

	// destroy surface
	Vulkan_Renderer::destroy_surface(m_instance, m_surface);
	m_surface = VK_NULL_HANDLE;

	// destroy debug messenger
#ifdef MINTY_DEBUG
	Vulkan_Renderer::destroy_debug_messenger(m_instance, m_debugMessenger);
	m_debugMessenger = VK_NULL_HANDLE;
#endif // MINTY_DEBUG

	// destroy instance
	Vulkan_Renderer::destroy_surface(m_instance, m_surface);
	m_surface = VK_NULL_HANDLE;

	// destroy instance
	Vulkan_Renderer::destroy_instance(m_instance);
	m_instance = VK_NULL_HANDLE;

	Manager::dispose();
}

void Minty::Vulkan_RenderManager::sync()
{
	Vulkan_Renderer::sync_device(m_device);
}

Bool Minty::Vulkan_RenderManager::start_frame()
{
	Frame& frame = get_current_frame();

	// wait for last frame to finish
	Vulkan_Renderer::wait_for_fence(m_device, frame.inFlightFence);
	Vulkan_Renderer::reset_fence(m_device, frame.inFlightFence);

	// get the image in the swapchain to use
	VkResult swapchainResult = Vulkan_Renderer::get_next_swapchain_image_index(m_device, m_swapchain->get_swapchain(), frame.imageAvailableSemaphore, m_swapchain->get_index());

	// check for swapchain rebuilding
	if (swapchainResult == VK_ERROR_OUT_OF_DATE_KHR)
	{
		recreate_swapchain();
		return false;
	}

	// get working command buffer for the current frame
	VkCommandBuffer commandBuffer = frame.commandBuffer;

	// clear buffer
	Vulkan_Renderer::reset_command_buffer(commandBuffer);

	// start new buffer
	Vulkan_Renderer::begin_command_buffer(commandBuffer);

	return true;
}

void Minty::Vulkan_RenderManager::end_frame()
{
	Vulkan_RenderManager& renderManager = Vulkan_RenderManager::get_singleton();

	// get command buffer
	Frame const& frame = renderManager.get_current_frame();
	VkCommandBuffer commandBuffer = frame.commandBuffer;

	// end and submit the command buffer
	Vulkan_Renderer::end_command_buffer(commandBuffer);
	Vulkan_Renderer::submit_command_buffer(commandBuffer, frame, renderManager.get_graphics_queue());

	// present the frame
	VkResult result = Vulkan_Renderer::present_frame(renderManager.get_present_queue(), renderManager.get_swapchain(), frame);

	// check for recreating swapchain
	if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR)
	{
		recreate_swapchain();
	}

	// next frame
	advance_frame();
}

VkCommandBuffer Minty::Vulkan_RenderManager::start_command_buffer_single()
{
	return Vulkan_Renderer::start_command_buffer_single(m_device, m_commandPool);
}

void Minty::Vulkan_RenderManager::finish_command_buffer_single(VkCommandBuffer const commandBuffer, VkQueue const queue)
{
	Vulkan_Renderer::finish_command_buffer_single(m_device, m_commandPool, commandBuffer, queue);
}

void Minty::Vulkan_RenderManager::recreate_swapchain()
{
	Vulkan_QueueFamilyIndices queueFamilyIndices = Vulkan_Renderer::find_queue_families(m_physicalDevice, m_surface);

	// destroy old swapchain and create new one over it
	Format targetFormat = m_swapchain->get_target_format();
	m_swapchain.release();
	m_swapchain = Owner(new Vulkan_Swapchain(*this, targetFormat, queueFamilyIndices));
}
