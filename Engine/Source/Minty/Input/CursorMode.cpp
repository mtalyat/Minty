#include "pch.h"
#include "CursorMode.h"
#include "Minty/Tool/Enum.h"

using namespace Minty;

static constexpr Size CURSORMODE_COUNT = 3;
static constexpr Char const* CURSORMODE_STRINGS[CURSORMODE_COUNT] = 
{ 
	"Normal", 
	"Hidden", 
	"Disabled"
};

Bool Minty::Parser<CursorMode>::parse(StringView const str, CursorMode &value)
{
	return Tool::try_parse_enum(str, CURSORMODE_STRINGS, CURSORMODE_COUNT, reinterpret_cast<Size&>(value));
}

String Minty::Parser<CursorMode>::to_string(CursorMode const &obj)
{
	return Tool::to_string_enum(reinterpret_cast<Size const&>(obj), CURSORMODE_STRINGS, CURSORMODE_COUNT);
}
