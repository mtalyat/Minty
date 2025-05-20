#pragma once
#include "Minty/Serialization/Parse.h"
#include "Minty/Serialization/ToString.h"

namespace Minty
{
	/// <summary>
	/// The visual state of the cursor.
	/// </summary>
	enum class CursorMode
	{
		Normal,
		Hidden,
		Disabled,
	};

	String to_string(CursorMode const obj);
	CursorMode parse_to_cursor_mode(String const& string);
	Bool parse_try_cursor_mode(String const& string, CursorMode& value);
	template<>
	inline CursorMode parse_to<CursorMode>(String const& string) { return parse_to_cursor_mode(string); }
	template<>
	inline Bool parse_try<CursorMode>(String const& string, CursorMode& value) { return parse_try_cursor_mode(string, value); }
}