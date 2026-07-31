#pragma once

#include "Resource/Sprite/SpriteLayoutGroup.hpp"
#include "Resource/Type/Handle.hpp"
#include "Core/Data/Vector.hpp"
#include "Core/Serialize/Serializer.hpp"

namespace Minty
{
    struct SpriteAtlasResource
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
         * @brief The groups of sprites within the atlas.
         */
        Vector<SpriteLayoutGroup> spriteGroups = {};
    };

    template<>
    struct Serializer<SpriteAtlasResource>
    {
        static Bool serialize(Writer &writer, SpriteAtlasResource const &value);
        static Bool deserialize(Reader &reader, SpriteAtlasResource &value);
    };
}