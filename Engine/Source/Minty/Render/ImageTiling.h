#ifndef MINTY_RENDER_IMAGETILING_H
#define MINTY_RENDER_IMAGETILING_H

/**
 * @file ImageTiling.h
 * @brief Header file defining the ImageTiling enum.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Enum.h"
#include "Minty/Serialization/Parser.h"

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
	
	template<>
	struct Parser<ImageTiling>
	{
		static Bool parse(StringView const str, ImageTiling& value);
		static String to_string(ImageTiling const& obj);
	};
}

#endif // MINTY_RENDER_IMAGETILING_H