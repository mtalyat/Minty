#include "pch.h"
#include "Filter.h"

using namespace Minty;

String Minty::to_string(Filter const obj)
{
	switch (obj)
	{
	case Filter::Nearest: return "Nearest";
	case Filter::Linear: return "Linear";

	default: return "";
	}
}

Filter Minty::parse_to_filter(String const& string)
{
	if (string == "Nearest") return Filter::Nearest;
	if (string == "Linear") return Filter::Linear;

	return Filter();
}

Bool Minty::parse_try_filter(String const& string, Filter& value)
{
	value = parse_to_filter(string);
	return value != Filter();
}