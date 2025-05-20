#include "pch.h"
#include "AddressMode.h"

using namespace Minty;

String Minty::to_string(AddressMode const obj)
{
	switch (obj)
	{
	case AddressMode::Repeat: return "Repeat";
	case AddressMode::MirroredRepeat: return "MirroredRepeat";
	case AddressMode::ClampToEdge: return "ClampToEdge";
	case AddressMode::ClampToBorder: return "ClampToBorder";
	case AddressMode::MirroredClampToEdge: return "MirroredClampToEdge";

	default: return "";
	}
}

AddressMode Minty::parse_to_address_mode(String const& string)
{
	if (string == "Repeat") return AddressMode::Repeat;
	if (string == "MirroredRepeat") return AddressMode::MirroredRepeat;
	if (string == "ClampToEdge") return AddressMode::ClampToEdge;
	if (string == "ClampToBorder") return AddressMode::ClampToBorder;
	if (string == "MirroredClampToEdge") return AddressMode::MirroredClampToEdge;

	return AddressMode();
}

Bool Minty::parse_try_address_mode(String const& string, AddressMode& value)
{
	value = parse_to_address_mode(string);
	return value != AddressMode();
}