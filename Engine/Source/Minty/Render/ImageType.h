#ifndef MINTY_RENDER_IMAGETYPE_H
#define MINTY_RENDER_IMAGETYPE_H

/**
 * @file ImageType.h
 * @brief Header file defining the ImageType enum.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Enum.h"
#include "Minty/Serialization/Parser.h"

namespace Minty
{
	/**
	 * @brief The amount of dimensions on the image.
	 */
	enum class ImageType
	{
		/**
		 * @brief Invalid.
		 */
		Undefined = 0,

		/**
		 * @brief One dimensional.
		 */
		D1 = 1,

		/**
		 * @brief Two dimensional.
		 */
		D2 = 2,

		/**
		 * @brief Three dimensional.
		 */
		D3 = 3,
	};

	MINTY_ENABLE_ENUM_OPERATORS(ImageType);
	
	template<>
	struct Parser<ImageType>
	{
		static Bool parse(StringView const str, ImageType& value);
		static String to_string(ImageType const& obj);
	};
}

#endif // MINTY_RENDER_IMAGETYPE_H