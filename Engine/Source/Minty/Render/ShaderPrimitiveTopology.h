#ifndef MINTY_RENDER_SHADERPRIMITIVETOPOLOGY_H
#define MINTY_RENDER_SHADERPRIMITIVETOPOLOGY_H

/**
 * @file ShaderPrimitiveTopology.h
 * @brief Header file defining the ShaderPrimitiveTopology enum.
 * @author Mitchell Talyat
 */

#include "Minty/Data/String.h"
#include "Minty/Serialization/Parse.h"

namespace Minty
{
	/**
	 * @brief Determines the type of primitive topology to use when rendering the vertex data.
	 */
	enum class ShaderPrimitiveTopology
	{
		/**
		 * @brief Invalid.
		 */
		Undefined = 0,

		/**
		 * @brief The vertex data is a list of points.
		 */
		PointList = 1,

		/**
		 * @brief The vertex data is a list of lines. Every 2 vertices is a line.
		 */
		LineList = 2,

		/**
		 * @brief The vertex data is a line strip.
		 */
		LineStrip = 3,

		/**
		 * @brief The vertex data is a list of triangles. Every 3 vertices is a triangle.
		 */
		TriangleList = 4,

		/**
		 * @brief The vertex data is a triangle strip.
		 */
		TriangleStrip = 5,

		/**
		 * @brief The vertex data is a triangle fan. The first vertex is the center and every 2 vertices is a triangle.
		 */
		TriangleFan = 6,
	};

	String to_string(ShaderPrimitiveTopology const obj);
	ShaderPrimitiveTopology parse_to_shader_primitive_topology(String const& string);
	Bool parse_try_shader_primitive_topology(String const& string, ShaderPrimitiveTopology& value);
	template<>
	inline ShaderPrimitiveTopology parse_to<ShaderPrimitiveTopology>(String const& string) { return parse_to_shader_primitive_topology(string); }
	template<>
	inline Bool parse_try<ShaderPrimitiveTopology>(String const& string, ShaderPrimitiveTopology& value) { return parse_try_shader_primitive_topology(string, value); }
}

#endif // MINTY_RENDER_SHADERPRIMITIVETOPOLOGY_H