#pragma once
#include "Minty/Data/String.h"
#include "Minty/Serialization/Parse.h"

namespace Minty
{
	/// <summary>
	/// Determines how the image is tiled.
	/// </summary>
	enum class ImageTiling
	{
		/// <summary>
		/// Invalid.
		/// </summary>
		Undefined = 0,

		/// <summary>
		/// 
		/// </summary>
		Optimal,

		/// <summary>
		/// 
		/// </summary>
		Linear,
	};

	String to_string(ImageTiling const obj);
	ImageTiling parse_to_image_tiling(String const& string);
	Bool parse_try_image_tiling(String const& string, ImageTiling& value);
	template<>
	inline ImageTiling parse_to<ImageTiling>(String const& string) { return parse_to_image_tiling(string); }
	template<>
	inline Bool parse_try<ImageTiling>(String const& string, ImageTiling& value) { return parse_try_image_tiling(string, value); }
}