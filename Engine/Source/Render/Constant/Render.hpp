#pragma once

/**
 * @file Render.h
 * @brief Constant definitions for the Render module.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"

namespace Minty
{
    /**
     * @brief The number of frames that can be processed simultaneously in the rendering pipeline, used for synchronization and resource management.
     */
    constexpr Size FRAMES_PER_FLIGHT = 2;

    /**
     * @brief The minimum value of the stencil buffer.
     */
    constexpr Size STENCIL_MIN = 0;

    /**
     * @brief The maximum value of the stencil buffer.
     */
	constexpr Size STENCIL_MAX = 255;

    constexpr Size MAX_MATERIAL_COUNT = 32; // TODO: this is a temporary limit for the number of materials that can be used in a single pipeline
}