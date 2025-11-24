#include "pch.h"
#include "Image.h"
#ifdef MINTY_VULKAN
#include "Platform/Vulkan/Vulkan_Image.h"
#endif // MINTY_VULKAN

using namespace Minty;

Owner<Image> Minty::Image::create(ImageBuilder const& builder)
{
#ifdef MINTY_VULKAN
	return Owner<Vulkan_Image>(builder);
#else
	return Owner<Image>();
#endif // MINTY_VULKAN
}
