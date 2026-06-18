#pragma once

/**
 * @file AddressMode.h
 * @brief Header file defining the AddressMode enum.
 * @author Mitchell Talyat
 */

#include "Core/Serialize/Parser.h"
#include "Core/Type/Enum.h"

namespace Minty
{
	/**
	 * @brief Determines how the image data is accessed in the pipeline.
	 */
	enum class TextureAddressModeEnum
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

		Count,

		Default = Repeat // Default address mode to use when one is not specified
	};

	MINTY_ENABLE_ENUM_OPERATORS(TextureAddressModeEnum)

	struct TextureAddressMode
	{
		TextureAddressModeEnum value;

		TextureAddressMode() : value(TextureAddressModeEnum::Undefined) {}
		TextureAddressMode(TextureAddressModeEnum const value) : value(value) {}
		operator TextureAddressModeEnum() const { return value; }
	};
	
	template<>
	struct Parser<TextureAddressModeEnum>
	{
		static Bool parse(StringView const str, TextureAddressModeEnum& value);
		static String to_string(TextureAddressModeEnum const& obj);
	};
	
	template<>
	struct Parser<TextureAddressMode>
	{
		inline static Bool parse(StringView const str, TextureAddressMode& value) { return Parser<TextureAddressModeEnum>::parse(str, value.value); }
		inline static String to_string(TextureAddressMode const& obj) { return Parser<TextureAddressModeEnum>::to_string(obj.value); }
	};
}
