#pragma once
#include "Minty/Data/String.h"
#include "Minty/Serialization/Parse.h"

namespace Minty
{
	/// <summary>
	/// Determines how the Shader culls faces.
	/// </summary>
	enum class ShaderCullMode
	{
		Undefined = 0,

		/// <summary>
		/// There is no culling.
		/// </summary>
		None = 1,

		/// <summary>
		/// The front side of a face is culled.
		/// </summary>
		Front = 2,

		/// <summary>
		/// The back side of a face is culled.
		/// </summary>
		Back = 3,
		
		/// <summary>
		/// Both sides of a face are culled.
		/// </summary>
		Both = 4,
	};

	String to_string(ShaderCullMode const obj);
	ShaderCullMode parse_to_shader_cull_mode(String const& string);
	Bool parse_try_shader_cull_mode(String const& string, ShaderCullMode& value);
	template<>
	inline ShaderCullMode parse_to<ShaderCullMode>(String const& string) { return parse_to_shader_cull_mode(string); }
	template<>
	inline Bool parse_try<ShaderCullMode>(String const& string, ShaderCullMode& value) { return parse_try_shader_cull_mode(string, value); }
}