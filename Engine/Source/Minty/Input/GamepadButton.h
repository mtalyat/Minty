#ifndef MINTY_INPUT_GAMEPADBUTTON_H
#define MINTY_INPUT_GAMEPADBUTTON_H

/**
 * @file GamepadButton.h
 * @brief Header file for gamepad button enumeration.
 * @author Mitchell Talyat
 */

#include "Minty/Serialization/Parser.h"

namespace Minty
{
	/**
	 * @brief A button on a gamepad.
	 */
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
	
	template<>
	struct Parser<GamepadButton>
	{
		static Bool parse(StringView const str, GamepadButton& value);
		static String to_string(GamepadButton const& obj);
	};
}

#endif // MINTY_INPUT_GAMEPADBUTTON_H