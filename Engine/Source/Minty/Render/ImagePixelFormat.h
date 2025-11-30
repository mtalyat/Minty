#ifndef MINTY_RENDER_IMAGEPIXELFORMAT_H
#define MINTY_RENDER_IMAGEPIXELFORMAT_H

/**
 * @file ImagePixelFormat.h
 * @brief Header file defining the ImagePixelFormat enum.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Enum.h"
#include "Minty/Data/String.h"
#include "Minty/Serialization/Parse.h"

namespace Minty
{
	/**
	 * @brief The format for how pixels are read.
	 */
	enum class ImagePixelFormat
	{
		/**
		 * @brief No format.
		 */
		None = 0,

		/**
		 * @brief Gray channel only.
		 */
		Gray = 1,

		/**
		 * @brief Gray and alpha channels.
		 */
		GrayAlpha = 2,

		/**
		 * @brief Red, green and blue channels.
		 */
		RedGreenBlue = 3,

		/**
		 * @brief Red, green, blue and alpha channels.
		 */
		RedGreenBlueAlpha = 4,
	};

	MINTY_ENABLE_ENUM_OPERATORS(ImagePixelFormat);

	String to_string(ImagePixelFormat const obj);
	ImagePixelFormat parse_to_image_pixel_format(String const& string);
	Bool parse_try_image_pixel_format(String const& string, ImagePixelFormat& value);
	template<>
	inline ImagePixelFormat parse_to<ImagePixelFormat>(String const& string) { return parse_to_image_pixel_format(string); }
	template<>
	inline Bool parse_try<ImagePixelFormat>(String const& string, ImagePixelFormat& value) { return parse_try_image_pixel_format(string, value); }
}

#endif // MINTY_RENDER_IMAGEPIXELFORMAT_H