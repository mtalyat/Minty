#include "pch.h"
#include "LoadOperation.h"
#include "Core/Tool/Enum.h"

using namespace Minty;

static constexpr Char const* LOADOPERATION_STRINGS[static_cast<Size>(LoadOperationEnum::Count)] =
{
	"Undefined",
	"DontCare",
	"Load",
	"Clear"
};

Bool Minty::Parser<LoadOperationEnum>::parse(StringView const str, LoadOperationEnum &value)
{
    return Tool::try_parse_enum(str, LOADOPERATION_STRINGS, static_cast<Size>(LoadOperationEnum::Count), value);
}

String Minty::Parser<LoadOperationEnum>::to_string(LoadOperationEnum const &obj)
{
	return Tool::to_string_enum(reinterpret_cast<Size const&>(obj), LOADOPERATION_STRINGS, static_cast<Size>(LoadOperationEnum::Count));
}