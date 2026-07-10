#include "pch.h"
#include "CameraPerspective.h"
#include "Core/Tool/Enum.h"

using namespace Minty;

static constexpr Char const* PERSPECTIVE_STRINGS[static_cast<Size>(CameraPerspectiveEnum::Count)] =
{
	"Undefined",
	"Perspective",
	"Orthographic"
};

Bool Minty::Parser<CameraPerspectiveEnum>::parse(StringView const str, CameraPerspectiveEnum &value)
{
    return Tool::try_parse_enum(str, PERSPECTIVE_STRINGS, static_cast<Size>(CameraPerspectiveEnum::Count), value);
}

String Minty::Parser<CameraPerspectiveEnum>::to_string(CameraPerspectiveEnum const &obj)
{
	return Tool::to_string_enum(reinterpret_cast<Size const&>(obj), PERSPECTIVE_STRINGS, static_cast<Size>(CameraPerspectiveEnum::Count));
}