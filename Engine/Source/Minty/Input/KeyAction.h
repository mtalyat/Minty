#ifndef MINTY_INPUT_KEYACTION_H
#define MINTY_INPUT_KEYACTION_H

/**
 * @file KeyAction.h
 * @brief Header file for key action enumeration.
 * @author Mitchell Talyat
 */

#include "Minty/Serialization/Parser.h"

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
	
	template<>
	struct Parser<KeyAction>
	{
		static Bool parse(StringView const str, KeyAction& value);
		static String to_string(KeyAction const& obj);
	};
}

#endif // MINTY_INPUT_KEYACTION_H