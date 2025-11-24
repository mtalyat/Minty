#pragma once
#include "Minty/Serialization/Parse.h"
#include "Minty/Serialization/ToString.h"

namespace Minty
{
	/// <summary>
	/// A button on the mouse.
	/// </summary>
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
	};

	String to_string(MouseButton const obj);
	MouseButton parse_to_mouse_button(String const& string);
	Bool parse_try_mouse_button(String const& string, MouseButton& value);
	template<>
	inline MouseButton parse_to<MouseButton>(String const& string) { return parse_to_mouse_button(string); }
	template<>
	inline Bool parse_try<MouseButton>(String const& string, MouseButton& value) { return parse_try_mouse_button(string, value); }
}