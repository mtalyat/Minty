#include "pch.h"
#include "Vulkan_RenderPass.h"
#include "Platform/Vulkan/Vulkan_Renderer.h"
#include "Platform/Vulkan/Vulkan_RenderManager.h"

using namespace Minty;

Minty::Vulkan_RenderPass::Vulkan_RenderPass(RenderPassInfo const& info)
	: RenderPass(info)
	, m_renderPass(VK_NULL_HANDLE)
{
	Vulkan_RenderManager& renderManager = Vulkan_RenderManager::get_singleton();

	if (info.colorAttachment)
	{
		VkAttachmentDescription colorAttachment = renderManager.create_attachment_description(*info.colorAttachment);
		if (info.depthAttachment)
		{
			VkAttachmentDescription depthAttachment = renderManager.create_attachment_description(*info.depthAttachment);
			m_renderPass = Vulkan_Renderer::create_render_pass(renderManager.get_device(), &colorAttachment, &depthAttachment);
		}
		else
		{
			m_renderPass = Vulkan_Renderer::create_render_pass(renderManager.get_device(), &colorAttachment, nullptr);
		}
	}
	else
	{
		if (info.depthAttachment)
		{
			VkAttachmentDescription depthAttachment = renderManager.create_attachment_description(*info.depthAttachment);
			m_renderPass = Vulkan_Renderer::create_render_pass(renderManager.get_device(), nullptr, &depthAttachment);
		}
		else
		{
			MINTY_ABORT(ErrorCode::Argument_InvalidValue); // "RenderPass must have at least one attachment."
		}
	}
}

Minty::Vulkan_RenderPass::~Vulkan_RenderPass()
{
	Vulkan_RenderManager& renderManager = Vulkan_RenderManager::get_singleton();
	Vulkan_Renderer::destroy_render_pass(renderManager.get_device(), m_renderPass);
}
