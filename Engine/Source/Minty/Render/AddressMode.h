#ifndef MINTY_RENDER_ADDRESSMODE_H
#define MINTY_RENDER_ADDRESSMODE_H

/**
 * @file AddressMode.h
 * @brief Header file defining the AddressMode enum.
 * @author Mitchell Talyat
 */

#include "Minty/Serialization/Parse.h"
#include "Minty/Serialization/ToString.h"

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

	String to_string(AddressMode const obj);
	AddressMode parse_to_address_mode(String const& string);
	Bool parse_try_address_mode(String const& string, AddressMode& value);
	template<>
	inline AddressMode parse_to<AddressMode>(StringView const string) { return parse_to_address_mode(string); }
	template<>
	inline Bool parse_try<AddressMode>(StringView const string, AddressMode& value) { return parse_try_address_mode(string, value); }
}

#endif // MINTY_RENDER_ADDRESSMODE_H