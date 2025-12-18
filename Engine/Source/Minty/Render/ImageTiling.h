#ifndef MINTY_RENDER_IMAGETILING_H
#define MINTY_RENDER_IMAGETILING_H

/**
 * @file ImageTiling.h
 * @brief Header file defining the ImageTiling enum.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Enum.h"
#include "Minty/Data/String.h"
#include "Minty/Serialization/Parse.h"

namespace Minty
{
	/**
	 * @brief Determines how the image is tiled.
	 */
	enum class ImageTiling
	{
		/**
		 * @brief Invalid.
		 */
		Undefined = 0,

		/**
		 * @brief Optimal tiling.
		 */
		Optimal,

		/**
		 * @brief Linear tiling.
		 */
		Linear,
	};

	MINTY_ENABLE_ENUM_OPERATORS(ImageTiling);

	String to_string(ImageTiling const obj);
	ImageTiling parse_to_image_tiling(String const& string);
	Bool parse_try_image_tiling(String const& string, ImageTiling& value);
	template<>
	inline ImageTiling parse_to<ImageTiling>(StringView const string) { return parse_to_image_tiling(string); }
	template<>
	inline Bool parse_try<ImageTiling>(StringView const string, ImageTiling& value) { return parse_try_image_tiling(string, value); }
}

#endif // MINTY_RENDER_IMAGETILING_H