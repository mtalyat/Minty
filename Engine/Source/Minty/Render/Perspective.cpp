#include "pch.h"
#include "Perspective.h"
#include "Minty/Tool/Enum.h"

using namespace Minty;

static constexpr Size PERSPECTIVE_COUNT = 3;
static constexpr Char const* PERSPECTIVE_STRINGS[PERSPECTIVE_COUNT] =
{
	"Undefined",
	"Perspective",
	"Orthographic"
};

Bool Minty::Parser<Perspective>::parse(StringView const str, Perspective &value)
{
    return Tool::try_parse_enum(str, PERSPECTIVE_STRINGS, PERSPECTIVE_COUNT, value);
}

String Minty::Parser<Perspective>::to_string(Perspective const &obj)
{
	return Tool::to_string_enum(reinterpret_cast<Size const&>(obj), PERSPECTIVE_STRINGS, PERSPECTIVE_COUNT);
}