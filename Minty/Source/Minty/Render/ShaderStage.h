#pragma once
#include "Minty/Data/String.h"
#include "Minty/Serialization/Parse.h"

namespace Minty
{
	/// <summary>
	/// Determines the stage of the shader.
	/// </summary>
	enum class ShaderStage
	{
		/// <summary>
		/// Invalid.
		/// </summary>
		Undefined,
		
		/// <summary>
		/// The vertex shader stage.
		/// </summary>
		Vertex,

		/// <summary>
		/// The fragment shader stage.
		/// </summary>
		Fragment
	};

	String to_string(ShaderStage const obj);
	ShaderStage parse_to_shader_stage(String const& string);
	Bool parse_try_shader_stage(String const& string, ShaderStage& value);
	template<>
	inline ShaderStage parse_to<ShaderStage>(String const& string) { return parse_to_shader_stage(string); }
	template<>
	inline Bool parse_try<ShaderStage>(String const& string, ShaderStage& value) { return parse_try_shader_stage(string, value); }
}