#pragma once

/**
 * @file TextureInfo.h
 * @brief TextureInfo struct definition.
 * This file defines the TextureInfo struct, which contains metadata about a texture resource in the application.
 */

#include "TextureFilter.h"
#include "TextureAddressMode.h"
#include "Resource/Image/ImageAspect.h"
#include "Resource/Type/Handle.h"
#include "Core/Serialize/Serializer.h"

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