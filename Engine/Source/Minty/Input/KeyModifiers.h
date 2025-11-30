#ifndef MINTY_INPUT_KEYMODIFIERS_H
#define MINTY_INPUT_KEYMODIFIERS_H

/**
 * @file KeyModifiers.h
 * @brief Header file for key modifier enumeration.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Enum.h"
#include "Minty/Serialization/Parse.h"
#include "Minty/Serialization/ToString.h"

namespace Minty
{
	/**
	 * @brief The modifer keys that can be held.
	 */
	enum class KeyModifiers
	{
		Shift = 0b000001,
		Control = 0b000010,
		Alt = 0b000100,
		Super = 0b001000,
		CapsLock = 0b010000,
		NumLock = 0b100000
	};

	MINTY_ENABLE_ENUM_OPERATORS(KeyModifiers)

	String to_string(KeyModifiers const obj);
	KeyModifiers parse_to_key_modifiers(String const& string);
	Bool parse_try_key_modifiers(String const& string, KeyModifiers& value);
	template<>
	inline KeyModifiers parse_to<KeyModifiers>(String const& string) { return parse_to_key_modifiers(string); }
	template<>
	inline Bool parse_try<KeyModifiers>(String const& string, KeyModifiers& value) { return parse_try_key_modifiers(string, value); }
}

#endif // MINTY_INPUT_KEYMODIFIERS_H