#include "pch.h"
#include "Texture.h"
#if defined(MINTY_VULKAN)
#include "Platform/Vulkan/Vulkan_Texture.h"
#endif // MINTY_VULKAN

using namespace Minty;

Owner<Texture> Minty::Texture::create(TextureBuilder const& builder)
{
#if defined(MINTY_VULKAN)
	return Owner<Vulkan_Texture>(builder);
#else
    return Owner<Texture>();
#endif // MINTY_VULKAN
}
