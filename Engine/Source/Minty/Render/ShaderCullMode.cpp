#include "pch.h"
#include "ShaderCullMode.h"
#include "Minty/Tool/Enum.h"

using namespace Minty;

static constexpr Size SHADERCULLMODE_COUNT = 5;
static constexpr Char const* SHADERCULLMODE_STRINGS[SHADERCULLMODE_COUNT] =
{
	"Undefined",
	"None",
	"Front",
	"Back",
	"Both"
};

Bool Minty::Parser<ShaderCullMode>::parse(StringView const str, ShaderCullMode &value)
{
    return Tool::try_parse_enum(str, SHADERCULLMODE_STRINGS, SHADERCULLMODE_COUNT, reinterpret_cast<Size&>(value));
}

String Minty::Parser<ShaderCullMode>::to_string(ShaderCullMode const &obj)
{
	return Tool::to_string_enum(reinterpret_cast<Size const&>(obj), SHADERCULLMODE_STRINGS, SHADERCULLMODE_COUNT);
}