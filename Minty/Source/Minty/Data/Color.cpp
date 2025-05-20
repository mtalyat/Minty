#include "pch.h"
#include "Color.h"
#include "Minty/Core/Encoding.h"

using namespace Minty;

String Minty::to_string(Color const obj)
{
	// convert to hex code
	return encode_base16(&obj.value, sizeof(Color::Color_t));
}

Color Minty::parse_to_color(String const& string)
{
	if (string.starts_with("#"))
	{
		// remove #
		return parse_to_color(string.sub(1, string.get_size() - 1));
	}

	Color::Color_t value = 0;
	decode_base16(string, &value, sizeof(Color::Color_t));
	return Color(value);
}

Bool Minty::parse_try_color(String const& string, Color& value)
{
	if (string.starts_with("#"))
	{
		// remove #
		return parse_try_color(string.sub(1, string.get_size() - 1), value);
	}

	// ensure the string is valid
	if (string.get_size() != 8)
	{
		// not the correct number of characters
		return false;
	}

	Color::Color_t color = 0;
	decode_base16(string, &color, sizeof(Color::Color_t));
	value = Color(color);
	return true;
}
