#ifndef MINTY_RENDER_MESHTYPE_H
#define MINTY_RENDER_MESHTYPE_H

/**
 * @file MeshType.h
 * @brief Header file defining the MeshType enum.
 * @author Mitchell Talyat
 */

#include "Minty/Serialization/Parser.h"

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
	
	template<>
	struct Parser<MeshType>
	{
		static Bool parse(StringView const str, MeshType& value);
		static String to_string(MeshType const& obj);
	};
}

#endif // MINTY_RENDER_MESHTYPE_H