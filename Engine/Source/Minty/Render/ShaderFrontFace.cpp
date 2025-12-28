#include "pch.h"
#include "ShaderFrontFace.h"
#include "Minty/Tool/Enum.h"

using namespace Minty;

static constexpr Size SHADERFRONTFACE_COUNT = 3;
static constexpr Char const* SHADERFRONTFACE_STRINGS[SHADERFRONTFACE_COUNT] =
{
	"Undefined",
	"CounterClockwise",
	"Clockwise"
};

Bool Minty::Parser<ShaderFrontFace>::parse(StringView const str, ShaderFrontFace &value)
{
    return Tool::try_parse_enum(str, SHADERFRONTFACE_STRINGS, SHADERFRONTFACE_COUNT, reinterpret_cast<Size&>(value));
}

String Minty::Parser<ShaderFrontFace>::to_string(ShaderFrontFace const &obj)
{
	return Tool::to_string_enum(reinterpret_cast<Size const&>(obj), SHADERFRONTFACE_STRINGS, SHADERFRONTFACE_COUNT);
}
