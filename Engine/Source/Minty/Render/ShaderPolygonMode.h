#ifndef MINTY_RENDER_SHADERPOLYGONMODE_H
#define MINTY_RENDER_SHADERPOLYGONMODE_H

/**
 * @file ShaderPolygonMode.h
 * @brief Header file defining the ShaderPolygonMode enum.
 * @author Mitchell Talyat
 */

#include "Minty/Serialization/Parser.h"

namespace Minty
{
	/**
	 * @brief Determines how the polygons are being drawn.
	 */
	enum class ShaderPolygonMode
	{
		/**
		 * @brief Invalid.
		 */
		Undefined = 0,

		/**
		 * @brief Fill the polygon.
		 */
		Fill = 1,

		/**
		 * @brief Draw the outlines of the polygon.
		 */
		Line = 2,

		/**
		 * @brief Draw the points of the polygon.
		 */
		Point = 3,
	};
	
	template<>
	struct Parser<ShaderPolygonMode>
	{
		static Bool parse(StringView const str, ShaderPolygonMode& value);
		static String to_string(ShaderPolygonMode const& obj);
	};
}

#endif // MINTY_RENDER_SHADERPOLYGONMODE_H