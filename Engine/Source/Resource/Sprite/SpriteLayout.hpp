#pragma once

#include "Core/Type/Int2.hpp"
#include "Core/Serialize/Serializer.hpp"

namespace Minty
{
    struct SpriteLayout
    {
        /**
         * @brief The offset of the sprite within the texture.
         */
		Int2 offset = {};

        /**
         * @brief The size of the sprite within the texture.
         */
		Int2 size = {};
        
        /**
         * @brief The pivot of the sprite within the texture.
         */
		Int2 pivot = {};
    };

    template<>
    struct Serializer<SpriteLayout>
    {
        static Bool serialize(Writer &writer, SpriteLayout const &value);
        static Bool deserialize(Reader &reader, SpriteLayout &value);
    };
}