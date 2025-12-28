#ifndef MINTY_RENDER_FONTFLAGS_H
#define MINTY_RENDER_FONTFLAGS_H

/**
 * @file FontFlags.h
 * @brief Header file defining the FontFlags enum.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Enum.h"
#include "Minty/Serialization/Parser.h"

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
		Bold = 0x1,

		/**
		 * @brief The font is italic.
		 */
		Italic = 0x2
	};

	MINTY_ENABLE_ENUM_OPERATORS(FontFlags)

	template<>
	struct Parser<FontFlags>
	{
		static Bool parse(StringView const str, FontFlags& value);
		static String to_string(FontFlags const& obj);
	};
}

#endif // MINTY_RENDER_FONTFLAGS_H