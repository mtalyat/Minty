#ifndef MINTY_RENDER_SHADERPOLYGONMODE_H
#define MINTY_RENDER_SHADERPOLYGONMODE_H

/**
 * @file ShaderPolygonMode.h
 * @brief Header file defining the ShaderPolygonMode enum.
 * @author Mitchell Talyat
 */

#include "Minty/Data/String.h"
#include "Minty/Serialization/Parse.h"

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

	String to_string(ShaderPolygonMode const obj);
	ShaderPolygonMode parse_to_shader_polygon_mode(String const& string);
	Bool parse_try_shader_polygon_mode(String const& string, ShaderPolygonMode& value);
	template<>
	inline ShaderPolygonMode parse_to<ShaderPolygonMode>(StringView const string) { return parse_to_shader_polygon_mode(string); }
	template<>
	inline Bool parse_try<ShaderPolygonMode>(StringView const string, ShaderPolygonMode& value) { return parse_try_shader_polygon_mode(string, value); }
}

#endif // MINTY_RENDER_SHADERPOLYGONMODE_H