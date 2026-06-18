#include "pch.h"
#include "CursorMode.h"
#include "Core/Tool/Enum.h"

using namespace Minty;

static constexpr Size CURSORMODE_COUNT = static_cast<Size>(CursorModeEnum::Count);
static constexpr Char const* CURSORMODE_STRINGS[CURSORMODE_COUNT] = 
{ 
	"Normal", 
	"Hidden", 
	"Disabled"
};

Bool Minty::Parser<CursorModeEnum>::parse(StringView const str, CursorModeEnum &value)
{
	return Tool::try_parse_enum(str, CURSORMODE_STRINGS, CURSORMODE_COUNT, value);
}

String Minty::Parser<CursorModeEnum>::to_string(CursorModeEnum const &obj)
{
	return Tool::to_string_enum(reinterpret_cast<Size const&>(obj), CURSORMODE_STRINGS, CURSORMODE_COUNT);
}
