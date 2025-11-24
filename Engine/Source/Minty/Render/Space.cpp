#include "pch.h"
#include "Space.h"

using namespace Minty;

String Minty::to_string(Space const obj)
{
	switch (obj)
	{
	case Space::D3: return "D3";
	case Space::D2: return "D2";
	case Space::UI: return "UI";

	default: return "";
	}
}

Space Minty::parse_to_space(String const& string)
{
	if (string == "D3") return Space::D3;
	if (string == "D2") return Space::D2;
	if (string == "UI") return Space::UI;

	return Space();
}

Bool Minty::parse_try_space(String const& string, Space& value)
{
	value = parse_to_space(string);
	return true;
}