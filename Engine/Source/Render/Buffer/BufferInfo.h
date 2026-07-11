#pragma once

/**
 * @file BufferInfo.h
 * @brief Header file defining the BufferInfo struct.
 * @author Mitchell Talyat
 */

#include "BufferUsage.h"
#include "Platform/Type/Primitive.h"
#include "Core/Data/Span.h"

namespace Minty
{
    /**
     * @brief The arguments for a Buffer.
     */
    struct BufferInfo
    {
        /**
         * @brief The data of the Buffer.
         */
        View data = {};

        /**
         * @brief The usage of the Buffer.
         */
        BufferUsageFlags usage = BufferUsageFlagsEnum::Undefined;

        /**
         * @brief When true, optimize for frequent per-frame usage. When false, optimize for infrequent usage.
         */
        Bool frequent = false;
    };
}
