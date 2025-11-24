#pragma once
#include "Minty/Data/String.h"
#include "Minty/Serialization/Parse.h"

namespace Minty
{
	/// <summary>
	/// Determines how the image data is filtered.
	/// </summary>
	enum class Filter
	{
		/// <summary>
		/// Invalid.
		/// </summary>
		Undefined = 0,

		/// <summary>
		/// Use the nearest pixel.
		/// </summary>
		Nearest = 1,

		/// <summary>
		/// Linearly interpolate between pixels.
		/// </summary>
		Linear = 2,
	};

	String to_string(Filter const obj);
	Filter parse_to_filter(String const& string);
	Bool parse_try_filter(String const& string, Filter& value);
	template<>
	inline Filter parse_to<Filter>(String const& string) { return parse_to_filter(string); }
	template<>
	inline Bool parse_try<Filter>(String const& string, Filter& value) { return parse_try_filter(string, value); }
}