#ifndef MINTY_RENDER_FONTFLAGS_H
#define MINTY_RENDER_FONTFLAGS_H

/**
 * @file FontFlags.h
 * @brief Header file defining the FontFlags enum.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Enum.h"
#include "Minty/Serialization/Parse.h"
#include "Minty/Serialization/ToString.h"

namespace Minty
{
	/**
	 * @brief Defines the flags that can be applied to a font.
	 */
	enum class FontFlags
	{
		/**
		 * @brief The font is regular, with no special styling.
		 */
		None = 0,

		/**
		 * @brief The font is bold.
		 */
		Bold = 1 << 0,

		/**
		 * @brief The font is italic.
		 */
		Italic = 1 << 1
	};

	MINTY_ENABLE_ENUM_OPERATORS(FontFlags)

	String to_string(FontFlags const obj);
	FontFlags parse_to_font_flags(String const& string);
	Bool parse_try_font_flags(String const& string, FontFlags& value);
	template<>
	inline FontFlags parse_to<FontFlags>(String const& string) { return parse_to_font_flags(string); }
	template<>
	inline Bool parse_try<FontFlags>(String const& string, FontFlags& value) { return parse_try_font_flags(string, value); }
}

#endif // MINTY_RENDER_FONTFLAGS_H