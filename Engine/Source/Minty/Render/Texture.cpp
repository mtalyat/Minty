#include "pch.h"
#include "Texture.h"
#include "Minty/Render/TextureInfo.h"
#if defined(MINTY_VULKAN)
#include "Platform/Vulkan/Vulkan_Texture.h"
#endif // MINTY_VULKAN

using namespace Minty;

Minty::Texture::Texture(TextureInfo const &info)
    : Asset(info.id), m_image(info.image)
{
    MINTY_ASSERT(m_image != nullptr, ErrorCode::Argument_ExpectedNonNull);
}

Shared<Texture> Minty::Texture::create(TextureInfo const &info)
{
#if defined(MINTY_VULKAN)
    return Shared<Vulkan_Texture>(info);
#else
    return Shared<Texture>();
#endif // MINTY_VULKAN
}
