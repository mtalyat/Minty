#ifndef MINTY_RENDER_SHADERINPUTTYPE_H
#define MINTY_RENDER_SHADERINPUTTYPE_H

/**
 * @file ShaderInputType.h
 * @brief Header file defining the ShaderInputType enum.
 * @author Mitchell Talyat
 */

#include "Minty/Data/String.h"
#include "Minty/Serialization/Parse.h"

namespace Minty
{
	/**
	 * @brief Determines the type of input for a shader.
	 */
	enum class ShaderInputType
	{
		/**
		 * @brief Invalid.
		 */
		Undefined = 0,
		Sample = 1,

		/**
		 * @brief An image with a sampler.
		 */
		CombinedImageSampler = 2,

		SampledImage = 3,
		StorageImage = 4,
		UniformTexelBuffer = 5,
		StorageTexelBuffer = 6,

		/**
		 * @brief A uniform buffer, used for changing data.
		 */
		UniformBuffer = 7,

		/**
		 * @brief A storage buffer, used for infrequently changing data.
		 */
		StorageBuffer = 8,

		UniformBufferDynamic = 9,
		StorageBufferDynamic = 10,

		/**
		 * @brief A push constant, meant for frequently changing data.
		 */
		PushConstant = 11,
	};

	String to_string(ShaderInputType const obj);
	ShaderInputType parse_to_shader_input_type(String const& string);
	Bool parse_try_shader_input_type(String const& string, ShaderInputType& value);
	template<>
	inline ShaderInputType parse_to<ShaderInputType>(StringView const string) { return parse_to_shader_input_type(string); }
	template<>
	inline Bool parse_try<ShaderInputType>(StringView const string, ShaderInputType& value) { return parse_try_shader_input_type(string, value); }
}

#endif // MINTY_RENDER_SHADERINPUTTYPE_H