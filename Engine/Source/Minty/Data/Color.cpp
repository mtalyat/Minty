#include "pch.h"
#include "Color.h"
#include "Minty/Core/Encoding.h"
#include "Minty/Debug/Assert.h"
#include "Minty/Data/String.h"
#include "Minty/Data/StringBuilder.h"

using namespace Minty;

String Minty::to_string(Color const obj)
{
	// convert to hex code
	Char buffer[9] = { 0 };
	encode_base16(&obj.value, sizeof(Color::Color_t), buffer, 8);
	return String(buffer);
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

	StringBuilder builder(string);
	if (builder.starts_with("#"))
	{
		// remove #
		builder.slice(1, builder.get_size() - 1);
	}

	// if string is 6 characters, add ff for alpha
	if (builder.get_size() == 6)
	{
		// add ff for alpha
		builder.append("ff");
	}

	MINTY_ASSERT_F(builder.get_size() == 8, ErrorCode::Argument_InvalidFormat, string);

	Color::Color_t value = 0;
	decode_base16(builder.get_data(), builder.get_size(), &value, sizeof(Color::Color_t));
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
	StringBuilder builder(string);
	if (builder.get_size() == 6)
	{
		// add ff for alpha
		builder.append("ff");
	}

	// ensure the string is valid
	if (builder.get_size() != 8)
	{
		// not the correct number of characters
		return false;
	}

	Color::Color_t color = 0;
	decode_base16(builder.get_data(), builder.get_size(), &color, sizeof(Color::Color_t));
	value = Color(color);
	return true;
}

Minty::Color::Color(Int const r, Int const g, Int const b, Int const a)
	: a(static_cast<Channel_t>(a)), b(static_cast<Channel_t>(b)), g(static_cast<Channel_t>(g)), r(static_cast<Channel_t>(r))
{
	MINTY_ASSERT_F(r >= 0, ErrorCode::Argument_OutOfRange, r);
	MINTY_ASSERT_F(g >= 0, ErrorCode::Argument_OutOfRange, g);
	MINTY_ASSERT_F(b >= 0, ErrorCode::Argument_OutOfRange, b);
	MINTY_ASSERT_F(a >= 0, ErrorCode::Argument_OutOfRange, a);
	MINTY_ASSERT_F(r <= MAX_CHANNEL, ErrorCode::Argument_OutOfRange, r);
	MINTY_ASSERT_F(g <= MAX_CHANNEL, ErrorCode::Argument_OutOfRange, g);
	MINTY_ASSERT_F(b <= MAX_CHANNEL, ErrorCode::Argument_OutOfRange, b);
	MINTY_ASSERT_F(a <= MAX_CHANNEL, ErrorCode::Argument_OutOfRange, a);
}

Minty::Color::Color(Float const r, Float const g, Float const b, Float const a)
	: a(static_cast<Channel_t>(a * MAX_CHANNEL)), b(static_cast<Channel_t>(b * MAX_CHANNEL)), g(static_cast<Channel_t>(g * MAX_CHANNEL)), r(static_cast<Channel_t>(r * MAX_CHANNEL))
{
	MINTY_ASSERT_F(r >= 0.0f, ErrorCode::Argument_OutOfRange, r);
	MINTY_ASSERT_F(g >= 0.0f, ErrorCode::Argument_OutOfRange, g);
	MINTY_ASSERT_F(b >= 0.0f, ErrorCode::Argument_OutOfRange, b);
	MINTY_ASSERT_F(a >= 0.0f, ErrorCode::Argument_OutOfRange, a);
	MINTY_ASSERT_F(r <= 1.0f, ErrorCode::Argument_OutOfRange, r);
	MINTY_ASSERT_F(g <= 1.0f, ErrorCode::Argument_OutOfRange, g);
	MINTY_ASSERT_F(b <= 1.0f, ErrorCode::Argument_OutOfRange, b);
	MINTY_ASSERT_F(a <= 1.0f, ErrorCode::Argument_OutOfRange, a);
}