#include "pch.h"
#include "Texture.h"
#if defined(MINTY_VULKAN)
#include "Platform/Vulkan/Vulkan_Texture.h"
#endif // MINTY_VULKAN

using namespace Minty;

Shared<Texture> Minty::Texture::create(TextureInfo const& info)
{
#if defined(MINTY_VULKAN)
	return Shared<Vulkan_Texture>(info);
#else
    return Shared<Texture>();
#endif // MINTY_VULKAN
}
