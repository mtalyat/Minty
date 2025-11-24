#pragma once
#include "Minty/Data/String.h"
#include "Minty/Serialization/Parse.h"

namespace Minty
{
	/// <summary>
	/// Determines the type of input for a shader.
	/// </summary>
	enum class ShaderInputType
	{
		/// <summary>
		/// Invalid.
		/// </summary>
		Undefined = 0,
		Sample = 1,

		/// <summary>
		/// An image with a sampler.
		/// </summary>
		CombinedImageSampler = 2,

		SampledImage = 3,
		StorageImage = 4,
		UniformTexelBuffer = 5,
		StorageTexelBuffer = 6,

		/// <summary>
		/// A uniform buffer, used for changing data.
		/// </summary>
		UniformBuffer = 7,

		/// <summary>
		/// A storage buffer, used for infrequently changing data.
		/// </summary>
		StorageBuffer = 8,

		UniformBufferDynamic = 9,
		StorageBufferDynamic = 10,

		/// <summary>
		/// A push constant, meant for frequently changing data.
		/// </summary>
		PushConstant = 11,
	};

	String to_string(ShaderInputType const obj);
	ShaderInputType parse_to_shader_input_type(String const& string);
	Bool parse_try_shader_input_type(String const& string, ShaderInputType& value);
	template<>
	inline ShaderInputType parse_to<ShaderInputType>(String const& string) { return parse_to_shader_input_type(string); }
	template<>
	inline Bool parse_try<ShaderInputType>(String const& string, ShaderInputType& value) { return parse_try_shader_input_type(string, value); }
}