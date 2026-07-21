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
         * @brief The position of the viewport in pixels.
         */
        Float2 viewPosition = { 0.0f, 0.0f };

        /**
         * @brief The size of the viewport in pixels.
         */
        Float2 viewSize = { 0.0f, 0.0f };

        /**
         * @brief The minimum depth of the viewport.
         */
        Float minDepth = 0.0f;

        /**
         * @brief The maximum depth of the viewport.
         */
        Float maxDepth = 1.0f;

        /**
         * @brief The position of the scissor rectangle in pixels.
         */
        Int2 scissorPosition = { 0, 0 };

        /**
         * @brief The size of the scissor rectangle in pixels.
         */
        UInt2 scissorSize = { 0, 0 };
    };
}