#ifndef MINTY_INPUT_KEYACTION_H
#define MINTY_INPUT_KEYACTION_H

/**
 * @file KeyAction.h
 * @brief Header file for key action enumeration.
 * @author Mitchell Talyat
 */

#include "Minty/Serialization/Parse.h"
#include "Minty/Serialization/ToString.h"

namespace Minty
{
	/**
	 * @brief The state of a key or button.
	 */
	enum class KeyAction
	{
		Up = 0,
		Down = 1,
		Hold = 2
	};

	String to_string(KeyAction const obj);
	KeyAction parse_to_key_action(String const& string);
	Bool parse_try_key_action(String const& string, KeyAction& value);
	template<>
	inline KeyAction parse_to<KeyAction>(StringView const string) { return parse_to_key_action(string); }
	template<>
	inline Bool parse_try<KeyAction>(StringView const string, KeyAction& value) { return parse_try_key_action(string, value); }
}

#endif // MINTY_INPUT_KEYACTION_H