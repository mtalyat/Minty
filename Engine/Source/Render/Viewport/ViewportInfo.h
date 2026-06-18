#pragma once

/**
 * @file ViewportInfo.h
 * @brief Header file defining the ViewportInfo struct.
 * @author Mitchell Talyat
 */

#include "Core/Type/Float2.h"
#include "Core/Type/Int2.h"
#include "Core/Type/UInt2.h"

namespace Minty
{
    /**
     * @brief Struct containing metadata about a viewport resource.
     */
    struct ViewportInfo
    {
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