#include "pch.h"
#include "ShaderInputRate.h"
#include "Minty/Tool/Enum.h"

using namespace Minty;

static constexpr Size SHADERINPUTRATE_COUNT = 3;
static constexpr Char const* SHADERINPUTRATE_STRINGS[SHADERINPUTRATE_COUNT] =
{
	"Undefined",
	"Vertex",
	"Instance"
};

Bool Minty::Parser<ShaderInputRate>::parse(StringView const str, ShaderInputRate &value)
{
    return Tool::try_parse_enum(str, SHADERINPUTRATE_STRINGS, SHADERINPUTRATE_COUNT, value);
}

String Minty::Parser<ShaderInputRate>::to_string(ShaderInputRate const &obj)
{
	return Tool::to_string_enum(reinterpret_cast<Size const&>(obj), SHADERINPUTRATE_STRINGS, SHADERINPUTRATE_COUNT);
}
