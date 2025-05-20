#include "pch.h"
#include "StoreOperation.h"

using namespace Minty;

String Minty::to_string(StoreOperation const obj)
{
	switch (obj)
	{
	case StoreOperation::DontCare: return "DontCare";
	case StoreOperation::Store: return "Store";

	default: return "";
	}
}

StoreOperation Minty::parse_to_store_operation(String const& string)
{
	if (string == "DontCare") return StoreOperation::DontCare;
	if (string == "Store") return StoreOperation::Store;

	return StoreOperation();
}

Bool Minty::parse_try_store_operation(String const& string, StoreOperation& value)
{
	value = parse_to_store_operation(string);
	return value != StoreOperation();
}