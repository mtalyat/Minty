#pragma once
#include "Minty/Serialization/Parse.h"
#include "Minty/Serialization/ToString.h"

namespace Minty
{
	/// <summary>
	/// An axis on a gamepad.
	/// </summary>
	enum class GamepadAxis
	{
		LeftX = 0,
		LeftY = 1,
		RightX = 2,
		RightY = 3,
		LeftTrigger = 4,
		RightTrigger = 5,
	};

	String to_string(GamepadAxis const obj);
	GamepadAxis parse_to_gamepad_axis(String const& string);
	Bool parse_try_gamepad_axis(String const& string, GamepadAxis& value);
	template<>
	inline GamepadAxis parse_to<GamepadAxis>(String const& string) { return parse_to_gamepad_axis(string); }
	template<>
	inline Bool parse_try<GamepadAxis>(String const& string, GamepadAxis& value) { return parse_try_gamepad_axis(string, value); }
}