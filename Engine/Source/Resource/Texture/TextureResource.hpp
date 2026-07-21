#pragma once

/**
 * @file TextureInfo.hpp
 * @brief TextureInfo struct definition.
 * This file defines the TextureInfo struct, which contains metadata about a texture resource in the application.
 */

#include "TextureFilter.hpp"
#include "TextureAddressMode.hpp"
#include "Resource/Image/ImageAspect.hpp"
#include "Resource/Type/Handle.hpp"
#include "Core/Serialize/Serializer.hpp"

namespace Minty
{
    struct TextureResource
    {
        ImageResourceHandle imageHandle = INVALID_HANDLE;
        UInt mipLevels = 1;
        TextureFilter filter = TextureFilterEnum::Default;
        TextureAddressMode addressMode = TextureAddressModeEnum::Default;
        ImageAspectFlags aspect = ImageAspectFlagsEnum::Color;
        Bool normalizeCoordinates = true;
    };

    template<>
    struct Serializer<TextureResource>
    {
        static Bool serialize(Writer &writer, TextureResource const &value);
        static Bool deserialize(Reader &reader, TextureResource &value);
    };
}