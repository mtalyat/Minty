#include "pch.h"
#include "Color.h"
#include "Minty/Core/Encoding.h"
#include "Minty/Debug/Assert.h"
#include "Minty/Data/String.h"
#include "Minty/Data/StringBuilder.h"
#include "Minty/Data/Tuple.h"

using namespace Minty;

static constexpr Size COLOR_NAMED_COUNT = 8;
static constexpr Tuple<Char const*, Color> COLOR_NAMED_VALUES[COLOR_NAMED_COUNT] =
{
	{ "Black", Color::black() },
	{ "Red", Color::red() },
	{ "Green", Color::green() },
	{ "Blue", Color::blue() },
	{ "White", Color::white() },
	{ "Yellow", Color::yellow() },
	{ "Cyan", Color::cyan() },
	{ "Magenta", Color::magenta() },
};

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

Bool Minty::Parser<Color>::parse(StringView const str, Color &value)
{
	// check for named colors
    for(auto const& [name, color] : COLOR_NAMED_VALUES)
	{
		if (str == name)
		{
			value = color;
			return true;
		}
	}

	StringBuilder builder(str);

	// remove the # if it exists
	if (builder.starts_with("#"))
	{
		builder.slice(1);
	}

	// add the alpha if it is missing
	if(builder.get_size() == 6)
	{
		builder.append("ff");
	}

	// if not the correct length, stop
	if(builder.get_size() != 8)
	{
		return false;
	}

	// if not the correct characters, stop
	for(Size i = 0; i < 8; i++)
	{
		Char const c = builder.index(i);
		if((c < '0' || c > '9') && (c < 'a' || c > 'f') && (c < 'A' || c > 'F'))
		{
			return false;
		}
	}

	Color::Color_t colorValue = 0;
	decode_base16(builder.get_data(), builder.get_size(), &colorValue, sizeof(Color::Color_t));
	value = Color(colorValue);
	return true;
}
