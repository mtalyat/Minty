#include "pch.hpp"
#include "PipelineCullMode.hpp"
#include "Core/Tool/Enum.hpp"

using namespace Minty;

static constexpr Char const* SHADERCULLMODE_STRINGS[static_cast<Size>(PipelineCullModeEnum::Count)] =
{
	"Undefined",
	"None",
	"Front",
	"Back",
	"Both"
};

Bool Minty::Parser<PipelineCullModeEnum>::parse(StringView const str, PipelineCullModeEnum &value)
{
    return Tool::try_parse_enum(str, SHADERCULLMODE_STRINGS, static_cast<Size>(PipelineCullModeEnum::Count), value);
}

String Minty::Parser<PipelineCullModeEnum>::to_string(PipelineCullModeEnum const &obj)
{
	return Tool::to_string_enum(reinterpret_cast<Size const&>(obj), SHADERCULLMODE_STRINGS, static_cast<Size>(PipelineCullModeEnum::Count));
}