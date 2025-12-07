#include "pch.h"
#include "RenderPass.h"
#include "Minty/Render/Image.h"
#include "Minty/Render/RenderManager.h"
#include "Minty/Render/Surface.h"
#include "Minty/Render/RenderPassInfo.h"
#include "Minty/Render/RenderTarget.h"
#include "Minty/Render/RenderTargetInfo.h"
#ifdef MINTY_VULKAN
#include "Platform/Vulkan/Vulkan_RenderPass.h"
#endif // MINTY_VULKAN

using namespace Minty;

Minty::RenderPass::RenderPass(RenderPassInfo const& info)
	: Asset(info.id)
	, m_renderTargets()
	, m_colorAttachment(info.colorAttachment != nullptr)
	, m_depthAttachment(info.depthAttachment != nullptr)
{
	// "At least one attachment (color or depth) must be provided to create a RenderPass."
	MINTY_ASSERT(m_colorAttachment || m_depthAttachment, ErrorCode::Argument_InvalidValue);
}

void Minty::RenderPass::refresh()
{
	// create a copy of the info
	RenderTargetInfo info{};

	// get a reference to the surface images for any RenderTargets that are surface bound
	RenderManager& renderManager = RenderManager::get_singleton();
	Shared<Surface> const& surface = renderManager.get_surface();
	MINTY_ASSERT(surface != nullptr, ErrorCode::Render_NoSurface);
	Vector<Shared<Image>> const& surfaceImages = surface->get_images();

	for (RenderTarget* target : m_renderTargets)
	{
		// set ID to the target's ID
		info.id = target->get_id();

		// set RenderPass to target's RenderPass
		info.renderPass = target->get_render_pass();

		// if surface bound, set the images to the surface images
		info.surfaceBound = target->is_surface_bound();
		if (info.surfaceBound)
		{
			// use new surface images
			info.images = surfaceImages;
		}
		else
		{
			// reuse old images
			info.images = target->get_images();
		}

		// refresh the target
		target->refresh(info);
	}
}

void Minty::RenderPass::register_render_target(RenderTarget* const renderTarget)
{
	MINTY_ASSERT(!m_renderTargets.contains(renderTarget), ErrorCode::Argument_KeyAlreadyExists);
	m_renderTargets.add(renderTarget);
}

void Minty::RenderPass::unregister_render_target(RenderTarget* const renderTarget)
{
	MINTY_ASSERT(m_renderTargets.contains(renderTarget), ErrorCode::Argument_KeyNotFound);
	m_renderTargets.remove(renderTarget);
}

Shared<RenderPass> Minty::RenderPass::create(RenderPassInfo const& info)
{
#ifdef MINTY_VULKAN
	return Shared<Vulkan_RenderPass>::create(info);
#else
    return Shared<RenderPass>();
#endif // MINTY_VULKAN
}

Shared<RenderPass> Minty::RenderPass::create()
{
	RenderPassInfo info{};
	return create(info);
}
