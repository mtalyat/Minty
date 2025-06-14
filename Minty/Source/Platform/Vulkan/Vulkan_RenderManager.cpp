#include "pch.h"
#include "Vulkan_RenderManager.h"
#include "Minty/Asset/AssetManager.h"
#include "Minty/Core/Format.h"
#include "Minty/Data/Transform.h"
#include "Minty/Data/Vector.h"
#include "Minty/Debug/Debug.h"
#include "Minty/Render/Camera.h"
#include "Minty/Render/RenderPass.h"
#include "Minty/Render/RenderTarget.h"
#include "Platform/Vulkan/Vulkan_Image.h"
#include "Platform/Vulkan/Vulkan_Renderer.h"
#include "Platform/Vulkan/Vulkan_RenderPass.h"
#include "Platform/Vulkan/Vulkan_RenderTarget.h"

using namespace Minty;

Minty::Vulkan_RenderManager::Vulkan_RenderManager(RenderManagerBuilder const& builder)
	: RenderManager(builder)
	, m_instance(VK_NULL_HANDLE)
#ifdef MINTY_DEBUG
	, m_debugMessenger(VK_NULL_HANDLE)
#endif // MINTY_DEBUG
	, m_targetSurfaceFormat(builder.targetSurfaceFormat)
	, m_vulkanSurface(VK_NULL_HANDLE)
	, m_physicalDevice(VK_NULL_HANDLE)
	, m_device(VK_NULL_HANDLE)
	, m_graphicsQueue(VK_NULL_HANDLE)
	, m_presentQueue(VK_NULL_HANDLE)
	, m_commandPool(VK_NULL_HANDLE)
	, m_frames()
	, m_currentFrameIndex(0)
	, m_passesMade(0)
{
}

// gets the current frame's command buffer
VkCommandBuffer Minty::Vulkan_RenderManager::get_current_command_buffer() const
{
	MINTY_ASSERT(get_state() == State::Pass, "Attempting to get the current command buffer while not rendering a pass.");
	return m_frames[m_currentFrameIndex].commandBuffer;
}

void Minty::Vulkan_RenderManager::initialize_frame(Vulkan_Frame& frame)
{
	frame.commandBuffer = Vulkan_Renderer::create_command_buffer(m_device, m_commandPool);

	frame.imageAvailableSemaphore = Vulkan_Renderer::create_semaphore(m_device);
	frame.renderFinishedSemaphore = Vulkan_Renderer::create_semaphore(m_device);
	frame.inFlightFence = Vulkan_Renderer::create_fence(m_device);
}

void Minty::Vulkan_RenderManager::dispose_frame(Vulkan_Frame& frame)
{
	Vulkan_Renderer::destroy_fence(m_device, frame.inFlightFence);
	Vulkan_Renderer::destroy_semaphore(m_device, frame.renderFinishedSemaphore);
	Vulkan_Renderer::destroy_semaphore(m_device, frame.imageAvailableSemaphore);
	Vulkan_Renderer::destroy_command_buffer(m_device, m_commandPool, frame.commandBuffer);
}

void Minty::Vulkan_RenderManager::create_depth_resources()
{
	// get depth format
	VkFormat depthFormat = Vulkan_Renderer::find_supported_depth_format(m_physicalDevice);

	// create depth image
	VkExtent2D swapchainExtent = m_vulkanSurface->get_extent();
	ImageBuilder depthImageBuilder{};
	depthImageBuilder.id = UUID::create();
	depthImageBuilder.size = UInt2(swapchainExtent.width, swapchainExtent.height);
	depthImageBuilder.aspect = ImageAspect::Depth;
	depthImageBuilder.format = static_cast<Format>(depthFormat);
	depthImageBuilder.tiling = ImageTiling::Optimal;
	depthImageBuilder.type = ImageType::D2;
	depthImageBuilder.usage = ImageUsage::DepthStencil;
	depthImageBuilder.immutable = false;
	set_depth_image(Owner<Vulkan_Image>(depthImageBuilder));
}

