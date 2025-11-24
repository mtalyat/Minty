#pragma once
#include "Minty/Data/String.h"
#include "Minty/Serialization/Parse.h"

namespace Minty
{
	/// <summary>
	/// Determines the type of primitive topology to use when rendering the vertex data.
	/// </summary>
	enum class ShaderPrimitiveTopology
	{
		/// <summary>
		/// Invalid.
		/// </summary>
		Undefined = 0,

		/// <summary>
		/// The vertex data is a list of points.
		/// </summary>
		PointList = 1,

		/// <summary>
		/// The vertex data is a list of lines. Every 2 vertices is a line.
		/// </summary>
		LineList = 2,

		/// <summary>
		/// The vertex data is a line strip.
		/// </summary>
		LineStrip = 3,

		/// <summary>
		/// The vertex data is a list of triangles. Every 3 vertices is a triangle.
		/// </summary>
		TriangleList = 4,

		/// <summary>
		/// The vertex data is a triangle strip.
		/// </summary>
		TriangleStrip = 5,

		/// <summary>
		/// The vertex data is a triangle fan. The first vertex is the center and every 2 vertices is a triangle.
		/// </summary>
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