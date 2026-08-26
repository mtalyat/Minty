#include "pch.hpp"
#include "CanvasResizeMode.hpp"
#include "Core/Tool/Enum.hpp"

using namespace Minty;

static constexpr Size CANVASRESIZEMODE_COUNT = 3;
static constexpr Char const *CANVASRESIZEMODE_STRINGS[CANVASRESIZEMODE_COUNT] = {
	"Undefined",
	"FixedSize",
	"Dynamic"};

Bool Minty::Parser<CanvasResizeModeEnum>::parse(StringView const str, CanvasResizeModeEnum &value)
{
	return Tool::try_parse_enum(str, CANVASRESIZEMODE_STRINGS, CANVASRESIZEMODE_COUNT, value);
}

String Minty::Parser<CanvasResizeModeEnum>::to_string(CanvasResizeModeEnum const &obj)
{
	return Tool::to_string_enum(reinterpret_cast<Size const &>(obj), CANVASRESIZEMODE_STRINGS, CANVASRESIZEMODE_COUNT);
}