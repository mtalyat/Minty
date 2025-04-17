#include "pch.h"
#include "Surface.h"
#ifdef MINTY_VULKAN
#include "Platform/Vulkan/Vulkan_Surface.h"
#endif // MINTY_VULKAN

using namespace Minty;

Owner<Surface> Minty::Surface::create(SurfaceBuilder const& builder)
{
#ifdef MINTY_VULKAN
	return Owner<Vulkan_Surface>(builder);
#else
	return Owner<Surface>();
#endif // MINTY_VULKAN
}
