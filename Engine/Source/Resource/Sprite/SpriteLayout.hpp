#pragma once

#include "Core/Type/Float2.hpp"
#include "Core/Type/CoordinateMode.hpp"
#include "Core/Serialize/Serializer.hpp"

namespace Minty
{
    struct SpriteLayout
    {
        /**
         * @brief The coordinate mode of the sprite layout.
         */
        CoordinateMode coordinateMode = CoordinateModeEnum::Normalized;

        /**
         * @brief The offset of the sprite within the texture.
         */
		Float2 offset = Float2(0.0f, 0.0f);

        /**
         * @brief The size of the sprite within the texture.
         */
		Float2 size = Float2(1.0f, 1.0f);
        
        /**
         * @brief The pivot of the sprite within the texture.
         */
		Float2 pivot = Float2(0.5f, 0.5f);
    };

    template<>
    struct Serializer<SpriteLayout>
    {
        static Bool serialize(Writer &writer, SpriteLayout const &value);
        static Bool deserialize(Reader &reader, SpriteLayout &value);
    };
}