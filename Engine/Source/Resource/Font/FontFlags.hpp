#pragma once

/**
 * @file FontFlags.hpp
 * @brief Header file defining the FontFlags enum.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include "Core/Serialize/Parser.hpp"

namespace Minty
{
	/**
	 * @brief Defines the flags that can be applied to a font.
	 */
	enum class FontFlagsEnum
	{
		/**
		 * @brief The font is regular, with no special styling.
		 */
		None = 0x0,

		/**
		 * @brief The font is bold.
		 */
		Bold = 0x1,

		/**
		 * @brief The font is italic.
		 */
		Italic = 0x2,

		Count = 3,

		Default = None
	};

	struct FontFlags
	{
		FontFlagsEnum value;

		constexpr FontFlags() : value(FontFlagsEnum::None) {}
		constexpr FontFlags(FontFlagsEnum flags) : value(flags) {}
		constexpr operator FontFlagsEnum() const { return value; }

		constexpr Bool has_flag(FontFlagsEnum flag) const { return (static_cast<Size>(value) & static_cast<Size>(flag)) != 0; }
		constexpr FontFlagsEnum operator|(FontFlagsEnum other) const { return static_cast<FontFlagsEnum>(static_cast<Size>(value) | static_cast<Size>(other)); }
		constexpr FontFlagsEnum operator&(FontFlagsEnum other) const { return static_cast<FontFlagsEnum>(static_cast<Size>(value) & static_cast<Size>(other)); }
		constexpr FontFlagsEnum operator~() const { return static_cast<FontFlagsEnum>(~static_cast<Size>(value)); }
	};

	template<>
	struct Parser<FontFlagsEnum>
	{
		static Bool parse(StringView const str, FontFlagsEnum& value);
		static String to_string(FontFlagsEnum const& obj);
	};

	template<>
	struct Parser<FontFlags>
	{
		inline static Bool parse(StringView const str, FontFlags& value) { return Parser<FontFlagsEnum>::parse(str, value.value); }
		inline static String to_string(FontFlags const& obj) { return Parser<FontFlagsEnum>::to_string(obj.value); }
	};
}
