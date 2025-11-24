#pragma once
#include "Minty/Data/String.h"
#include "Minty/Serialization/Parse.h"

namespace Minty
{
	/// <summary>
	/// Determines how coordinates are interpreted.
	/// </summary>
	enum class CoordinateMode
	{
		/// <summary>
		/// Invalid.
		/// </summary>
		Undefined = 0,

		/// <summary>
		/// Each coordinate is represented with a float that falls within the range of [0, 1].
		/// </summary>
		Normalized = 1,

		/// <summary>
		/// Each coordinate is represented with an integer that falls within the range of [0, size], where size is the width or height, respectively.
		/// </summary>
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