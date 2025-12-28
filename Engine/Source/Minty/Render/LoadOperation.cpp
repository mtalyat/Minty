#include "pch.h"
#include "LoadOperation.h"
#include "Minty/Tool/Enum.h"

using namespace Minty;

static constexpr Size LOADOPERATION_COUNT = 4;
static constexpr Char const* LOADOPERATION_STRINGS[LOADOPERATION_COUNT] =
{
	"Undefined",
	"DontCare",
	"Load",
	"Clear"
};

Bool Minty::Parser<LoadOperation>::parse(StringView const str, LoadOperation &value)
{
    return Tool::try_parse_enum(str, LOADOPERATION_STRINGS, LOADOPERATION_COUNT, reinterpret_cast<Size&>(value));
}

String Minty::Parser<LoadOperation>::to_string(LoadOperation const &obj)
{
	return Tool::to_string_enum(reinterpret_cast<Size const&>(obj), LOADOPERATION_STRINGS, LOADOPERATION_COUNT);
}