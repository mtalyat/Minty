#ifndef MINTY_INPUT_MOUSEBUTTON_H
#define MINTY_INPUT_MOUSEBUTTON_H

/**
 * @file MouseButton.h
 * @brief Header file for mouse button enumeration.
 * @author Mitchell Talyat
 */

#include "Minty/Serialization/Parser.h"

namespace Minty
{
	/**
	 * @brief A button on the mouse.
	 */
	enum class MouseButton
	{
		Button1 = 0,
		Button2 = 1,
		Button3 = 2,
		Button4 = 3,
		Button5 = 4,
		Button6 = 5,
		Button7 = 6,
		Button8 = 7,

		Left = Button1,
		Right = Button2,
		Middle = Button3,
		X1 = Button4,
		X2 = Button5
	};
	
	template<>
	struct Parser<MouseButton>
	{
		static Bool parse(StringView const str, MouseButton& value);
		static String to_string(MouseButton const& obj);
	};
}

#endif // MINTY_INPUT_MOUSEBUTTON_H