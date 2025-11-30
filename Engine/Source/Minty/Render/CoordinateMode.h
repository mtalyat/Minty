#ifndef MINTY_RENDER_COORDINATEMODE_H
#define MINTY_RENDER_COORDINATEMODE_H

/**
 * @file CoordinateMode.h
 * @brief Header file defining the CoordinateMode enum.
 * @author Mitchell Talyat
 */

#include "Minty/Data/String.h"
#include "Minty/Serialization/Parse.h"

namespace Minty
{
	/**
	 * @brief Determines how coordinates are interpreted.
	 */
	enum class CoordinateMode
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
	};

	String to_string(CoordinateMode const obj);
	CoordinateMode parse_to_coordinate_mode(String const& string);
	Bool parse_try_coordinate_mode(String const& string, CoordinateMode& value);
	template<>
	inline CoordinateMode parse_to<CoordinateMode>(String const& string) { return parse_to_coordinate_mode(string); }
	template<>
	inline Bool parse_try<CoordinateMode>(String const& string, CoordinateMode& value) { return parse_try_coordinate_mode(string, value); }
}

#endif // MINTY_RENDER_COORDINATEMODE_H