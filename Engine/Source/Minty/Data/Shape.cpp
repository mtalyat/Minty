#include "pch.h"
#include "Shape.h"
#include "Minty/Tool/Enum.h"

using namespace Minty;

static constexpr Size SHAPE_COUNT = 7;
static constexpr Char const* SHAPE_STRINGS[SHAPE_COUNT] =
{
	"Empty",
	"Box",
	"Sphere",
	"Capsule",
	"Cylinder",
	"Cone",
	"Custom",
};

Bool Minty::Parser<Shape>::parse(StringView const str, Shape &value)
{
    return Tool::try_parse_enum(str, SHAPE_STRINGS, SHAPE_COUNT, value);
}

String Minty::Parser<Shape>::to_string(Shape const &value)
{
    return Tool::to_string_enum(reinterpret_cast<Size const&>(value), SHAPE_STRINGS, SHAPE_COUNT);
}
