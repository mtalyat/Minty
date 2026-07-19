#pragma once

#include "Core/Serialize/Parser.hpp"

namespace Minty
{
    enum class InputBindingTypeEnum
    {
        None,
        Button,
        Axis,
        Axis2D,
        Count
    };

    struct InputBindingType
    {
        InputBindingTypeEnum value;

        constexpr InputBindingType() : value(InputBindingTypeEnum::None) {}
        constexpr InputBindingType(InputBindingTypeEnum const value) : value(value) {}
        constexpr operator InputBindingTypeEnum() const { return value; }

        constexpr bool operator==(InputBindingType const& other) const { return value == other.value; }
        constexpr bool operator!=(InputBindingType const& other) const { return value != other.value; }
    };

    template<>
    struct Parser<InputBindingTypeEnum>
    {
        static Bool parse(StringView const str, InputBindingTypeEnum& value);
        static String to_string(InputBindingTypeEnum const& obj);
    };

    template<>
    struct Parser<InputBindingType>
    {
        inline static Bool parse(StringView const str, InputBindingType& value) { return Parser<InputBindingTypeEnum>::parse(str, value.value); }
        inline static String to_string(InputBindingType const& obj) { return Parser<InputBindingTypeEnum>::to_string(obj.value); }
    };
}