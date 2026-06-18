#include "pch.h"
#include "StoreOperation.h"
#include "Core/Tool/Enum.h"

using namespace Minty;

static constexpr Char const* STOREOPERATION_STRINGS[static_cast<Size>(StoreOperationEnum::Count)] =
{
	"Undefined",
	"DontCare",
	"Store"
};

Bool Minty::Parser<StoreOperationEnum>::parse(StringView const str, StoreOperationEnum &value)
{
    return Tool::try_parse_enum(str, STOREOPERATION_STRINGS, static_cast<Size>(StoreOperationEnum::Count), value);
}

String Minty::Parser<StoreOperationEnum>::to_string(StoreOperationEnum const &value)
{
	return Tool::to_string_enum(reinterpret_cast<Size const&>(value), STOREOPERATION_STRINGS, static_cast<Size>(StoreOperationEnum::Count));
}