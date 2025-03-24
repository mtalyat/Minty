#pragma once
#include "Minty/Data/String.h"
#include "Minty/Serialization/Parse.h"

namespace Minty
{
	/// <summary>
	/// Determines how the polygons are being drawn.
	/// </summary>
	enum class ShaderPolygonMode
	{
		/// <summary>
		/// Invalid.
		/// </summary>
		Undefined = 0,

		/// <summary>
		/// Fill the polygon.
		/// </summary>
		Fill = 1,

		/// <summary>
		/// Draw the outlines of the polygon.
		/// </summary>
		Line = 2,

		/// <summary>
		/// Draw the points of the polygon.
		/// </summary>
		Point = 3,
	};

	String to_string(ShaderPolygonMode const obj);
	ShaderPolygonMode parse_to_shader_polygon_mode(String const& string);
	Bool parse_try_shader_polygon_mode(String const& string, ShaderPolygonMode& value);
	template<>
	inline ShaderPolygonMode parse_to<ShaderPolygonMode>(String const& string) { return parse_to_shader_polygon_mode(string); }
	template<>
	inline Bool parse_try<ShaderPolygonMode>(String const& string, ShaderPolygonMode& value) { return parse_try_shader_polygon_mode(string, value); }
}