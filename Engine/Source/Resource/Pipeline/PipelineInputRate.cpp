#include "pch.hpp"
#include "PipelineInputRate.hpp"
#include "Core/Tool/Enum.hpp"

using namespace Minty;

static constexpr Char const* SHADERINPUTRATE_STRINGS[static_cast<Size>(PipelineInputRateEnum::Count)] =
{
	"Undefined",
	"Vertex",
	"Instance"
};

Bool Minty::Parser<PipelineInputRateEnum>::parse(StringView const str, PipelineInputRateEnum &value)
{
    return Tool::try_parse_enum(str, SHADERINPUTRATE_STRINGS, static_cast<Size>(PipelineInputRateEnum::Count), value);
}

String Minty::Parser<PipelineInputRateEnum>::to_string(PipelineInputRateEnum const &obj)
{
	return Tool::to_string_enum(reinterpret_cast<Size const&>(obj), SHADERINPUTRATE_STRINGS, static_cast<Size>(PipelineInputRateEnum::Count));
}
