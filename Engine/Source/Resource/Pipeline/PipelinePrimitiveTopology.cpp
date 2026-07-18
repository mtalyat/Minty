#include "pch.hpp"
#include "PipelinePrimitiveTopology.hpp"
#include "Core/Tool/Enum.hpp"

using namespace Minty;

static constexpr Char const* SHADERPRIMITIVETOPOLOGY_STRINGS[static_cast<Size>(PipelinePrimitiveTopologyEnum::Count)] =
{
	"Undefined",
	"PointList",
	"LineList",
	"LineStrip",
	"TriangleList",
	"TriangleStrip",
	"TriangleFan"
};

Bool Minty::Parser<PipelinePrimitiveTopologyEnum>::parse(StringView const str, PipelinePrimitiveTopologyEnum &value)
{
    return Tool::try_parse_enum(str, SHADERPRIMITIVETOPOLOGY_STRINGS, static_cast<Size>(PipelinePrimitiveTopologyEnum::Count), value);
}

String Minty::Parser<PipelinePrimitiveTopologyEnum>::to_string(PipelinePrimitiveTopologyEnum const &obj)
{
	return Tool::to_string_enum(reinterpret_cast<Size const&>(obj), SHADERPRIMITIVETOPOLOGY_STRINGS, static_cast<Size>(PipelinePrimitiveTopologyEnum::Count));
}