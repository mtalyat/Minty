#include "pch.h"
#include "MouseButton.h"

using namespace Minty;

String Minty::to_string(MouseButton const obj)
{
	switch (obj)
	{
	case MouseButton::Button1: return "Button1";
	case MouseButton::Button2: return "Button2";
	case MouseButton::Button3: return "Button3";
	case MouseButton::Button4: return "Button4";
	case MouseButton::Button5: return "Button5";
	case MouseButton::Button6: return "Button6";
	case MouseButton::Button7: return "Button7";
	case MouseButton::Button8: return "Button8";

	default: return "";
	}
}

MouseButton Minty::parse_to_mouse_button(String const& string)
{
	if (string == "Button1") return MouseButton::Button1;
	if (string == "Button2") return MouseButton::Button2;
	if (string == "Button3") return MouseButton::Button3;
	if (string == "Button4") return MouseButton::Button4;
	if (string == "Button5") return MouseButton::Button5;
	if (string == "Button6") return MouseButton::Button6;
	if (string == "Button7") return MouseButton::Button7;
	if (string == "Button8") return MouseButton::Button8;
	if (string == "Left") return MouseButton::Left;
	if (string == "Right") return MouseButton::Right;
	if (string == "Middle") return MouseButton::Middle;

	return MouseButton();
}

Bool Minty::parse_try_mouse_button(String const& string, MouseButton& value)
{
	value = parse_to_mouse_button(string);
	return true;
}