#include "pch.h"
#include "KeyModifiers.h"

using namespace Minty;

String Minty::to_string(KeyModifiers const obj)
{
	switch (obj)
	{
	case KeyModifiers::Shift: return "Shift";
	case KeyModifiers::Control: return "Control";
	case KeyModifiers::Alt: return "Alt";
	case KeyModifiers::Super: return "Super";
	case KeyModifiers::CapsLock: return "CapsLock";
	case KeyModifiers::NumLock: return "NumLock";

	default: return "";
	}
}

KeyModifiers Minty::parse_to_key_modifiers(String const& string)
{
	if (string == "Shift") return KeyModifiers::Shift;
	if (string == "Control") return KeyModifiers::Control;
	if (string == "Alt") return KeyModifiers::Alt;
	if (string == "Super") return KeyModifiers::Super;
	if (string == "CapsLock") return KeyModifiers::CapsLock;
	if (string == "NumLock") return KeyModifiers::NumLock;

	return KeyModifiers();
}

Bool Minty::parse_try_key_modifiers(String const& string, KeyModifiers& value)
{
	value = parse_to_key_modifiers(string);
	return true;
}