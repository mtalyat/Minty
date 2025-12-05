#ifndef MINTY_RENDER_FILTER_H
#define MINTY_RENDER_FILTER_H

/**
 * @file Filter.h
 * @brief Header file defining the Filter enum.
 * @author Mitchell Talyat
 */

#include "Minty/Data/String.h"
#include "Minty/Serialization/Parse.h"

namespace Minty
{
	/**
	 * @brief Determines how the image data is filtered.
	 */
	enum class Filter
	{
		/**
		 * @brief Invalid.
		 */
		Undefined = 0,

		/**
		 * @brief Use the nearest pixel.
		 */
		Nearest = 1,

		/**
		 * @brief Linearly interpolate between pixels.
		 */
		Linear = 2,
	};

	String to_string(Filter const obj);
	Filter parse_to_filter(String const& string);
	Bool parse_try_filter(String const& string, Filter& value);
	template<>
	inline Filter parse_to<Filter>(StringView const string) { return parse_to_filter(string); }
	template<>
	inline Bool parse_try<Filter>(StringView const string, Filter& value) { return parse_try_filter(string, value); }
}

#endif // MINTY_RENDER_FILTER_H