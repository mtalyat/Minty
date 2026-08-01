#pragma once

#include "Render/Type/Handle.hpp"
#include "Platform/Type/Primitive.hpp"
#include "Core/Type/CoordinateMode.hpp"
#include "Core/Type/Int2.hpp"

namespace Minty
{
    struct SpriteInfo
    {
        /**
         * @brief The handle to the texture used by the sprite.
         */
        TextureHandle textureHandle = INVALID_HANDLE;

        /**
         * @brief The offset of the sprite within the texture.
         */
		Int2 offset = Int2(0, 0);

        /**
         * @brief The size of the sprite within the texture.
         */
		Int2 size = Int2(0, 0);
        
        /**
         * @brief The pivot of the sprite within the texture.
         */
		Int2 pivot = Int2(0, 0);

        /**
         * @brief The number of pixels that fit within 1 unit of world space.
         */
		Float pixelsPerUnit = 100.0f;
    };
}