#ifndef MINTY_INPUT_KEYMODIFIERS_H
#define MINTY_INPUT_KEYMODIFIERS_H

/**
 * @file KeyModifiers.h
 * @brief Header file for key modifier enumeration.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Enum.h"
#include "Minty/Serialization/Parser.h"

namespace Minty
{
	/**
	 * @brief The modifer keys that can be held.
	 */
	enum class KeyModifiers
	{
		/**
		 * @brief No modifier keys are held.
		 */
		None = 0x0,

		/**
		 * @brief The Shift key is held.
		 */
		Shift = 0x1,

		/**
		 * @brief The Control key is held.
		 */
		Control = 0x2,

		/**
		 * @brief The Alt key is held.
		 */
		Alt = 0x4,

		/**
		 * @brief The Super (Windows/Command) key is held.
		 */
		Super = 0x8,

		/**
		 * @brief The Caps Lock key is active.
		 */
		CapsLock = 0x10,

		/**
		 * @brief The Num Lock key is active.
		 */
		NumLock = 0x20
	};

	MINTY_ENABLE_ENUM_OPERATORS(KeyModifiers)
	
	template<>
	struct Parser<KeyModifiers>
	{
		static Bool parse(StringView const str, KeyModifiers& value);
		static String to_string(KeyModifiers const& obj);
	};
}

#endif // MINTY_INPUT_KEYMODIFIERS_H