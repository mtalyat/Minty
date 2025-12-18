#include "pch.h"
#include "KeyAction.h"

using namespace Minty;

String Minty::to_string(KeyAction const obj)
{
	switch (obj)
	{
	case KeyAction::Up: return "Up";
	case KeyAction::Down: return "Down";
	case KeyAction::Hold: return "Hold";

	default: return "";
	}
}

KeyAction Minty::parse_to_key_action(String const& string)
{
	if (string == "Up") return KeyAction::Up;
	if (string == "Down") return KeyAction::Down;
	if (string == "Hold") return KeyAction::Hold;

	return KeyAction();
}

Bool Minty::parse_try_key_action(String const& string, KeyAction& value)
{
	value = parse_to_key_action(string);
	return true;
}