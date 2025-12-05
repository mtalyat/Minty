#ifndef MINTY_RENDER_IMAGETYPE_H
#define MINTY_RENDER_IMAGETYPE_H

/**
 * @file ImageType.h
 * @brief Header file defining the ImageType enum.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Enum.h"
#include "Minty/Data/String.h"
#include "Minty/Serialization/Parse.h"

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

	String to_string(ImageType const obj);
	ImageType parse_to_image_type(String const& string);
	Bool parse_try_image_type(String const& string, ImageType& value);
	template<>
	inline ImageType parse_to<ImageType>(StringView const string) { return parse_to_image_type(string); }
	template<>
	inline Bool parse_try<ImageType>(StringView const string, ImageType& value) { return parse_try_image_type(string, value); }
}

#endif // MINTY_RENDER_IMAGETYPE_H