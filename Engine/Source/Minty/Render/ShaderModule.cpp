#include "pch.h"
#include "ShaderModule.h"
#ifdef MINTY_VULKAN
#include "Platform/Vulkan/Vulkan_ShaderModule.h"
#endif // MINTY_VULKAN

using namespace Minty;

Shared<ShaderModule> Minty::ShaderModule::create(ShaderModuleInfo const& info)
{
#ifdef MINTY_VULKAN
	return Shared<Vulkan_ShaderModule>(info);
#else
    return Shared<ShaderModule>();
#endif // MINTY_VULKAN
}
