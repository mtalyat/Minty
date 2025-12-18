#include "pch.h"
#include "Surface.h"
#include "Minty/Render/SurfaceInfo.h"
#ifdef MINTY_VULKAN
#include "Platform/Vulkan/Vulkan_Surface.h"
#endif // MINTY_VULKAN

using namespace Minty;

Minty::Surface::Surface(SurfaceInfo const &info)
			: Asset(info.id)
		{
		}

Shared<Surface> Minty::Surface::create(SurfaceInfo const& info)
{
#ifdef MINTY_VULKAN
	return Shared<Vulkan_Surface>::create(info);
#else
	return Shared<Surface>();
#endif // MINTY_VULKAN
}