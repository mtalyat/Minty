#include "pch.h"
#include "ShaderModule.h"
#include "Minty/Render/ShaderModuleInfo.h"
#ifdef MINTY_VULKAN
#include "Platform/Vulkan/Vulkan_ShaderModule.h"
#endif // MINTY_VULKAN

using namespace Minty;

Minty::ShaderModule::ShaderModule(ShaderModuleInfo const &info)
    : Asset(info.id)
{
    MINTY_ASSERT(info.data != nullptr, ErrorCode::Argument_ExpectedNonNull);
    MINTY_ASSERT(info.size > 0, ErrorCode::Argument_ExpectedAboveZero);
}

Shared<ShaderModule> Minty::ShaderModule::create(ShaderModuleInfo const &info)
{
#ifdef MINTY_VULKAN
    return Shared<Vulkan_ShaderModule>::create(info);
#else
    return Shared<ShaderModule>();
#endif // MINTY_VULKAN
}
