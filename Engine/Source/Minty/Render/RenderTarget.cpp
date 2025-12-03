#include "pch.h"
#include "RenderTarget.h"
#include "Minty/Render/RenderPass.h"
#include "Minty/Render/RenderTargetInfo.h"
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
	MINTY_ASSERT(m_renderPass != nullptr, ErrorCode::Argument_ExpectedNonNull);
	MINTY_ASSERT(!m_images.is_empty(), ErrorCode::Argument_ExpectedNonEmpty);

	m_renderPass->register_render_target(this);
}

Minty::RenderTarget::~RenderTarget()
{
	m_renderPass->unregister_render_target(this);
}

Shared<RenderTarget> Minty::RenderTarget::create(RenderTargetInfo const& info)
{
#ifdef MINTY_VULKAN
	return Shared<Vulkan_RenderTarget>::create(info);
#else
	return Shared<RenderTarget>();
#endif // MINTY_VULKAN
}

Shared<RenderTarget> Minty::RenderTarget::create()
{
	RenderTargetInfo info{};
	return create(info);
}
