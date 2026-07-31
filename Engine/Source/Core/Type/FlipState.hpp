#pragma once

#include "Platform/Type/Primitive.hpp"
#include "Core/Serialize/Parser.hpp"

namespace Minty
{
    enum class FlipStateEnumFlags : Int
    {
        None = 0,
        Horizontal = 1 << 0,
        Vertical = 1 << 1,
        Both = Horizontal | Vertical,

        Count = 3,
        Default = None
    };

    struct FlipState
    {
        FlipStateEnumFlags value;

        constexpr FlipState() : value(FlipStateEnumFlags::None) {}
        constexpr FlipState(FlipStateEnumFlags const value) : value(value) {}
        constexpr operator FlipStateEnumFlags() const { return value; }

        constexpr Bool operator==(FlipStateEnumFlags const other) const { return value == other; }
        constexpr Bool operator!=(FlipStateEnumFlags const other) const { return value != other; }
        constexpr FlipState operator|(FlipStateEnumFlags const other) const { return FlipState(static_cast<FlipStateEnumFlags>(static_cast<Int>(value) | static_cast<Int>(other))); }
        constexpr FlipState operator&(FlipStateEnumFlags const other) const { return FlipState(static_cast<FlipStateEnumFlags>(static_cast<Int>(value) & static_cast<Int>(other))); }
        constexpr FlipState& operator|=(FlipStateEnumFlags const other) { value = static_cast<FlipStateEnumFlags>(static_cast<Int>(value) | static_cast<Int>(other)); return *this; }
        constexpr FlipState& operator&=(FlipStateEnumFlags const other) { value = static_cast<FlipStateEnumFlags>(static_cast<Int>(value) & static_cast<Int>(other)); return *this; }
        constexpr Bool has_flag(FlipStateEnumFlags const flag) const { return (static_cast<Int>(value) & static_cast<Int>(flag)) == static_cast<Int>(flag); }
    };

    template<>
    struct Parser<FlipStateEnumFlags>
    {
        static Bool parse(StringView const str, FlipStateEnumFlags& value);
        static String to_string(FlipStateEnumFlags const& obj);
    };

    template<>
    struct Parser<FlipState>
    {
        inline static Bool parse(StringView const str, FlipState& value) { return Parser<FlipStateEnumFlags>::parse(str, value.value); }
        inline static String to_string(FlipState const& obj) { return Parser<FlipStateEnumFlags>::to_string(obj.value); }
    };
}