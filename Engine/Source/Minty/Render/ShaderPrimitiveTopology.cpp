#include "pch.h"
#include "ShaderPrimitiveTopology.h"
#include "Minty/Tool/Enum.h"

using namespace Minty;

static constexpr Size SHADERPRIMITIVETOPOLOGY_COUNT = 7;
static constexpr Char const* SHADERPRIMITIVETOPOLOGY_STRINGS[SHADERPRIMITIVETOPOLOGY_COUNT] =
{
	"Undefined",
	"PointList",
	"LineList",
	"LineStrip",
	"TriangleList",
	"TriangleStrip",
	"TriangleFan"
};

Bool Minty::Parser<ShaderPrimitiveTopology>::parse(StringView const str, ShaderPrimitiveTopology &value)
{
    return Tool::try_parse_enum(str, SHADERPRIMITIVETOPOLOGY_STRINGS, SHADERPRIMITIVETOPOLOGY_COUNT, reinterpret_cast<Size&>(value));
}

String Minty::Parser<ShaderPrimitiveTopology>::to_string(ShaderPrimitiveTopology const &obj)
{
	return Tool::to_string_enum(reinterpret_cast<Size const&>(obj), SHADERPRIMITIVETOPOLOGY_STRINGS, SHADERPRIMITIVETOPOLOGY_COUNT);
}