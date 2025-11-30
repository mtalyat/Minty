#include "pch.h"
#include "Surface.h"
#ifdef MINTY_VULKAN
#include "Platform/Vulkan/Vulkan_Surface.h"
#endif // MINTY_VULKAN

using namespace Minty;

Shared<Surface> Minty::Surface::create(SurfaceInfo const& info)
{
#ifdef MINTY_VULKAN
	return Shared<Vulkan_Surface>(info);
#else
	return Shared<Surface>();
#endif // MINTY_VULKAN
}
