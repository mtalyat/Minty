#include "pch.h"
#include "Image.h"
#ifdef MINTY_VULKAN
#include "Platform/Vulkan/Vulkan_Image.h"
#endif // MINTY_VULKAN

using namespace Minty;

Owner<Image> Minty::Image::create(ImageInfo const& info)
{
#ifdef MINTY_VULKAN
	return Owner<Vulkan_Image>(info);
#else
	return Owner<Image>();
#endif // MINTY_VULKAN
}
