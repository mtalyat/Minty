#pragma once

/**
 * @file PipelineFrontFace.hpp
 * @brief Header file defining the PipelineFrontFace enum.
 * @author Mitchell Talyat
 */

#include "Core/Type/Enum.hpp"
#include "Core/Serialize/Parser.hpp"

namespace Minty
{
	/**
	 * @brief Determines which side of the polygon is the front.
	 */
	enum class PipelineFrontFaceEnum
	{
		/**
		 * @brief Invalid.
		 */
		Undefined = 0,

		/**
		 * @brief The front face is determined by the counter-clockwise winding order.
		 */
		CounterClockwise = 1,

		/**
		 * @brief The front face is determined by the clockwise winding order.
		 */
		Clockwise = 2,

		Count,

		Default = Clockwise,
	};

	MINTY_ENABLE_ENUM_OPERATORS(PipelineFrontFaceEnum)

	struct PipelineFrontFace
	{
		PipelineFrontFaceEnum value;

		constexpr PipelineFrontFace() : value(PipelineFrontFaceEnum::Default) {}
		constexpr PipelineFrontFace(PipelineFrontFaceEnum v) : value(v) {}
		constexpr operator PipelineFrontFaceEnum() const { return value; }
	};

	template<>
	struct Parser<PipelineFrontFaceEnum>
	{
		static Bool parse(StringView const str, PipelineFrontFaceEnum& value);
		static String to_string(PipelineFrontFaceEnum const& obj);
	};

	template<>
	struct Parser<PipelineFrontFace>
	{
		inline static Bool parse(StringView const str, PipelineFrontFace& value) { return Parser<PipelineFrontFaceEnum>::parse(str, value.value); }
		inline static String to_string(PipelineFrontFace const& obj) { return Parser<PipelineFrontFaceEnum>::to_string(obj.value); }
	};
}
