#include "pch.h"
#include "Conditional.h"
#include "Minty/Data/Scope.h"

using namespace Minty;

String Minty::to_string(Conditional const obj)
{
	switch (obj)
	{
	case Conditional::Equal: return "Equal";
	case Conditional::NotEqual: return "NotEqual";
	case Conditional::GreaterThan: return "GreaterThan";
	case Conditional::GreaterThanOrEqualTo: return "GreaterThanOrEqualTo";
	case Conditional::LessThan: return "LessThan";
	case Conditional::LessThanOrEqualTo: return "LessThanOrEqualTo";

	default: return "";
	}
}

Conditional Minty::parse_to_conditional(String const& string)
{
	if (string == "Equal") return Conditional::Equal;
	if (string == "NotEqual") return Conditional::NotEqual;
	if (string == "GreaterThan") return Conditional::GreaterThan;
	if (string == "GreaterThanOrEqualTo") return Conditional::GreaterThanOrEqualTo;
	if (string == "LessThan") return Conditional::LessThan;
	if (string == "LessThanOrEqualTo") return Conditional::LessThanOrEqualTo;

	return Conditional();
}

Bool Minty::parse_try_conditional(String const& string, Conditional& value)
{
	value = parse_to_conditional(string);
	return true;
}