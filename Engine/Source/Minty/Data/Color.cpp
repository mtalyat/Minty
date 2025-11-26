#include "pch.h"
#include "Color.h"
#include "Minty/Core/Encoding.h"
#include "Minty/Debug/Assert.h"

using namespace Minty;

String Minty::to_string(Color const obj)
{
	// convert to hex code
	return encode_base16(&obj.value, sizeof(Color::Color_t));
}

Color Minty::parse_to_color(String const &string)
{
	// check for common names
	if (string == "Black")
		return Color::black();
	else if (string == "Red")
		return Color::red();
	else if (string == "Green")
		return Color::green();
	else if (string == "Blue")
		return Color::blue();
	else if (string == "White")
		return Color::white();
	else if (string == "Yellow")
		return Color::yellow();
	else if (string == "Cyan")
		return Color::cyan();
	else if (string == "Magenta")
		return Color::magenta();

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

	MINTY_ASSERT(str.get_size() == 8, ErrorCode::Argument_InvalidFormat, string);

	Color::Color_t value = 0;
	decode_base16(str, &value, sizeof(Color::Color_t));
	return Color(value);
}

Bool Minty::parse_try_color(String const &string, Color &value)
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

Minty::Color::Color(Int const r, Int const g, Int const b, Int const a)
	: a(static_cast<Channel_t>(a)), b(static_cast<Channel_t>(b)), g(static_cast<Channel_t>(g)), r(static_cast<Channel_t>(r))
{
	MINTY_ASSERT(r >= 0, ErrorCode::Argument_OutOfBounds, r);
	MINTY_ASSERT(g >= 0, ErrorCode::Argument_OutOfBounds, g);
	MINTY_ASSERT(b >= 0, ErrorCode::Argument_OutOfBounds, b);
	MINTY_ASSERT(a >= 0, ErrorCode::Argument_OutOfBounds, a);
	MINTY_ASSERT(r <= MAX_CHANNEL, ErrorCode::Argument_OutOfBounds, r);
	MINTY_ASSERT(g <= MAX_CHANNEL, ErrorCode::Argument_OutOfBounds, g);
	MINTY_ASSERT(b <= MAX_CHANNEL, ErrorCode::Argument_OutOfBounds, b);
	MINTY_ASSERT(a <= MAX_CHANNEL, ErrorCode::Argument_OutOfBounds, a);
}

Minty::Color::Color(Float const r, Float const g, Float const b, Float const a)
	: a(static_cast<Channel_t>(a * MAX_CHANNEL)), b(static_cast<Channel_t>(b * MAX_CHANNEL)), g(static_cast<Channel_t>(g * MAX_CHANNEL)), r(static_cast<Channel_t>(r * MAX_CHANNEL))
{
	MINTY_ASSERT(r >= 0.0f, ErrorCode::Argument_OutOfBounds, r);
	MINTY_ASSERT(g >= 0.0f, ErrorCode::Argument_OutOfBounds, g);
	MINTY_ASSERT(b >= 0.0f, ErrorCode::Argument_OutOfBounds, b);
	MINTY_ASSERT(a >= 0.0f, ErrorCode::Argument_OutOfBounds, a);
	MINTY_ASSERT(r <= 1.0f, ErrorCode::Argument_OutOfBounds, r);
	MINTY_ASSERT(g <= 1.0f, ErrorCode::Argument_OutOfBounds, g);
	MINTY_ASSERT(b <= 1.0f, ErrorCode::Argument_OutOfBounds, b);
	MINTY_ASSERT(a <= 1.0f, ErrorCode::Argument_OutOfBounds, a);
}