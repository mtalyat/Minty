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
	case Conditional::GreaterThanOrEqual: return "GreaterThanOrEqual";
	case Conditional::LessThan: return "LessThan";
	case Conditional::LessThanOrEqual: return "LessThanOrEqual";

	default: return "";
	}
}

Conditional Minty::parse_to_conditional(String const& string)
{
	if (string == "==") return Conditional::Equal;
	if (string == "!=") return Conditional::NotEqual;
	if (string == ">") return Conditional::GreaterThan;
	if (string == ">=") return Conditional::GreaterThanOrEqual;
	if (string == "<") return Conditional::LessThan;
	if (string == "<=") return Conditional::LessThanOrEqual;
	if (string == "Equal") return Conditional::Equal;
	if (string == "NotEqual") return Conditional::NotEqual;
	if (string == "GreaterThan") return Conditional::GreaterThan;
	if (string == "GreaterThanOrEqual") return Conditional::GreaterThanOrEqual;
	if (string == "LessThan") return Conditional::LessThan;
	if (string == "LessThanOrEqual") return Conditional::LessThanOrEqual;

	return Conditional();
}

Bool Minty::parse_try_conditional(String const& string, Conditional& value)
{
	value = parse_to_conditional(string);
	return true;
}