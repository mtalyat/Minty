#pragma once

/**
 * @file PipelineInputRate.h
 * @brief Header file defining the PipelineInputRate enum.
 * @author Mitchell Talyat
 */

#include "Core/Type/Enum.hpp"
#include "Core/Serialize/Parser.hpp"

namespace Minty
{
	/**
	 * @brief Determines what data is being inputted to the shader.
	 */
	enum class PipelineInputRateEnum
	{
		/**
		 * @brief Invalid.
		 */
		Undefined = 0,

		/**
		 * @brief The shader is using vertex data.
		 */
		Vertex = 1,

		/**
		 * @brief The shader is using instance data.
		 */
		Instance = 2,

		Count
	};

	MINTY_ENABLE_ENUM_OPERATORS(PipelineInputRateEnum)

	struct PipelineInputRate
	{
		PipelineInputRateEnum value;

		constexpr PipelineInputRate() : value(PipelineInputRateEnum::Undefined) {}
		constexpr PipelineInputRate(PipelineInputRateEnum v) : value(v) {}
		constexpr operator PipelineInputRateEnum() const { return value; }
	};
	
	template<>
	struct Parser<PipelineInputRateEnum>
	{
		static Bool parse(StringView const str, PipelineInputRateEnum& value);
		static String to_string(PipelineInputRateEnum const& obj);
	};

	template<>
	struct Parser<PipelineInputRate>
	{
		inline static Bool parse(StringView const str, PipelineInputRate& value) { return Parser<PipelineInputRateEnum>::parse(str, value.value); }
		inline static String to_string(PipelineInputRate const& obj) { return Parser<PipelineInputRateEnum>::to_string(obj.value); }
	};
}
