#pragma once

#include "Platform/Type/Primitive.h"
#include "Core/Serialize/Parser.h"

namespace Minty
{
    enum class GeometryIndexTypeEnum
    {
        None = 0,
        UInt16,
        UInt32,
        Count,

        Default = UInt16
    };

    struct GeometryIndexType
    {
        GeometryIndexTypeEnum value;

        constexpr GeometryIndexType() : value{GeometryIndexTypeEnum::Default} {}
        constexpr GeometryIndexType(GeometryIndexTypeEnum const value) : value{value} {}
        constexpr GeometryIndexTypeEnum operator()() const { return value; }

        constexpr Size get_size() const
        {
            switch (value)
            {
                case GeometryIndexTypeEnum::UInt16:
                    return sizeof(UInt16);
                case GeometryIndexTypeEnum::UInt32:
                    return sizeof(UInt32);
            }

            return 0;
        }

        constexpr Bool operator==(GeometryIndexType const &other) const { return value == other.value; }
        constexpr Bool operator!=(GeometryIndexType const &other) const { return value != other.value; }

        constexpr static GeometryIndexTypeEnum from_size(Size const size)
        {
            switch (size)
            {
                case sizeof(UInt16):
                    return GeometryIndexTypeEnum::UInt16;
                case sizeof(UInt32):
                    return GeometryIndexTypeEnum::UInt32;
            }

            return GeometryIndexTypeEnum::None;
        }
    };

    template<>
    struct Parser<GeometryIndexTypeEnum>
    {
        static Bool parse(StringView const str, GeometryIndexTypeEnum &value);
        static String to_string(GeometryIndexTypeEnum const &value);
    };
}