#include "pch.h"
#include "PipelineFrontFace.h"
#include "Core/Tool/Enum.h"

using namespace Minty;

static constexpr Char const* SHADERFRONTFACE_STRINGS[static_cast<Size>(PipelineFrontFaceEnum::Count)] =
{
	"Undefined",
	"CounterClockwise",
	"Clockwise"
};

Bool Minty::Parser<PipelineFrontFaceEnum>::parse(StringView const str, PipelineFrontFaceEnum &value)
{
    return Tool::try_parse_enum(str, SHADERFRONTFACE_STRINGS, static_cast<Size>(PipelineFrontFaceEnum::Count), value);
}

String Minty::Parser<PipelineFrontFaceEnum>::to_string(PipelineFrontFaceEnum const &obj)
{
	return Tool::to_string_enum(reinterpret_cast<Size const&>(obj), SHADERFRONTFACE_STRINGS, static_cast<Size>(PipelineFrontFaceEnum::Count));
}
