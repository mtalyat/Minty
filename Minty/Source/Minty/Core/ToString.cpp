#include "pch.h"
#include "ToString.h"
#include <sstream>

using namespace Minty;

#define MINTY_TO_STRING(value) std::stringstream ss; ss << value; return String(ss.str().c_str())

String Minty::to_string(Bool const value)
{
	return value ? "true" : "false";
}

String Minty::to_string(Char const value)
{
	Char buffer[2] = { value, '\0' };
	return String(buffer);
}

String Minty::to_string(Byte const value)
{
	MINTY_TO_STRING(value);
}

String Minty::to_string(Short const value)
{
	MINTY_TO_STRING(value);
}

String Minty::to_string(UShort const value)
{
	MINTY_TO_STRING(value);
}

String Minty::to_string(Int const value)
{
	MINTY_TO_STRING(value);
}

String Minty::to_string(UInt const value)
{
	MINTY_TO_STRING(value);
}

String Minty::to_string(Long const value)
{
	MINTY_TO_STRING(value);
}

String Minty::to_string(ULong const value)
{
	MINTY_TO_STRING(value);
}

String Minty::to_string(Float const value)
{
	MINTY_TO_STRING(value);
}

String Minty::to_string(Double const value)
{
	MINTY_TO_STRING(value);
}

#undef MINTY_TO_STRING