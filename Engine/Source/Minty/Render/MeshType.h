#ifndef MINTY_RENDER_MESHTYPE_H
#define MINTY_RENDER_MESHTYPE_H

/**
 * @file MeshType.h
 * @brief Header file defining the MeshType enum.
 * @author Mitchell Talyat
 */

#include "Minty/Serialization/Parse.h"
#include "Minty/Serialization/ToString.h"

namespace Minty
{
	/**
	 * @brief The type of Mesh.
	 */
	enum class MeshType
	{
		/**
		 * @brief An empty Mesh.
		 */
		Empty,

		/**
		 * @brief A custom Mesh.
		 */
		Custom,

		/**
		 * @brief A square Mesh.
		 */
		Quad,

		/**
		 * @brief A cube Mesh.
		 */
		Cube,
	};

	String to_string(MeshType const obj);
	MeshType parse_to_mesh_type(String const& string);
	Bool parse_try_mesh_type(String const& string, MeshType& value);
	template<>
	inline MeshType parse_to<MeshType>(String const& string) { return parse_to_mesh_type(string); }
	template<>
	inline Bool parse_try<MeshType>(String const& string, MeshType& value) { return parse_try_mesh_type(string, value); }
}

#endif // MINTY_RENDER_MESHTYPE_H