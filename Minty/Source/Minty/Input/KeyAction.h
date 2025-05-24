#pragma once
#include "Minty/Serialization/Parse.h"
#include "Minty/Serialization/ToString.h"

namespace Minty
{
	/// <summary>
	/// The state of a key or button.
	/// </summary>
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
	inline KeyAction parse_to<KeyAction>(String const& string) { return parse_to_key_action(string); }
	template<>
	inline Bool parse_try<KeyAction>(String const& string, KeyAction& value) { return parse_try_key_action(string, value); }
}