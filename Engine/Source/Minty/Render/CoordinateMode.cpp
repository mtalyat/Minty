#include "pch.h"
#include "CoordinateMode.h"
#include "Minty/Tool/Enum.h"

using namespace Minty;

static constexpr Size COORDINATEMODE_COUNT = 3;
static constexpr Char const* COORDINATEMODE_STRINGS[COORDINATEMODE_COUNT] = {
	"Undefined",
	"Normalized",
	"Pixel"
};

Bool Minty::Parser<CoordinateMode>::parse(StringView const str, CoordinateMode &value)
{
    return Tool::try_parse_enum(str, COORDINATEMODE_STRINGS, COORDINATEMODE_COUNT, reinterpret_cast<Size&>(value));
}

String Minty::Parser<CoordinateMode>::to_string(CoordinateMode const &obj)
{
    return Tool::to_string_enum(reinterpret_cast<Size const&>(obj), COORDINATEMODE_STRINGS, COORDINATEMODE_COUNT);
}