void Minty::Vulkan_RenderManager::destroy_depth_resources()
{
	set_depth_image(nullptr);
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
	Ref<Window> const& window = get_window();
	VkSurfaceKHR surface = Vulkan_Renderer::create_surface(m_instance, window);

	// get physical device
	m_physicalDevice = Vulkan_Renderer::select_physical_device(m_instance, surface);

	// get queue families
	Vulkan_QueueFamilyIndices queueFamilyIndices = Vulkan_Renderer::find_queue_families(m_physicalDevice, surface);

	// create device
	m_device = Vulkan_Renderer::create_device(m_physicalDevice, queueFamilyIndices);

	// create surface/swapchain object
	SurfaceBuilder surfaceBuilder{};
	surfaceBuilder.id = UUID::create();
	surfaceBuilder.targetFormat = m_targetSurfaceFormat;
	surfaceBuilder.window = window;
	Owner<Surface> vulkanSurface = Owner<Vulkan_Surface>(surfaceBuilder, surface, *this, queueFamilyIndices);
	m_vulkanSurface = vulkanSurface.create_ref();
	set_surface(std::move(vulkanSurface));

	// get queues
	m_graphicsQueue = Vulkan_Renderer::get_device_queue(m_device, queueFamilyIndices.graphicsFamily.value());
	m_presentQueue = Vulkan_Renderer::get_device_queue(m_device, queueFamilyIndices.presentFamily.value());

	// create command pool
	m_commandPool = Vulkan_Renderer::create_command_pool(m_device, queueFamilyIndices.graphicsFamily.value());

	// create depth resources
	create_depth_resources();

	// initialize frames
	for (Size i = 0; i < FRAMES_PER_FLIGHT; ++i)
	{
		initialize_frame(m_frames.at(i));
	}

	RenderManager::initialize();

	// create defaults
	//     viewport
	UInt2 swapchainSize = m_vulkanSurface->get_size();
	ViewportBuilder viewportBuilder{};
	viewportBuilder.id = UUID::create();
	viewportBuilder.viewSize = swapchainSize;
	viewportBuilder.maskSize = swapchainSize;
	set_default_viewport(Viewport::create(viewportBuilder));
}

void Minty::Vulkan_RenderManager::dispose()
{
	// sync first
	sync();

	RenderManager::dispose();

	// remove references
	m_vulkanSurface.release();

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

	// destroy device
	Vulkan_Renderer::destroy_device(m_device);
	m_device = VK_NULL_HANDLE;

	// destroy debug messenger
#ifdef MINTY_DEBUG
	Vulkan_Renderer::destroy_debug_messenger(m_instance, m_debugMessenger);
	m_debugMessenger = VK_NULL_HANDLE;
#endif // MINTY_DEBUG

	// destroy instance
	Vulkan_Renderer::destroy_instance(m_instance);
	m_instance = VK_NULL_HANDLE;
}

void Minty::Vulkan_RenderManager::sync()
{
	Vulkan_Renderer::sync_device(m_device);
}

Bool Minty::Vulkan_RenderManager::start_frame()
{
	if (!RenderManager::start_frame())
	{
		return false;
	}

	Vulkan_Frame& frame = get_current_frame();

	// wait for last frame to finish
	Vulkan_Renderer::wait_for_fence(m_device, frame.inFlightFence);
	Vulkan_Renderer::reset_fence(m_device, frame.inFlightFence);

	// get the image in the swapchain to use
	VkResult swapchainResult = Vulkan_Renderer::get_next_swapchain_image_index(m_device, m_vulkanSurface->get_swapchain(), frame.imageAvailableSemaphore, m_vulkanSurface->get_current_image_index_ref());

	// check for swapchain rebuilding
	if (swapchainResult == VK_ERROR_OUT_OF_DATE_KHR && check_resize_pending())
	{
		abort_frame();

		refresh();
		
		return false;
	}

	// get working command buffer for the current frame
	VkCommandBuffer commandBuffer = frame.commandBuffer;

	// clear buffer
	Vulkan_Renderer::reset_command_buffer(commandBuffer);

	// start new buffer
	Vulkan_Renderer::begin_command_buffer(commandBuffer);

	// reset the render pass count
	m_passesMade = 0;

	return true;
}

void Minty::Vulkan_RenderManager::abort_frame()
{
	// reset current command buffer
	Vulkan_Frame const& frame = get_current_frame();
	VkCommandBuffer commandBuffer = frame.commandBuffer;
	Vulkan_Renderer::reset_command_buffer(commandBuffer);

	RenderManager::abort_frame();
}

void Minty::Vulkan_RenderManager::end_frame()
{
	// if no passes made, abort
	if (!m_passesMade)
	{
		abort_frame();
		return;
	}

	// get command buffer
	Vulkan_Frame const& frame = get_current_frame();
	VkCommandBuffer commandBuffer = frame.commandBuffer;

	// end and submit the command buffer
	Vulkan_Renderer::end_command_buffer(commandBuffer);
	Vulkan_Renderer::submit_command_buffer(commandBuffer, frame, get_graphics_queue());

	VkResult result = Vulkan_Renderer::present_frame(get_present_queue(), *m_vulkanSurface.get(), frame);

	// check for recreating swapchain
	if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR)
	{
		refresh();
	}

	// next frame
	advance_frame();

	RenderManager::end_frame();
}

