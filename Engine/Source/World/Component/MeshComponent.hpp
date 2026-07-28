#pragma once

/**
 * @file MeshComponent.hpp
 * @brief Header file defining the MeshComponent structure.
 * @author Mitchell Talyat
 */

#include "Render/Type/Handle.hpp"
#include "Core/Serialize/Serializer.hpp"

namespace Minty
{
	/**
	 * @brief Holds the Mesh and Material of an Entity.
	 */
	struct MeshComponent
	{
		/**
		 * @brief The handle to the Mesh.
		 * @note If the Mesh is null, the Material must also be null.
		 */
		GeometryHandle mesh = INVALID_HANDLE;

		/**
		 * @brief The handle to the Material.
		 * @note If the Material is null, the Mesh must also be null.
		 */
		MaterialHandle material = INVALID_HANDLE;
	};

	template<>
	struct Serializer<MeshComponent>
	{
		static void serialize(Writer& writer, MeshComponent const& value);
		static Bool deserialize(Reader& reader, MeshComponent& value);
	};
}
