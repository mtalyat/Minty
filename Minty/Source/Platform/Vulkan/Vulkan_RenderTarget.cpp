#include "pch.h"
#include "Vulkan_RenderTarget.h"
#include "Minty/Render/Image.h"
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

	// create framebuffers
	
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

void Minty::Vulkan_RenderTarget::reinitialize(RenderTargetBuilder const& builder)
{
	dispose();
	initialize(builder);
}
