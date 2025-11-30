#include "pch.h"
#include "Viewport.h"
#ifdef MINTY_VULKAN
#include "Platform/Vulkan/Vulkan_Viewport.h"
#endif // MINTY_VULKAN

using namespace Minty;

Shared<Viewport> Minty::Viewport::create(ViewportInfo const& info)
{
#ifdef MINTY_VULKAN
	return Shared<Vulkan_Viewport>(info);
#else
    return Shared<Viewport>();
#endif // MINTY_VULKAN
}
