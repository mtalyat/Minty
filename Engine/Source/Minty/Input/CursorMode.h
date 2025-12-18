#ifndef MINTY_INPUT_CURSORMODE_H
#define MINTY_INPUT_CURSORMODE_H

/**
 * @file CursorMode.h
 * @brief Header file for cursor mode enumeration.
 * @author Mitchell Talyat
 */

#include "Minty/Serialization/Parse.h"
#include "Minty/Serialization/ToString.h"

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

	String to_string(CursorMode const obj);
	CursorMode parse_to_cursor_mode(String const& string);
	Bool parse_try_cursor_mode(String const& string, CursorMode& value);
	template<>
	inline CursorMode parse_to<CursorMode>(StringView const string) { return parse_to_cursor_mode(string); }
	template<>
	inline Bool parse_try<CursorMode>(StringView const string, CursorMode& value) { return parse_try_cursor_mode(string, value); }
}

#endif // MINTY_INPUT_CURSORMODE_H