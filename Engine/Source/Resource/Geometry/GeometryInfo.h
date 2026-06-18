#pragma once

/**
 * @file GeometryInfo.h
 * @brief Header file defining the GeometryInfo struct.
 * @author Mitchell Talyat
 */

#include "Core/Data/ListContainer.h"

namespace Minty
{
    /**
     * @brief The arguments for a GeometryResource.
     */
    struct GeometryInfo
    {
        /**
         * @brief The vertex data for this Geometry.
         */
        PointerConst vertexData = nullptr;

        /**
         * @brief The size of the vertex data in bytes.
         */
        Size vertexDataSize = 0;

        /**
         * @brief The stride of the vertex data in bytes.
         */
        Size vertexStride = 0;

        /**
         * @brief The index data for this Geometry.
         */
        PointerConst indexData = nullptr;

        /**
         * @brief The size of the index data in bytes.
         */
        Size indexDataSize = 0;

        /**
         * @brief The stride of the index data in bytes.
         */
        Size indexStride = 0;
    };
}