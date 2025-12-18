#include "pch.h"
#include "Perspective.h"

using namespace Minty;

String Minty::to_string(Perspective const obj)
{
	switch (obj)
	{
	case Perspective::Perspective: return "Perspective";
	case Perspective::Orthographic: return "Orthographic";

	default: return "";
	}
}

Perspective Minty::parse_to_perspective(String const& string)
{
	if (string == "Perspective") return Perspective::Perspective;
	if (string == "Orthographic") return Perspective::Orthographic;

	return Perspective();
}

Bool Minty::parse_try_perspective(String const& string, Perspective& value)
{
	value = parse_to_perspective(string);
	return value != Perspective();
}