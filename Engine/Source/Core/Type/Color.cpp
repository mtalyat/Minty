#include "pch.h"
#include "Color.h"
#include "Core/Encoding/Encoding.h"
#include "Core/Debug/Debug.h"
#include "Core/Data/StringBuilder.h"
#include "Core/Data/Tuple.h"

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
	: a(static_cast<ChannelType>(a)), b(static_cast<ChannelType>(b)), g(static_cast<ChannelType>(g)), r(static_cast<ChannelType>(r))
{
	MINTY_ASSERT_A(r >= 0, ErrorCodeEnum::Argument_OutOfRange, static_cast<WInt>(r));
	MINTY_ASSERT_A(g >= 0, ErrorCodeEnum::Argument_OutOfRange, static_cast<WInt>(g));
	MINTY_ASSERT_A(b >= 0, ErrorCodeEnum::Argument_OutOfRange, static_cast<WInt>(b));
	MINTY_ASSERT_A(a >= 0, ErrorCodeEnum::Argument_OutOfRange, static_cast<WInt>(a));
	MINTY_ASSERT_A(r <= MAX_CHANNEL, ErrorCodeEnum::Argument_OutOfRange, static_cast<WInt>(r));
	MINTY_ASSERT_A(g <= MAX_CHANNEL, ErrorCodeEnum::Argument_OutOfRange, static_cast<WInt>(g));
	MINTY_ASSERT_A(b <= MAX_CHANNEL, ErrorCodeEnum::Argument_OutOfRange, static_cast<WInt>(b));
	MINTY_ASSERT_A(a <= MAX_CHANNEL, ErrorCodeEnum::Argument_OutOfRange, static_cast<WInt>(a));
}

Minty::Color::Color(Float const r, Float const g, Float const b, Float const a)
	: a(static_cast<ChannelType>(a * MAX_CHANNEL)), b(static_cast<ChannelType>(b * MAX_CHANNEL)), g(static_cast<ChannelType>(g * MAX_CHANNEL)), r(static_cast<ChannelType>(r * MAX_CHANNEL))
{
	MINTY_ASSERT_A(r >= 0.0f, ErrorCodeEnum::Argument_OutOfRange, static_cast<WFloat>(r));
	MINTY_ASSERT_A(g >= 0.0f, ErrorCodeEnum::Argument_OutOfRange, static_cast<WFloat>(g));
	MINTY_ASSERT_A(b >= 0.0f, ErrorCodeEnum::Argument_OutOfRange, static_cast<WFloat>(b));
	MINTY_ASSERT_A(a >= 0.0f, ErrorCodeEnum::Argument_OutOfRange, static_cast<WFloat>(a));
	MINTY_ASSERT_A(r <= 1.0f, ErrorCodeEnum::Argument_OutOfRange, static_cast<WFloat>(r));
	MINTY_ASSERT_A(g <= 1.0f, ErrorCodeEnum::Argument_OutOfRange, static_cast<WFloat>(g));
	MINTY_ASSERT_A(b <= 1.0f, ErrorCodeEnum::Argument_OutOfRange, static_cast<WFloat>(b));
	MINTY_ASSERT_A(a <= 1.0f, ErrorCodeEnum::Argument_OutOfRange, static_cast<WFloat>(a));
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

	Color::ValueType colorValue = 0;
	decode_base16(builder.get_data(), builder.get_size(), &colorValue, sizeof(Color::ValueType));
	value = Color(colorValue);
	return true;
}

String Minty::Parser<Color>::to_string(Color const &value)
{
	static constexpr Size BUFFER_SIZE = 9; // 8 characters + null terminator
	Char buffer[BUFFER_SIZE] = { 0 };
	Color::ValueType colorValue = value.value;
	encode_base16(&colorValue, sizeof(Color::ValueType), buffer, BUFFER_SIZE - 1);
	return String(buffer);
}
