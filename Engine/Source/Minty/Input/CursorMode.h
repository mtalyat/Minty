#ifndef MINTY_INPUT_CURSORMODE_H
#define MINTY_INPUT_CURSORMODE_H

/**
 * @file CursorMode.h
 * @brief Header file for cursor mode enumeration.
 * @author Mitchell Talyat
 */

#include "Minty/Serialization/Parser.h"

namespace Minty
{
	/**
	 * @brief The visual state of the cursor.
	 */
	enum class CursorMode
	{
		/**
		 * @brief Normal cursor mode.
		 */
		Normal,

		/**
		 * @brief Hidden cursor mode.
		 */
		Hidden,
		
		/**
		 * @brief Disabled cursor mode.
		 */
		Disabled,
	};
	
	template<>
	struct Parser<CursorMode>
	{
		static Bool parse(StringView const str, CursorMode& value);
		static String to_string(CursorMode const& obj);
	};
}

#endif // MINTY_INPUT_CURSORMODE_H