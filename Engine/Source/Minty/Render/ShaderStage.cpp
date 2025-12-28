#include "pch.h"
#include "ShaderStage.h"
#include "Minty/Tool/Enum.h"

using namespace Minty;

static constexpr Size SHADERSTAGE_COUNT = 3;
static constexpr Char const* SHADERSTAGE_STRINGS[SHADERSTAGE_COUNT] =
{
	"Undefined",
	"Vertex",
	"Fragment"
};

Bool Minty::Parser<ShaderStage>::parse(StringView const str, ShaderStage &value)
{
    return Tool::try_parse_enum(str, SHADERSTAGE_STRINGS, SHADERSTAGE_COUNT, reinterpret_cast<Size&>(value));
}

String Minty::Parser<ShaderStage>::to_string(ShaderStage const &value)
{
	return Tool::to_string_enum(reinterpret_cast<Size const&>(value), SHADERSTAGE_STRINGS, SHADERSTAGE_COUNT);
}
