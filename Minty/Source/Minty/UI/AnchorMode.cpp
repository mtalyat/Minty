#include "pch.h"
#include "AnchorMode.h"

using namespace Minty;

String Minty::to_string(AnchorMode const obj)
{
	// special cases
    switch (obj)
    {
	case AnchorMode::Empty: return "Empty";
	case AnchorMode::All: return "All";
    }

	// default case
    String result = "";
	if (static_cast<Bool>(obj & AnchorMode::Top)) result += "Top";
	if (static_cast<Bool>(obj & AnchorMode::Middle)) result += "Middle";
	if (static_cast<Bool>(obj & AnchorMode::Bottom)) result += "Bottom";
	if (static_cast<Bool>(obj & AnchorMode::Left)) result += "Left";
	if (static_cast<Bool>(obj & AnchorMode::Center)) result += "Center";
	if (static_cast<Bool>(obj & AnchorMode::Right)) result += "Right";
	return result;
}

AnchorMode Minty::parse_to_anchor_mode(String const& string)
{
	// special cases
	if (string == "Empty") return AnchorMode::Empty;
	if (string == "All") return AnchorMode::All;

	// default case
	AnchorMode result = AnchorMode::Empty;
	if (string.contains("Top")) result |= AnchorMode::Top;
	if (string.contains("Middle")) result |= AnchorMode::Middle;
	if (string.contains("Bottom")) result |= AnchorMode::Bottom;
	if (string.contains("Left")) result |= AnchorMode::Left;
	if (string.contains("Center")) result |= AnchorMode::Center;
	if (string.contains("Right")) result |= AnchorMode::Right;
	return result;
}

Bool Minty::parse_try_anchor_mode(String const& string, AnchorMode& value)
{
	value = parse_to_anchor_mode(string);
	return string == "Empty" || value != AnchorMode::Empty;
}
