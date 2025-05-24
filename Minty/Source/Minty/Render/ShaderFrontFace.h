#pragma once
#include "Minty/Data/String.h"
#include "Minty/Serialization/Parse.h"

namespace Minty
{
	/// <summary>
	/// Determines which side of the polygon is the front.
	/// </summary>
	enum class ShaderFrontFace
	{
		/// <summary>
		/// Invalid.
		/// </summary>
		Undefined = 0,

		/// <summary>
		/// The front face is determined by the counter-clockwise winding order.
		/// </summary>
		CounterClockwise = 1,

		/// <summary>
		/// The front face is determined by the clockwise winding order.
		/// </summary>
		Clockwise = 2,
	};

	String to_string(ShaderFrontFace const obj);
	ShaderFrontFace parse_to_shader_front_face(String const& string);
	Bool parse_try_shader_front_face(String const& string, ShaderFrontFace& value);
	template<>
	inline ShaderFrontFace parse_to<ShaderFrontFace>(String const& string) { return parse_to_shader_front_face(string); }
	template<>
	inline Bool parse_try<ShaderFrontFace>(String const& string, ShaderFrontFace& value) { return parse_try_shader_front_face(string, value); }
}