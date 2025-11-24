#include "pch.h"
#include "GamepadAxis.h"

using namespace Minty;

String Minty::to_string(GamepadAxis const obj)
{
	switch (obj)
	{
	case GamepadAxis::LeftX: return "LeftX";
	case GamepadAxis::LeftY: return "LeftY";
	case GamepadAxis::RightX: return "RightX";
	case GamepadAxis::RightY: return "RightY";
	case GamepadAxis::LeftTrigger: return "LeftTrigger";
	case GamepadAxis::RightTrigger: return "RightTrigger";

	default: return "";
	}
}

GamepadAxis Minty::parse_to_gamepad_axis(String const& string)
{
	if (string == "LeftX") return GamepadAxis::LeftX;
	if (string == "LeftY") return GamepadAxis::LeftY;
	if (string == "RightX") return GamepadAxis::RightX;
	if (string == "RightY") return GamepadAxis::RightY;
	if (string == "LeftTrigger") return GamepadAxis::LeftTrigger;
	if (string == "RightTrigger") return GamepadAxis::RightTrigger;

	return GamepadAxis();
}

Bool Minty::parse_try_gamepad_axis(String const& string, GamepadAxis& value)
{
	value = parse_to_gamepad_axis(string);
	return true;
}