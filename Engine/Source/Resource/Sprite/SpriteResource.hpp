#pragma once

#include "Resource/Sprite/SpriteLayout.hpp"
#include "Resource/Type/Handle.hpp"
#include "Core/Type/Float2.hpp"
#include "Core/Type/CoordinateMode.hpp"

namespace Minty
{
    struct SpriteResource
    {
        /**
         * @brief The handle to the texture used by the sprite.
         */
        TextureResourceHandle textureResourceHandle = INVALID_HANDLE;

        /**
         * @brief The number of pixels that fit within 1 unit of world space.
         */
		Float pixelsPerUnit = 100.0f;

        /**
         * @brief The layout of the sprite within the texture.
         */
        SpriteLayout layout = {};
    };

    template<>
    struct Serializer<SpriteResource>
    {
        static Bool serialize(Writer &writer, SpriteResource const &value);
        static Bool deserialize(Reader &reader, SpriteResource &value);
    };
}