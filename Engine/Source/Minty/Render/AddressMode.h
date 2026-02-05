#ifndef MINTY_RENDER_ADDRESSMODE_H
#define MINTY_RENDER_ADDRESSMODE_H

/**
 * @file AddressMode.h
 * @brief Header file defining the AddressMode enum.
 * @author Mitchell Talyat
 */

#include "Minty/Serialization/Parser.h"

namespace Minty
{
	/**
	 * @brief Determines how the image data is accessed in the pipeline.
	 */
	enum class AddressMode
	{
		/**
		 * @brief Invalid.
		 */
		Undefined = 0,

		/**
		 * @brief The texture coordinates are repeated.
		 */
		Repeat = 1,

		/**
		 * @brief The texture coordinates are mirrored and repeated.
		 */
		MirroredRepeat = 2,

		/**
		 * @brief The texture coordinates are clamped to the edge.
		 */
		ClampToEdge = 3,

		/**
		 * @brief The texture coordinates are clamped to the border.
		 */
		ClampToBorder = 4,

		/**
		 * @brief The texture coordinates are mirrored and clamped to the edge.
		 */
		MirroredClampToEdge = 5,
	};
	
	template<>
	struct Parser<AddressMode>
	{
		static Bool parse(StringView const str, AddressMode& value);
		static String to_string(AddressMode const& obj);
	};
}

#endif // MINTY_RENDER_ADDRESSMODE_H