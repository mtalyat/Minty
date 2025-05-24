#include "pch.h"
#include "Vulkan_ShaderModule.h"
#include "Platform/Vulkan/Vulkan_RenderManager.h"
#include "Platform/Vulkan/Vulkan_Renderer.h"

using namespace Minty;

Minty::Vulkan_ShaderModule::Vulkan_ShaderModule(ShaderModuleBuilder const& builder)
	: ShaderModule(builder)
	, m_shaderModule(VK_NULL_HANDLE)
{
	m_shaderModule = Vulkan_Renderer::create_shader_module(Vulkan_RenderManager::get_singleton().get_device(), builder.data, builder.size);
}

Minty::Vulkan_ShaderModule::~Vulkan_ShaderModule()
{
	Vulkan_Renderer::destroy_shader_module(Vulkan_RenderManager::get_singleton().get_device(), m_shaderModule);
}
