#include "pch.h"
#include "LoadOperation.h"

using namespace Minty;

String Minty::to_string(LoadOperation const obj)
{
	switch (obj)
	{
	case LoadOperation::DontCare: return "DontCare";
	case LoadOperation::Load: return "Load";
	case LoadOperation::Clear: return "Clear";

	default: return "";
	}
}

LoadOperation Minty::parse_to_load_operation(String const& string)
{
	if (string == "DontCare") return LoadOperation::DontCare;
	if (string == "Load") return LoadOperation::Load;
	if (string == "Clear") return LoadOperation::Clear;

	return LoadOperation();
}

Bool Minty::parse_try_load_operation(String const& string, LoadOperation& value)
{
	value = parse_to_load_operation(string);
	return value != LoadOperation();
}