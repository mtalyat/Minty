#pragma once
#include "Minty/Data/String.h"
#include "Minty/Serialization/Parse.h"

namespace Minty
{
	/// <summary>
	/// The format for how pixels are read.
	/// </summary>
	enum class ImagePixelFormat
	{
		/// <summary>
		/// No format.
		/// </summary>
		None = 0,
		/// <summary>
		/// Gray channel only.
		/// </summary>
		Gray = 1,
		/// <summary>
		/// Gray and alpha channels.
		/// </summary>
		GrayAlpha = 2,
		/// <summary>
		/// Red, green and blue channels.
		/// </summary>
		RedGreenBlue = 3,
		/// <summary>
		/// Red, green, blue and alpha channels.
		/// </summary>
		RedGreenBlueAlpha = 4,
	};

	String to_string(ImagePixelFormat const obj);
	ImagePixelFormat parse_to_image_pixel_format(String const& string);
	Bool parse_try_image_pixel_format(String const& string, ImagePixelFormat& value);
	template<>
	inline ImagePixelFormat parse_to<ImagePixelFormat>(String const& string) { return parse_to_image_pixel_format(string); }
	template<>
	inline Bool parse_try<ImagePixelFormat>(String const& string, ImagePixelFormat& value) { return parse_try_image_pixel_format(string, value); }
}