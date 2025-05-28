#pragma once
#include "Minty/Core/Macro.h"
#include "Minty/Serialization/Parse.h"
#include "Minty/Serialization/ToString.h"

namespace Minty
{
	/// <summary>
	/// Defines the flags that can be applied to a font.
	/// </summary>
	enum class FontFlags
	{
		/// <summary>
		/// The font is regular, with no special styling.
		/// </summary>
		None = 0,

		/// <summary>
		/// The font is bold.
		/// </summary>
		Bold = 1 << 0,

		/// <summary>
		/// The font is italic.
		/// </summary>
		Italic = 1 << 1
	};

	MINTY_ENUM_FLAGS_OPERATORS(FontFlags)

	String to_string(FontFlags const obj);
	FontFlags parse_to_font_flags(String const& string);
	Bool parse_try_font_flags(String const& string, FontFlags& value);
	template<>
	inline FontFlags parse_to<FontFlags>(String const& string) { return parse_to_font_flags(string); }
	template<>
	inline Bool parse_try<FontFlags>(String const& string, FontFlags& value) { return parse_try_font_flags(string, value); }
}