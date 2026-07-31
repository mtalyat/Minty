#pragma once

#include "Render/Sprite/Sprite.hpp"
#include "Core/Type/Color.hpp"
#include "Core/Type/FlipState.hpp"

namespace Minty
{
    struct SpriteComponent
    {
        /**
         * @brief The sprite to render.
         */
        Sprite sprite = {};

        /**
         * @brief The color of the sprite.
         */
        Color color = Color::white();

        /**
         * @brief The flip state of the sprite.
         */
        FlipState flipState = FlipStateEnumFlags::Default;
    };
}