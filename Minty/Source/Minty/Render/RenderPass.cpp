#include "pch.h"
#include "RenderPass.h"
#ifdef MINTY_VULKAN
#include "Platform/Vulkan/Vulkan_RenderPass.h"
#endif // MINTY_VULKAN

using namespace Minty;

Minty::RenderPass::RenderPass(RenderPassBuilder const& builder)
	: Asset(builder.id)
	, m_renderTargets()
	, m_colorAttachment(builder.colorAttachment != nullptr)
	, m_depthAttachment(builder.depthAttachment != nullptr)
{
	MINTY_ASSERT(m_colorAttachment || m_depthAttachment, "RenderPass must have at least one attachment.");
}

void Minty::RenderPass::refresh(RenderTargetBuilder const& builder)
{
	for (RenderTarget* target : m_renderTargets)
	{
		target->refresh(builder);
	}
}

void Minty::RenderPass::register_render_target(RenderTarget* const renderTarget)
{
	MINTY_ASSERT(!m_renderTargets.contains(renderTarget), "RenderPass already contains this RenderTarget.");
	m_renderTargets.add(renderTarget);
}

void Minty::RenderPass::unregister_render_target(RenderTarget* const renderTarget)
{
	MINTY_ASSERT(m_renderTargets.contains(renderTarget), "RenderPass does not contain this RenderTarget.");
	m_renderTargets.remove(renderTarget);
}

Owner<RenderPass> Minty::RenderPass::create(RenderPassBuilder const& builder)
{
#ifdef MINTY_VULKAN
	return Owner<Vulkan_RenderPass>(builder);
#else
    return Owner<RenderPass>();
#endif // MINTY_VULKAN
}
