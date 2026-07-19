#pragma once

#include "Core/Serialize/Parser.hpp"

namespace Minty
{
    enum class InputTypeEnum
    {
        None,
        Key,
        MouseButton,
        MouseMove,
        MouseScroll,
        GamepadButton,
        GamepadAxis,
        Count
    };

    struct InputType
    {
        InputTypeEnum value;

        constexpr InputType() : value(InputTypeEnum::None) {}
        constexpr InputType(InputTypeEnum const value) : value(value) {}
        constexpr operator InputTypeEnum() const { return value; }

        constexpr bool operator==(InputType const& other) const { return value == other.value; }
        constexpr bool operator!=(InputType const& other) const { return value != other.value; }
    };

    template<>
    struct Parser<InputTypeEnum>
    {
        static Bool parse(StringView const str, InputTypeEnum& value);
        static String to_string(InputTypeEnum const& obj);
    };

    template<>
    struct Parser<InputType>
    {
        inline static Bool parse(StringView const str, InputType& value) { return Parser<InputTypeEnum>::parse(str, value.value); }
        inline static String to_string(InputType const& obj) { return Parser<InputTypeEnum>::to_string(obj.value); }
    };
}