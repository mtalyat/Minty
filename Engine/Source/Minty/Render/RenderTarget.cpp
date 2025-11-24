#include "pch.h"
#include "RenderTarget.h"
#include "Minty/Render/RenderPass.h"
#ifdef MINTY_VULKAN
#include "Platform/Vulkan/Vulkan_RenderTarget.h"
#endif // MINTY_VULKAN

using namespace Minty;

/// <summary>
/// Creates a new RenderTarget.
/// </summary>
/// <param name="info">The arguments.</param>
Minty::RenderTarget::RenderTarget(RenderTargetInfo const& info)
	: Asset(info.id)
	, m_renderPass(info.renderPass)
	, m_images(info.images)
	, m_surfaceBound(info.surfaceBound)
{
	MINTY_ASSERT(m_renderPass != nullptr, "RenderTargetInfo renderPass must not be null.");
	MINTY_ASSERT(!m_images.is_empty(), "RenderTargetInfo images must not be empty.");

	m_renderPass->register_render_target(this);
}

Minty::RenderTarget::~RenderTarget()
{
	m_renderPass->unregister_render_target(this);
}

Owner<RenderTarget> Minty::RenderTarget::create(RenderTargetInfo const& info)
{
#ifdef MINTY_VULKAN
	return Owner<Vulkan_RenderTarget>(info);
#else
	return Owner<RenderTarget>();
#endif // MINTY_VULKAN
}
