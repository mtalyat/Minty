#include "pch.hpp"
#include "PipelineDepthStencilMode.hpp"
#include "Core/Tool/Enum.hpp"

using namespace Minty;

static constexpr Char const* PIPELINE_DEPTH_STENCIL_MODE_STRINGS[static_cast<Size>(PipelineDepthStencilModeEnum::Count)] =
{
    "None",
    "Write",
    "Test"
};

Bool Minty::Parser<PipelineDepthStencilModeEnum>::parse(StringView const str, PipelineDepthStencilModeEnum &value)
{
    return Tool::try_parse_enum(str, PIPELINE_DEPTH_STENCIL_MODE_STRINGS, static_cast<Size>(PipelineDepthStencilModeEnum::Count), value);
}

String Minty::Parser<PipelineDepthStencilModeEnum>::to_string(PipelineDepthStencilModeEnum const &obj)
{
    return Tool::to_string_enum(reinterpret_cast<Size const&>(obj), PIPELINE_DEPTH_STENCIL_MODE_STRINGS, static_cast<Size>(PipelineDepthStencilModeEnum::Count));
}
