#include "pch.h"
#include "Vulkan_ShaderModule.h"
#include "Platform/Vulkan/Vulkan_RenderManager.h"
#include "Platform/Vulkan/Vulkan_Renderer.h"

using namespace Minty;

Minty::Vulkan_ShaderModule::Vulkan_ShaderModule(ShaderModuleInfo const& info)
	: ShaderModule(info)
	, m_shaderModule(VK_NULL_HANDLE)
{
	m_shaderModule = Vulkan_Renderer::create_shader_module(Vulkan_RenderManager::get_singleton().get_device(), info.data, info.size);
}

Minty::Vulkan_ShaderModule::~Vulkan_ShaderModule()
{
	Vulkan_Renderer::destroy_shader_module(Vulkan_RenderManager::get_singleton().get_device(), m_shaderModule);
}
