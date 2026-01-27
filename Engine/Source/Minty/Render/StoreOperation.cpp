#include "pch.h"
#include "StoreOperation.h"
#include "Minty/Tool/Enum.h"

using namespace Minty;

static constexpr Size STOREOPERATION_COUNT = 3;
static constexpr Char const* STOREOPERATION_STRINGS[STOREOPERATION_COUNT] =
{
	"Undefined",
	"DontCare",
	"Store"
};

Bool Minty::Parser<StoreOperation>::parse(StringView const str, StoreOperation &value)
{
    return Tool::try_parse_enum(str, STOREOPERATION_STRINGS, STOREOPERATION_COUNT, value);
}

String Minty::Parser<StoreOperation>::to_string(StoreOperation const &value)
{
	return Tool::to_string_enum(reinterpret_cast<Size const&>(value), STOREOPERATION_STRINGS, STOREOPERATION_COUNT);
}