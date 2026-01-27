#include "pch.h"
#include "ShaderInputType.h"
#include "Minty/Tool/Enum.h"

using namespace Minty;

static constexpr Size SHADERINPUTTYPE_COUNT = 12;
static constexpr Char const* SHADERINPUTTYPE_STRINGS[SHADERINPUTTYPE_COUNT] =
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

Bool Minty::Parser<ShaderInputType>::parse(StringView const str, ShaderInputType &value)
{
    return Tool::try_parse_enum(str, SHADERINPUTTYPE_STRINGS, SHADERINPUTTYPE_COUNT, value);
}
