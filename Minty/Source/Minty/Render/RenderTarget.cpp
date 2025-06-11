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
/// <param name="builder">The arguments.</param>
Minty::RenderTarget::RenderTarget(RenderTargetBuilder const& builder)
	: Asset(builder.id)
	, m_renderPass(builder.renderPass)
	, m_images(builder.images)
{
	MINTY_ASSERT(m_renderPass != nullptr, "RenderTargetBuilder renderPass must not be null.");
	MINTY_ASSERT(!m_images.is_empty(), "RenderTargetBuilder images must not be empty.");

	m_renderPass->register_render_target(this);
}

Minty::RenderTarget::~RenderTarget()
{
	m_renderPass->unregister_render_target(this);
}

Owner<RenderTarget> Minty::RenderTarget::create(RenderTargetBuilder const& builder)
{
#ifdef MINTY_VULKAN
	return Owner<Vulkan_RenderTarget>(builder);
#else
	return Owner<RenderTarget>();
#endif // MINTY_VULKAN
}
