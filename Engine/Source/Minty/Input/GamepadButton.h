#pragma once
#include "Minty/Serialization/Parse.h"
#include "Minty/Serialization/ToString.h"

namespace Minty
{
	/// <summary>
	/// A button on a gamepad.
	/// </summary>
	enum class GamepadButton
	{
		ButtonSouth = 0,
		ButtonEast = 1,
		ButtonWest = 2,
		ButtonNorth = 3,
		LeftBumper = 4,
		RightBumper = 5,
		Back = 6,
		Start = 7,
		Home = 8,
		LeftThumb = 9,
		RightThumb = 10,
		DpadUp = 11,
		DpadRight = 12,
		DpadDown = 13,
		DpadLeft = 14,
	};

	String to_string(GamepadButton const obj);
	GamepadButton parse_to_gamepad_button(String const& string);
	Bool parse_try_gamepad_button(String const& string, GamepadButton& value);
	template<>
	inline GamepadButton parse_to<GamepadButton>(String const& string) { return parse_to_gamepad_button(string); }
	template<>
	inline Bool parse_try<GamepadButton>(String const& string, GamepadButton& value) { return parse_try_gamepad_button(string, value); }
}