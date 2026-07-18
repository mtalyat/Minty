#include "pch.hpp"
#include "PipelinePolygonMode.hpp"
#include "Core/Tool/Enum.hpp"

using namespace Minty;

static constexpr Char const* SHADERPOLYGONMODE_STRINGS[static_cast<Size>(PipelinePolygonModeEnum::Count)] =
{
	"Undefined",
	"Fill",
	"Line",
	"Point"
};

Bool Minty::Parser<PipelinePolygonModeEnum>::parse(StringView const str, PipelinePolygonModeEnum &value)
{
    return Tool::try_parse_enum(str, SHADERPOLYGONMODE_STRINGS, static_cast<Size>(PipelinePolygonModeEnum::Count), value);
}

String Minty::Parser<PipelinePolygonModeEnum>::to_string(PipelinePolygonModeEnum const &obj)
{
	return Tool::to_string_enum(reinterpret_cast<Size const&>(obj), SHADERPOLYGONMODE_STRINGS, static_cast<Size>(PipelinePolygonModeEnum::Count));
}
