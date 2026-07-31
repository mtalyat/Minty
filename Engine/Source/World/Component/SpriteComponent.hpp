#pragma once

#include "Render/Sprite/Sprite.hpp"
#include "Render/Type/Handle.hpp"
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
         * @brief The material to use for rendering the sprite.
         * @note If INVALID_HANDLE, the default sprite material will be used.
         */
        MaterialHandle materialHandle = INVALID_HANDLE;

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