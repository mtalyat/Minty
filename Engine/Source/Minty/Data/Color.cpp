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
	// check for common names
    if (string == "Black") return Color::black();
    else if (string == "Red") return Color::red();
    else if (string == "Green") return Color::green();
    else if (string == "Blue") return Color::blue();
    else if (string == "White") return Color::white();
    else if (string == "Yellow") return Color::yellow();
    else if (string == "Cyan") return Color::cyan();
    else if (string == "Magenta") return Color::magenta();

	String str = string;
	if (str.starts_with("#"))
	{
		// remove #
		str = str.sub(1, str.get_size() - 1);
	}

	// if string is 6 characters, add ff for alpha
	if (str.get_size() == 6)
	{
		// add ff for alpha
		str.append("ff");
	}

	MINTY_ASSERT(str.get_size() == 8, "Color string must be 8 hexadecimal characters long (or 6 without alpha).");

	Color::Color_t value = 0;
	decode_base16(str, &value, sizeof(Color::Color_t));
	return Color(value);
}

Bool Minty::parse_try_color(String const& string, Color& value)
{
	if (string.starts_with("#"))
	{
		// remove #
		return parse_try_color(string.sub(1, string.get_size() - 1), value);
	}

	// if string is 6 characters, add ff for alpha
	String str = string;
	if (str.get_size() == 6)
	{
		// add ff for alpha
		str.append("ff");
	}

	// ensure the string is valid
	if (str.get_size() != 8)
	{
		// not the correct number of characters
		return false;
	}

	Color::Color_t color = 0;
	decode_base16(str, &color, sizeof(Color::Color_t));
	value = Color(color);
	return true;
}
