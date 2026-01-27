#include "pch.h"
#include "ShaderPolygonMode.h"
#include "Minty/Tool/Enum.h"

using namespace Minty;

static constexpr Size SHADERPOLYGONMODE_COUNT = 4;
static constexpr Char const* SHADERPOLYGONMODE_STRINGS[SHADERPOLYGONMODE_COUNT] =
{
	"Undefined",
	"Fill",
	"Line",
	"Point"
};

Bool Minty::Parser<ShaderPolygonMode>::parse(StringView const str, ShaderPolygonMode &value)
{
    return Tool::try_parse_enum(str, SHADERPOLYGONMODE_STRINGS, SHADERPOLYGONMODE_COUNT, value);
}

String Minty::Parser<ShaderPolygonMode>::to_string(ShaderPolygonMode const &obj)
{
	return Tool::to_string_enum(reinterpret_cast<Size const&>(obj), SHADERPOLYGONMODE_STRINGS, SHADERPOLYGONMODE_COUNT);
}
