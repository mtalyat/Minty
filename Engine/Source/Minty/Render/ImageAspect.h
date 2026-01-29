#ifndef MINTY_RENDER_IMAGE_ASPECT_H
#define MINTY_RENDER_IMAGE_ASPECT_H

/**
 * @file ImageAspect.h
 * @brief Header file defining the ImageAspect enum.
 * @author Mitchell Talyat
 */

#include "Minty/Data/String.h"
#include "Minty/Serialization/Parser.h"

namespace Minty
{
	/**
	 * @brief Determines how the image is used in the pipeline.
	 */
	enum class ImageAspect
	{
		/**
		 * @brief Invalid.
		 */
		Undefined = 0,

		/**
		 * @brief Used for color.
		 */
		Color = 1,

		/**
		 * @brief Used for depth.
		 */
		Depth = 2,
	};
	
	template<>
	struct Parser<ImageAspect>
	{
		static Bool parse(StringView const str, ImageAspect& value);
		static String to_string(ImageAspect const& obj);
	};
}

#endif // MINTY_RENDER_IMAGE_ASPECT_H