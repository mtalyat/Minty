#include "pch.h"
#include "CursorMode.h"

using namespace Minty;

String Minty::to_string(CursorMode const obj)
{
	switch (obj)
	{
	case CursorMode::Normal: return "Normal";
	case CursorMode::Hidden: return "Hidden";
	case CursorMode::Disabled: return "Disabled";

	default: return "";
	}
}

CursorMode Minty::parse_to_cursor_mode(String const& string)
{
	if (string == "Normal") return CursorMode::Normal;
	if (string == "Hidden") return CursorMode::Hidden;
	if (string == "Disabled") return CursorMode::Disabled;

	return CursorMode();
}

Bool Minty::parse_try_cursor_mode(String const& string, CursorMode& value)
{
	value = parse_to_cursor_mode(string);
	return true;
}