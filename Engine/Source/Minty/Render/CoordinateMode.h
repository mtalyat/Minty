#ifndef MINTY_RENDER_COORDINATEMODE_H
#define MINTY_RENDER_COORDINATEMODE_H

/**
 * @file CoordinateMode.h
 * @brief Header file defining the CoordinateMode enum.
 * @author Mitchell Talyat
 */

#include "Minty/Data/String.h"
#include "Minty/Serialization/Parser.h"

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
	
	template<>
	struct Parser<CoordinateMode>
	{
		static Bool parse(StringView const str, CoordinateMode& value);
		static String to_string(CoordinateMode const& obj);
	};
}

#endif // MINTY_RENDER_COORDINATEMODE_H