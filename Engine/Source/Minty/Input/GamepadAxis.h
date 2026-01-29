#ifndef MINTY_INPUT_GAMEPADAXIS_H
#define MINTY_INPUT_GAMEPADAXIS_H

/**
 * @file GamepadAxis.h
 * @brief Header file for gamepad axis enumeration.
 * @author Mitchell Talyat
 */

#include "Minty/Serialization/Parser.h"

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
	
	template<>
	struct Parser<GamepadAxis>
	{
		static Bool parse(StringView const str, GamepadAxis& value);
		static String to_string(GamepadAxis const& obj);
	};
}

#endif // MINTY_INPUT_GAMEPADAXIS_H