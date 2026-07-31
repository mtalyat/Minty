#pragma once

/**
 * @file AnchorModeEnum.hpp
 * @brief Header file defining the AnchorModeEnum enum.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include "Core/Serialize/Parser.hpp"
 
namespace Minty
{
	/**
	 * @brief Determines how the anchor is applied to the UI element.
	 */
	enum class AnchorEnumFlags : Int
	{
		Empty = 0,

		Top = 0b000001,
		Middle = 0b000010,
		Bottom = 0b000100,
		Left = 0b001000,
		Center = 0b010000,
		Right = 0b100000,

		Vertical = 0b000111,
		Horizontal = 0b111000,

		TopLeft = Top | Left,
		TopCenter = Top | Center,
		TopRight = Top | Right,
		MiddleLeft = Middle | Left,
		MiddleCenter = Middle | Center,
		MiddleRight = Middle | Right,
		BottomLeft = Bottom | Left,
		BottomCenter = Bottom | Center,
		BottomRight = Bottom | Right,

		All = 0b111111,
	};

	struct Anchor
	{
		AnchorEnumFlags value;

		constexpr Anchor() : value(AnchorEnumFlags::Empty) {}
		constexpr Anchor(AnchorEnumFlags const value) : value(value) {}
		constexpr operator AnchorEnumFlags() const { return value; }

		constexpr Bool operator==(AnchorEnumFlags const other) const { return value == other; }
		constexpr Bool operator!=(AnchorEnumFlags const other) const { return value != other; }
		constexpr Anchor operator|(AnchorEnumFlags const other) const { return Anchor(static_cast<AnchorEnumFlags>(static_cast<Int>(value) | static_cast<Int>(other))); }
		constexpr Anchor operator&(AnchorEnumFlags const other) const { return Anchor(static_cast<AnchorEnumFlags>(static_cast<Int>(value) & static_cast<Int>(other))); }
		constexpr Anchor operator|(Anchor const other) const { return Anchor(static_cast<AnchorEnumFlags>(static_cast<Int>(value) | static_cast<Int>(other.value))); }
		constexpr Anchor operator&(Anchor const other) const { return Anchor(static_cast<AnchorEnumFlags>(static_cast<Int>(value) & static_cast<Int>(other.value))); }
		constexpr Anchor& operator|=(AnchorEnumFlags const other) { value = static_cast<AnchorEnumFlags>(static_cast<Int>(value) | static_cast<Int>(other)); return *this; }
		constexpr Anchor& operator&=(AnchorEnumFlags const other) { value = static_cast<AnchorEnumFlags>(static_cast<Int>(value) & static_cast<Int>(other)); return *this; }
		constexpr Anchor& operator|=(Anchor const other) { value = static_cast<AnchorEnumFlags>(static_cast<Int>(value) | static_cast<Int>(other.value)); return *this; }
		constexpr Anchor& operator&=(Anchor const other) { value = static_cast<AnchorEnumFlags>(static_cast<Int>(value) & static_cast<Int>(other.value)); return *this; }

		constexpr Bool has_flag(AnchorEnumFlags const flag) const { return (static_cast<Int>(value) & static_cast<Int>(flag)) == static_cast<Int>(flag); }
	};

    template<>
    struct Parser<AnchorEnumFlags>
    {
        static Bool parse(StringView const str, AnchorEnumFlags &value);
        static String to_string(AnchorEnumFlags const &value);
    };

	template<>
	struct Parser<Anchor>
	{
        inline static Bool parse(StringView const str, Anchor &value) { return Parser<AnchorEnumFlags>::parse(str, value.value); }
        inline static String to_string(Anchor const &value) { return Parser<AnchorEnumFlags>::to_string(value.value); }
	};
}
