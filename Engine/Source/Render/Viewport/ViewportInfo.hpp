#pragma once

/**
 * @file ViewportInfo.hpp
 * @brief Header file defining the ViewportInfo struct.
 * @author Mitchell Talyat
 */

#include "Core/Type/Float2.hpp"
#include "Core/Type/Int2.hpp"
#include "Core/Type/UInt2.hpp"

namespace Minty
{
    /**
     * @brief Struct containing metadata about a viewport resource.
     */
    struct ViewportInfo
    {
        /**
         * @brief If true, this viewport will update to match the active surface size on refresh.
         */
        Bool dynamic = false;

        /**
         * @brief The normalized position of the viewport, where (0,0) is the top-left and (1,1) is the bottom-right of the surface.
         */
        Float2 viewPosition = { 0.0f, 0.0f };

        /**
         * @brief The normalized size of the viewport, where (1,1) covers the full surface.
         */
        Float2 viewSize = { 1.0f, 1.0f };

        /**
         * @brief The minimum depth of the viewport.
         */
        Float minDepth = 0.0f;

        /**
         * @brief The maximum depth of the viewport.
         */
        Float maxDepth = 1.0f;

        /**
         * @brief The normalized position of the scissor rectangle.
         */
        Float2 scissorPosition = { 0.0f, 0.0f };

        /**
         * @brief The normalized size of the scissor rectangle. (1,1) covers the full surface.
         */
        Float2 scissorSize = { 1.0f, 1.0f };
    };
}