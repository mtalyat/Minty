#include "pch.hpp"
#include "PipelineInputType.hpp"
#include "Core/Tool/Enum.hpp"

using namespace Minty;

static constexpr Char const* SHADERINPUTTYPE_STRINGS[static_cast<Size>(PipelineInputTypeEnum::Count)] =
{
	"Undefined",
	"Sample",
	"CombinedImageSampler",
	"SampledImage",
	"StorageImage",
	"UniformTexelBuffer",
	"StorageTexelBuffer",
	"UniformBuffer",
	"StorageBuffer",
	"UniformBufferDynamic",
	"StorageBufferDynamic",
	"PushConstant"
};

Bool Minty::Parser<PipelineInputTypeEnum>::parse(StringView const str, PipelineInputTypeEnum &value)
{
    return Tool::try_parse_enum(str, SHADERINPUTTYPE_STRINGS, static_cast<Size>(PipelineInputTypeEnum::Count), value);
}

String Minty::Parser<PipelineInputTypeEnum>::to_string(PipelineInputTypeEnum const &obj)
{
    return Tool::to_string_enum(reinterpret_cast<Size const&>(obj), SHADERINPUTTYPE_STRINGS, static_cast<Size>(PipelineInputTypeEnum::Count));
}
