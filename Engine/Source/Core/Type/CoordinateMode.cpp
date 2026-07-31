#include "pch.hpp"
#include "CoordinateMode.hpp"
#include "Core/Tool/Enum.hpp"

using namespace Minty;

static constexpr Size COORDINATEMODE_COUNT = 3;
static constexpr Char const* COORDINATEMODE_STRINGS[COORDINATEMODE_COUNT] = {
	"Undefined",
	"Normalized",
	"Pixel"
};

Bool Minty::Parser<CoordinateModeEnum>::parse(StringView const str, CoordinateModeEnum &value)
{
    return Tool::try_parse_enum(str, COORDINATEMODE_STRINGS, COORDINATEMODE_COUNT, value);
}

String Minty::Parser<CoordinateModeEnum>::to_string(CoordinateModeEnum const &obj)
{
    return Tool::to_string_enum(reinterpret_cast<Size const&>(obj), COORDINATEMODE_STRINGS, COORDINATEMODE_COUNT);
}
