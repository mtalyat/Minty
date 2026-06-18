#pragma once

/**
 * @file PipelineInputType.h
 * @brief Header file defining the PipelineInputType enum.
 * @author Mitchell Talyat
 */

#include "Core/Type/Enum.h"
#include "Core/Serialize/Parser.h"

namespace Minty
{
	/**
	 * @brief Determines the type of input for a shader.
	 */
	enum class PipelineInputTypeEnum
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

		Count,
	};

	MINTY_ENABLE_ENUM_OPERATORS(PipelineInputTypeEnum)

	struct PipelineInputType
	{
		PipelineInputTypeEnum value;

		constexpr PipelineInputType() : value(PipelineInputTypeEnum::Undefined) {}
		constexpr PipelineInputType(PipelineInputTypeEnum v) : value(v) {}
		constexpr operator PipelineInputTypeEnum() const { return value; }
	};
	
	template<>
	struct Parser<PipelineInputTypeEnum>
	{
		static Bool parse(StringView const str, PipelineInputTypeEnum& value);
		static String to_string(PipelineInputTypeEnum const& obj);
	};

	template<>
	struct Parser<PipelineInputType>
	{
		inline static Bool parse(StringView const str, PipelineInputType& value) { return Parser<PipelineInputTypeEnum>::parse(str, value.value); }
		inline static String to_string(PipelineInputType const& obj) { return Parser<PipelineInputTypeEnum>::to_string(obj.value); }
	};
}
