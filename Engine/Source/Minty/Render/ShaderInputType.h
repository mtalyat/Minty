#ifndef MINTY_RENDER_SHADERINPUTTYPE_H
#define MINTY_RENDER_SHADERINPUTTYPE_H

/**
 * @file ShaderInputType.h
 * @brief Header file defining the ShaderInputType enum.
 * @author Mitchell Talyat
 */

#include "Minty/Serialization/Parser.h"

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

		/**
		 * @brief A sampler.
		 */
		Sample = 1,

		/**
		 * @brief An image with a sampler.
		 */
		CombinedImageSampler = 2,

		/**
		 * @brief An image without a sampler.
		 */
		SampledImage = 3,

		/**
		 * @brief A storage image.
		 */
		StorageImage = 4,

		/**
		 * @brief A uniform texel buffer.
		 */
		UniformTexelBuffer = 5,

		/**
		 * @brief A storage texel buffer.
		 */
		StorageTexelBuffer = 6,

		/**
		 * @brief A uniform buffer, used for changing data.
		 */
		UniformBuffer = 7,

		/**
		 * @brief A storage buffer, used for infrequently changing data.
		 */
		StorageBuffer = 8,

		/**
		 * @brief A dynamic uniform buffer.
		 */
		UniformBufferDynamic = 9,

		/**
		 * @brief A dynamic storage buffer.
		 */
		StorageBufferDynamic = 10,

		/**
		 * @brief A push constant, meant for frequently changing data.
		 */
		PushConstant = 11,
	};
	
	template<>
	struct Parser<ShaderInputType>
	{
		static Bool parse(StringView const str, ShaderInputType& value);
		static String to_string(ShaderInputType const& obj);
	};
}

#endif // MINTY_RENDER_SHADERINPUTTYPE_H