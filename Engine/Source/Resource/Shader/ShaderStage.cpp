#include "pch.hpp"
#include "ShaderStage.hpp"
#include "Core/Tool/Enum.hpp"

using namespace Minty;

static constexpr Char const* SHADERSTAGE_STRINGS[static_cast<Size>(ShaderStageEnum::Count)] =
{
	"Undefined",
	"Vertex",
	"Fragment"
};

Bool Minty::Parser<ShaderStageEnum>::parse(StringView const str, ShaderStageEnum &value)
{
    return Tool::try_parse_enum(str, SHADERSTAGE_STRINGS, static_cast<Size>(ShaderStageEnum::Count), value);
}

String Minty::Parser<ShaderStageEnum>::to_string(ShaderStageEnum const &value)
{
	return Tool::to_string_enum(reinterpret_cast<Size const&>(value), SHADERSTAGE_STRINGS, static_cast<Size>(ShaderStageEnum::Count));
}
