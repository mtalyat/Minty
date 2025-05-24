#include "pch.h"
#include "Vulkan_RenderTarget.h"
#include "Minty/Render/Image.h"
#include "Platform/Vulkan/Vulkan_Image.h"
#include "Platform/Vulkan/Vulkan_Renderer.h"
#include "Platform/Vulkan/Vulkan_RenderManager.h"
#include "Platform/Vulkan/Vulkan_RenderPass.h"

using namespace Minty;

Minty::Vulkan_RenderTarget::Vulkan_RenderTarget(RenderTargetBuilder const& builder)
	: RenderTarget(builder)
	, m_framebuffers()
	, m_size()
{
	initialize(builder);
}

Minty::Vulkan_RenderTarget::~Vulkan_RenderTarget()
{
	dispose();
}

void Minty::Vulkan_RenderTarget::initialize(RenderTargetBuilder const& builder)
{
	MINTY_ASSERT(builder.images.get_size() > 0, "RenderTargetBuilder must have at least one image.");

	// get size
	Ref<Image> const& image = builder.images.front();
	m_size = image->get_size();

	// get render pass
	Ref<Vulkan_RenderPass> vulkanRenderPass = builder.renderPass.cast_to<Vulkan_RenderPass>();

	// get render manager and resources
	Vulkan_RenderManager& renderManager = Vulkan_RenderManager::get_singleton();
	Ref<Image> depthImage = renderManager.get_depth_image();
	Ref<Vulkan_Image> vulkanDepthImage = depthImage.cast_to<Vulkan_Image>();

	MINTY_ASSERT(!builder.renderPass->has_depth_attachment() || depthImage != nullptr, "Attempting to initialize a RenderTarget when the RenderManager depth image is null.");

	// create framebuffers
	m_framebuffers.reserve(builder.images.get_size());
	Ref<Vulkan_Image> vulkanImage;
	UInt2 size;
	VkExtent2D extent;
	for (Ref<Image> const& image : builder.images)
	{
		vulkanImage = image.cast_to<Vulkan_Image>();
		size = vulkanImage->get_size();
		extent = { static_cast<uint32_t>(size.x), static_cast<uint32_t>(size.y) };
		VkFramebuffer framebuffer = Vulkan_Renderer::create_framebuffer(
			renderManager.get_device(),
			static_cast<VkRenderPass>(builder.renderPass->get_native()),
			extent,
			builder.renderPass->has_color_attachment() ? vulkanImage->get_view() : VK_NULL_HANDLE,
			builder.renderPass->has_depth_attachment() ? vulkanDepthImage->get_view() : VK_NULL_HANDLE
		);
		m_framebuffers.add(framebuffer);
	}
}

void Minty::Vulkan_RenderTarget::dispose()
{
	// destroy framebuffers
	Vulkan_RenderManager& renderManager = Vulkan_RenderManager::get_singleton();
	for (auto const& framebuffer : m_framebuffers)
	{
		Vulkan_Renderer::destroy_framebuffer(renderManager.get_device(), framebuffer);
	}
	m_framebuffers.clear();
}

void Minty::Vulkan_RenderTarget::refresh(RenderTargetBuilder const& builder)
{
	dispose();
	initialize(builder);
}
