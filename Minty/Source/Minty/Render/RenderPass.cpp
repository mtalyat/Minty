#include "pch.h"
#include "RenderPass.h"
#include "Minty/Render/Image.h"
#include "Minty/Render/RenderManager.h"
#include "Minty/Render/Surface.h"
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

void Minty::RenderPass::refresh()
{
	// create a copy of the builder
	RenderTargetBuilder builder{};

	// get a reference to the surface images for any RenderTargets that are surface bound
	RenderManager& renderManager = RenderManager::get_singleton();
	Ref<Surface> surface = renderManager.get_surface();
	MINTY_ASSERT(surface != nullptr, "Failed to refresh RenderPass. No surface found.");
	Vector<Ref<Image>> surfaceImages = surface->get_images();

	Debug::write_line("Render pass image new size: ", to_string(surfaceImages.front()->get_size()));

	// set the render pass to self
	Owner<RenderPass> self = Owner<RenderPass>(this);
	builder.renderPass = self.create_ref();

	for (RenderTarget* target : m_renderTargets)
	{
		// set ID to the target's ID
		builder.id = target->get_id();

		// if surface bound, set the images to the surface images
		builder.surfaceBound = target->is_surface_bound();
		if (builder.surfaceBound)
		{
			// use new surface images
			builder.images = surfaceImages;
		}
		else
		{
			// reuse old images
			builder.images = target->get_images();
		}

		// refresh the target
		target->refresh(builder);
	}

	self.kill();
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
