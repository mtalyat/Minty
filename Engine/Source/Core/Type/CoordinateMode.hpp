#pragma once

/**
 * @file CoordinateMode.hpp
 * @brief Header file defining the CoordinateModeEnum enum.
 * @author Mitchell Talyat
 */

#include "Core/Serialize/Parser.hpp"

namespace Minty
{
	/**
	 * @brief Determines how coordinates are interpreted.
	 */
	enum class CoordinateModeEnum
	{
		/**
		 * @brief Invalid.
		 */
		Undefined = 0,

		/**
		 * @brief Each coordinate is represented with a float that falls within the range of [0, 1].
		 */
		Normalized = 1,

		/**
		 * @brief Each coordinate is represented with an integer that falls within the range of [0, size], where size is the width or height, respectively.
		 */
		Pixel = 2,

		Count,

		Default = Normalized
	};

	struct CoordinateMode
	{
		CoordinateModeEnum value;

		constexpr CoordinateMode() : value(CoordinateModeEnum::Undefined) {}
		constexpr CoordinateMode(CoordinateModeEnum const value) : value(value) {}
		constexpr operator CoordinateModeEnum() const { return value; }

		constexpr Bool operator==(CoordinateModeEnum const other) const { return value == other; }
		constexpr Bool operator!=(CoordinateModeEnum const other) const { return value != other; }
	};
	
	template<>
	struct Parser<CoordinateModeEnum>
	{
		static Bool parse(StringView const str, CoordinateModeEnum& value);
		static String to_string(CoordinateModeEnum const& obj);
	};

	template<>
	struct Parser<CoordinateMode>
	{
		inline static Bool parse(StringView const str, CoordinateMode& value) { return Parser<CoordinateModeEnum>::parse(str, value.value); }
		inline static String to_string(CoordinateMode const& obj) { return Parser<CoordinateModeEnum>::to_string(obj.value); }
	};
}