Bool Minty::Vulkan_RenderManager::start_pass(CameraInfo const& cameraInfo)
{
	// get the camera
	Ref<Camera> const& camera = cameraInfo.camera;

	if (camera == nullptr)
	{
		return false;
	}

	// get render target
	Ref<RenderTarget> renderTarget = camera->get_render_target();

	// skip frame if no target
	if (renderTarget == nullptr)
	{
		return false;
	}

	// start pass
	if (!RenderManager::start_pass(cameraInfo))
	{
		// could not start pass
		return false;
	}

	// get vulkan render target and pass
	Ref<Vulkan_RenderTarget> vulkanRenderTarget = renderTarget.cast_to<Vulkan_RenderTarget>();
	Ref<Vulkan_RenderPass> vulkanRenderPass = vulkanRenderTarget->get_render_pass().cast_to<Vulkan_RenderPass>();

	// get render area
	// remember: Viewport determines where to render within this area, so this area should be the whole screen
	VkRect2D renderArea{};
	renderArea.offset = { 0, 0 };
	renderArea.extent = m_vulkanSurface->get_extent();

	// get clear color
	Color clearColor = cameraInfo.camera->get_color();
	VkClearColorValue clearColorValue{};
	clearColorValue.float32[0] = clearColor.rlf();
	clearColorValue.float32[1] = clearColor.glf();
	clearColorValue.float32[2] = clearColor.blf();
	clearColorValue.float32[3] = clearColor.alf();

	// begin the pass
	Vulkan_Renderer::begin_render_pass(get_current_command_buffer(), vulkanRenderPass->get_render_pass(), vulkanRenderTarget->get_framebuffer(m_vulkanSurface->get_current_image_index_ref()), renderArea, clearColorValue);

	return true;
}

void Minty::Vulkan_RenderManager::end_pass()
{
	Vulkan_Renderer::end_render_pass(get_current_command_buffer());

	RenderManager::end_pass();

	m_passesMade++;
}

VkCommandBuffer Minty::Vulkan_RenderManager::start_command_buffer_single()
{
	return Vulkan_Renderer::start_command_buffer_single(m_device, m_commandPool);
}

void Minty::Vulkan_RenderManager::finish_command_buffer_single(VkCommandBuffer const commandBuffer, VkQueue const queue)
{
	Vulkan_Renderer::finish_command_buffer_single(m_device, m_commandPool, commandBuffer, queue);
}

VkAttachmentDescription Minty::Vulkan_RenderManager::create_attachment_description(RenderAttachment const& attachment) const
{
	VkAttachmentDescription description{};

	// set format based on the attachment type
	switch (attachment.type)
	{
	case RenderAttachment::Type::Color:
		description.format = Vulkan_Renderer::to_vulkan(get_color_attachment_format());
		break;
	case RenderAttachment::Type::Depth:
		description.format = Vulkan_Renderer::to_vulkan(get_depth_attachment_format());
		break;
	default:
		MINTY_ABORT("Invalid attachment type.");
		return {};
	}
	description.samples = VK_SAMPLE_COUNT_1_BIT;
	description.loadOp = Vulkan_Renderer::to_vulkan(attachment.loadOperation);
	description.storeOp = Vulkan_Renderer::to_vulkan(attachment.storeOperation);
	description.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	description.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
	description.initialLayout = Vulkan_Renderer::to_vulkan(attachment.initialLayout);
	description.finalLayout = Vulkan_Renderer::to_vulkan(attachment.finalLayout);
	description.flags = 0;

	return description;
}

void Minty::Vulkan_RenderManager::draw_vertices(UInt const vertexCount) const
{
	Vulkan_Renderer::draw(get_current_command_buffer(), vertexCount);
}

void Minty::Vulkan_RenderManager::draw_indices(UInt const indexCount) const
{
	Vulkan_Renderer::draw_indexed(get_current_command_buffer(), indexCount);
}

void Minty::Vulkan_RenderManager::draw_instances(UInt const instanceCount, UInt const vertexCount) const
{
	Vulkan_Renderer::draw_instanced(get_current_command_buffer(), instanceCount, vertexCount);
}