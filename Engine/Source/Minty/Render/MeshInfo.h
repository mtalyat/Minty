#ifndef MINTY_RENDER_MESHINFO_H
#define MINTY_RENDER_MESHINFO_H

/**
 * @file MeshInfo.h
 * @brief Header file for the MeshInfo struct.
 */

#include "Minty/Core/Types.h"
#include "Minty/Data/UUID.h"
#include "Minty/Render/MeshType.h"

namespace Minty
{
    /**
     * @struct MeshInfo
     * @brief Structure containing information for creating a Mesh.
     */
	struct MeshInfo
	{
        /**
         * @brief The UUID of the Mesh.
         */
		UUID id = {};

        /**
         * @brief The type of the Mesh.
         */
		MeshType type = MeshType::Empty;

        /**
         * @brief Pointer to the vertex data.
         */
		Any vertexData = nullptr;

        /**
         * @brief The stride of each vertex in bytes.
         */
		Size vertexStride = 0;

        /**
         * @brief The number of vertices.
         */
		Size vertexCount = 0;

        /**
         * @brief Pointer to the index data.
         */
		Any indexData = nullptr;

        /**
         * @brief The stride of each index in bytes.
         */
		Size indexStride = 0;

        /**
         * @brief The number of indices.
         */
		Size indexCount = 0;
	};
}

#endif // MINTY_RENDER_MESHINFO_H