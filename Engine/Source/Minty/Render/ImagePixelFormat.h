#ifndef MINTY_RENDER_IMAGEPIXELFORMAT_H
#define MINTY_RENDER_IMAGEPIXELFORMAT_H

/**
 * @file ImagePixelFormat.h
 * @brief Header file defining the ImagePixelFormat enum.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Enum.h"
#include "Minty/Serialization/Parser.h"

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

	template<>
	struct Parser<ImagePixelFormat>
	{
		static Bool parse(StringView const str, ImagePixelFormat& value);
		static String to_string(ImagePixelFormat const& obj);
	};
}

#endif // MINTY_RENDER_IMAGEPIXELFORMAT_H