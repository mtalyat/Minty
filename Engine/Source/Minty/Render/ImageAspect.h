#ifndef MINTY_RENDER_IMAGE_ASPECT_H
#define MINTY_RENDER_IMAGE_ASPECT_H

/**
 * @file ImageAspect.h
 * @brief Header file defining the ImageAspect enum.
 * @author Mitchell Talyat
 */

#include "Minty/Data/String.h"
#include "Minty/Serialization/Parse.h"

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

	String to_string(ImageAspect const obj);
	ImageAspect parse_to_image_aspect(String const& string);
	Bool parse_try_image_aspect(String const& string, ImageAspect& value);
	template<>
	inline ImageAspect parse_to<ImageAspect>(String const& string) { return parse_to_image_aspect(string); }
	template<>
	inline Bool parse_try<ImageAspect>(String const& string, ImageAspect& value) { return parse_try_image_aspect(string, value); }
}

#endif // MINTY_RENDER_IMAGE_ASPECT_H