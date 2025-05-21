#include "pch.h"
#include "GamepadButton.h"

using namespace Minty;

String Minty::to_string(GamepadButton const obj)
{
	switch (obj)
	{
	case GamepadButton::ButtonSouth: return "ButtonSouth";
	case GamepadButton::ButtonEast: return "ButtonEast";
	case GamepadButton::ButtonWest: return "ButtonWest";
	case GamepadButton::ButtonNorth: return "ButtonNorth";
	case GamepadButton::LeftBumper: return "LeftBumper";
	case GamepadButton::RightBumper: return "RightBumper";
	case GamepadButton::Back: return "Back";
	case GamepadButton::Start: return "Start";
	case GamepadButton::Home: return "Home";
	case GamepadButton::LeftThumb: return "LeftThumb";
	case GamepadButton::RightThumb: return "RightThumb";
	case GamepadButton::DpadUp: return "DpadUp";
	case GamepadButton::DpadRight: return "DpadRight";
	case GamepadButton::DpadDown: return "DpadDown";
	case GamepadButton::DpadLeft: return "DpadLeft";

	default: return "";
	}
}

GamepadButton Minty::parse_to_gamepad_button(String const& string)
{
	if (string == "ButtonSouth") return GamepadButton::ButtonSouth;
	if (string == "ButtonEast") return GamepadButton::ButtonEast;
	if (string == "ButtonWest") return GamepadButton::ButtonWest;
	if (string == "ButtonNorth") return GamepadButton::ButtonNorth;
	if (string == "LeftBumper") return GamepadButton::LeftBumper;
	if (string == "RightBumper") return GamepadButton::RightBumper;
	if (string == "Back") return GamepadButton::Back;
	if (string == "Start") return GamepadButton::Start;
	if (string == "Home") return GamepadButton::Home;
	if (string == "LeftThumb") return GamepadButton::LeftThumb;
	if (string == "RightThumb") return GamepadButton::RightThumb;
	if (string == "DpadUp") return GamepadButton::DpadUp;
	if (string == "DpadRight") return GamepadButton::DpadRight;
	if (string == "DpadDown") return GamepadButton::DpadDown;
	if (string == "DpadLeft") return GamepadButton::DpadLeft;

	return GamepadButton();
}

Bool Minty::parse_try_gamepad_button(String const& string, GamepadButton& value)
{
	value = parse_to_gamepad_button(string);
	return true;
}
