#include "pch.h"
#include "Vulkan_RenderTarget.h"
#include "Minty/Render/Image.h"
#include "Platform/Vulkan/Vulkan_Image.h"
#include "Platform/Vulkan/Vulkan_Renderer.h"
#include "Platform/Vulkan/Vulkan_RenderManager.h"
#include "Platform/Vulkan/Vulkan_RenderPass.h"
#include "Minty/Render/RenderTargetInfo.h"

using namespace Minty;

Minty::Vulkan_RenderTarget::Vulkan_RenderTarget(RenderTargetInfo const& info)
	: RenderTarget(info)
	, m_framebuffers()
	, m_size()
{
	initialize(info);
}

Minty::Vulkan_RenderTarget::~Vulkan_RenderTarget()
{
	dispose();
}

void Minty::Vulkan_RenderTarget::initialize(RenderTargetInfo const& info)
{
	MINTY_ASSERT(info.images.get_size() > 0, ErrorCode::Argument_ExpectedNonEmpty);

	// get size
	Shared<Image> const& image = info.images.front();
	m_size = image->get_size();

	// get render pass
	Shared<Vulkan_RenderPass> vulkanRenderPass = info.renderPass.cast<Vulkan_RenderPass>();

	// get render manager and resources
	Vulkan_RenderManager& renderManager = Vulkan_RenderManager::get_singleton();
	Shared<Image> const& depthImage = renderManager.get_depth_image();
	Shared<Vulkan_Image> vulkanDepthImage = depthImage.cast<Vulkan_Image>();

	MINTY_ASSERT(!info.renderPass->has_depth_attachment() || depthImage != nullptr, ErrorCode::Argument_InvalidValue); // "Attempting to initialize a RenderTarget when the RenderManager depth image is null."

	// create framebuffers
	m_framebuffers.reserve(info.images.get_size());
	Shared<Vulkan_Image> vulkanImage;
	UInt2 size;
	VkExtent2D extent;
	for (Shared<Image> const& image : info.images)
	{
		vulkanImage = image.cast<Vulkan_Image>();
		size = vulkanImage->get_size();
		extent = { static_cast<uint32_t>(size.x), static_cast<uint32_t>(size.y) };
		VkFramebuffer framebuffer = Vulkan_Renderer::create_framebuffer(
			renderManager.get_device(),
			static_cast<VkRenderPass>(info.renderPass->get_native()),
			extent,
			info.renderPass->has_color_attachment() ? vulkanImage->get_view() : VK_NULL_HANDLE,
			info.renderPass->has_depth_attachment() ? vulkanDepthImage->get_view() : VK_NULL_HANDLE
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

void Minty::Vulkan_RenderTarget::refresh(RenderTargetInfo const& info)
{
	dispose();
	initialize(info);
}
