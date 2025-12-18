#ifndef MINTY_INPUT_GAMEPADAXIS_H
#define MINTY_INPUT_GAMEPADAXIS_H

/**
 * @file GamepadAxis.h
 * @brief Header file for gamepad axis enumeration.
 * @author Mitchell Talyat
 */

#include "Minty/Serialization/Parse.h"
#include "Minty/Serialization/ToString.h"

namespace Minty
{
	/**
	 * @brief An axis on a gamepad.
	 */
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
	inline GamepadAxis parse_to<GamepadAxis>(StringView const string) { return parse_to_gamepad_axis(string); }
	template<>
	inline Bool parse_try<GamepadAxis>(StringView const string, GamepadAxis& value) { return parse_try_gamepad_axis(string, value); }
}

#endif // MINTY_INPUT_GAMEPADAXIS_H