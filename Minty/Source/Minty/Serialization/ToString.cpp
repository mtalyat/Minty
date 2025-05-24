#include "pch.h"
#include "ToString.h"
#include <sstream>

using namespace Minty;

#define MINTY_TO_STRING_1(value) std::stringstream ss; ss << value; return String(ss.str().c_str())
#define MINTY_TO_STRING_2(value0, value1) std::stringstream ss; ss << "(" << to_string(value0) << ", " << to_string(value1) << ")"; return String(ss.str().c_str())
#define MINTY_TO_STRING_3(value0, value1, value2) std::stringstream ss; ss << "(" << to_string(value0) << ", " << to_string(value1) << ", " << to_string(value2) << ")"; return String(ss.str().c_str())
#define MINTY_TO_STRING_4(value0, value1, value2, value3) std::stringstream ss; ss << "(" << to_string(value0) << ", " << to_string(value1) << ", " << to_string(value2) << ", " << to_string(value3) << ")"; return String(ss.str().c_str())

String Minty::to_string(Bool const value)
{
	return value ? "T" : "F";
}

String Minty::to_string(Bool2 const& value)
{
	MINTY_TO_STRING_2(value.x, value.y);
}

String Minty::to_string(Bool3 const& value)
{
	MINTY_TO_STRING_3(value.x, value.y, value.z);
}

String Minty::to_string(Bool4 const& value)
{
	MINTY_TO_STRING_4(value.x, value.y, value.z, value.w);
}

String Minty::to_string(Char const value)
{
	Char buffer[2] = { value, '\0' };
	return String(buffer);
}

String Minty::to_string(Char const* const value)
{
	return String(value);
}

String Minty::to_string(Byte const value)
{
	MINTY_TO_STRING_1(static_cast<UInt>(value));
}

String Minty::to_string(Short const value)
{
	MINTY_TO_STRING_1(value);
}

String Minty::to_string(UShort const value)
{
	MINTY_TO_STRING_1(value);
}

String Minty::to_string(Int const value)
{
	MINTY_TO_STRING_1(value);
}

String Minty::to_string(Int2 const& value)
{
	MINTY_TO_STRING_2(value.x, value.y);
}

String Minty::to_string(Int3 const& value)
{
	MINTY_TO_STRING_3(value.x, value.y, value.z);
}

String Minty::to_string(Int4 const& value)
{
	MINTY_TO_STRING_4(value.x, value.y, value.z, value.w);
}

String Minty::to_string(UInt const value)
{
	MINTY_TO_STRING_1(value);
}

String Minty::to_string(UInt2 const& value)
{
	MINTY_TO_STRING_2(value.x, value.y);
}

String Minty::to_string(UInt3 const& value)
{
	MINTY_TO_STRING_3(value.x, value.y, value.z);
}

String Minty::to_string(UInt4 const& value)
{
	MINTY_TO_STRING_4(value.x, value.y, value.z, value.w);
}

String Minty::to_string(Long const value)
{
	MINTY_TO_STRING_1(value);
}

String Minty::to_string(ULong const value)
{
	MINTY_TO_STRING_1(value);
}

static String remove_trailing_zeros(std::string const& string)
{
	std::string result = string;
	if (result.find('.') != std::string::npos) {
		// remove trailing zeros
		result.erase(result.find_last_not_of('0') + 1);
		// remove decimal point if at end
		if (result.back() == '.')
		{
			result.pop_back();
		}
	}
	return String(result.c_str());
}

String Minty::to_string(Float const value)
{
	std::ostringstream stream;
	stream << value;
	return remove_trailing_zeros(stream.str());
}

String Minty::to_string(Float2 const& value)
{
	MINTY_TO_STRING_2(value.x, value.y);
}

String Minty::to_string(Float3 const& value)
{
	MINTY_TO_STRING_3(value.x, value.y, value.z);
}

String Minty::to_string(Float4 const& value)
{
	MINTY_TO_STRING_4(value.x, value.y, value.z, value.w);
}

String Minty::to_string(Double const value)
{
	std::ostringstream stream;
	stream << value;
	return remove_trailing_zeros(stream.str());
}

String Minty::to_string(String const& value)
{
	return value;
}

#undef MINTY_TO_STRING_1
#undef MINTY_TO_STRING_2
#undef MINTY_TO_STRING_3
#undef MINTY_TO_STRING_4