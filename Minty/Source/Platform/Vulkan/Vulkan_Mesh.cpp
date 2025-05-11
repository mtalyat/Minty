#include "pch.h"
#include "Vulkan_Mesh.h"
#include "Minty/Library/Vulkan.h"
#include "Platform/Vulkan/Vulkan_Renderer.h"
#include "Platform/Vulkan/Vulkan_RenderManager.h"

using namespace Minty;

void Minty::Vulkan_Mesh::on_bind() const
{
	Vulkan_RenderManager& renderManager = Vulkan_RenderManager::get_singleton();

	VkCommandBuffer commandBuffer = renderManager.get_current_command_buffer();
	Vulkan_Renderer::bind_vertex_buffer(commandBuffer, static_cast<VkBuffer>(m_vertexBuffer->get_native()), 0);
	Vulkan_Renderer::bind_index_buffer(commandBuffer, static_cast<VkBuffer>(m_indexBuffer->get_native()));
}
