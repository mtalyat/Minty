#pragma once

#include "Resource/Sprite/SpriteLayout.hpp"
#include "Core/Type/UInt2.hpp"
#include "Core/Type/Int2.hpp"
#include "Core/Serialize/Serializer.hpp"

namespace Minty
{
    struct SpriteLayoutGroup
    {
        /**
         * @brief The offset of the first sprite within the texture.
         */
        Int2 offset = {};

        /**
         * @brief The number of sprites in the group.
         */
        UInt2 count = {};

        /**
         * @brief The layout of the sprite within the texture.
         */
        SpriteLayout layout = {};
    };

    template<>
    struct Serializer<SpriteLayoutGroup>
    {
        static Bool serialize(Writer &writer, SpriteLayoutGroup const &value);
        static Bool deserialize(Reader &reader, SpriteLayoutGroup &value);
    };
}