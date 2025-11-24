#include "pch.h"
#include "Viewport.h"
#ifdef MINTY_VULKAN
#include "Platform/Vulkan/Vulkan_Viewport.h"
#endif // MINTY_VULKAN

using namespace Minty;

Owner<Viewport> Minty::Viewport::create(ViewportBuilder const& builder)
{
#ifdef MINTY_VULKAN
	return Owner<Vulkan_Viewport>(builder);
#else
    return Owner<Viewport>();
#endif // MINTY_VULKAN
}
