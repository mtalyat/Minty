#pragma once
#include "Minty/Data/String.h"
#include "Minty/Serialization/Parse.h"

namespace Minty
{
	/// <summary>
	/// Determines what data is being inputted to the shader.
	/// </summary>
	enum class ShaderInputRate
	{
		/// <summary>
		/// Invalid.
		/// </summary>
		Undefined = 0,

		/// <summary>
		/// The shader is using vertex data.
		/// </summary>
		Vertex = 1,

		/// <summary>
		/// The shader is using instance data.
		/// </summary>
		Instance = 2
	};

	String to_string(ShaderInputRate const obj);
	ShaderInputRate parse_to_shader_input_rate(String const& string);
	Bool parse_try_shader_input_rate(String const& string, ShaderInputRate& value);
	template<>
	inline ShaderInputRate parse_to<ShaderInputRate>(String const& string) { return parse_to_shader_input_rate(string); }
	template<>
	inline Bool parse_try<ShaderInputRate>(String const& string, ShaderInputRate& value) { return parse_try_shader_input_rate(string, value); }
}