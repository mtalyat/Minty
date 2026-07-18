#include "pch.hpp"
#include "GeometryIndexType.hpp"
#include "Core/Tool/Enum.hpp"

using namespace Minty;

static constexpr Char const* GEOMETRY_INDEX_TYPE_STRINGS[static_cast<Size>(GeometryIndexTypeEnum::Count)] =
{
    "None",
    "UInt16",
    "UInt32"
};

Bool Minty::Parser<GeometryIndexTypeEnum>::parse(StringView const str, GeometryIndexTypeEnum &value)
{
    return Tool::try_parse_enum(str, GEOMETRY_INDEX_TYPE_STRINGS, static_cast<Size>(GeometryIndexTypeEnum::Count), value);
}

String Minty::Parser<GeometryIndexTypeEnum>::to_string(GeometryIndexTypeEnum const &value)
{
    return Tool::to_string_enum(reinterpret_cast<Size const&>(value), GEOMETRY_INDEX_TYPE_STRINGS, static_cast<Size>(GeometryIndexTypeEnum::Count));
}
