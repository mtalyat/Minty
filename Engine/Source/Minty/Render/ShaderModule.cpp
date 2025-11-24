#include "pch.h"
#include "ShaderModule.h"
#ifdef MINTY_VULKAN
#include "Platform/Vulkan/Vulkan_ShaderModule.h"
#endif // MINTY_VULKAN

using namespace Minty;

Owner<ShaderModule> Minty::ShaderModule::create(ShaderModuleBuilder const& builder)
{
#ifdef MINTY_VULKAN
	return Owner<Vulkan_ShaderModule>(builder);
#else
    return Owner<ShaderModule>();
#endif // MINTY_VULKAN
}
