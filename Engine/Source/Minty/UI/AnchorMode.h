#pragma once
#include "Minty/Core/Types.h"
#include "Minty/Core/Macro.h"
#include "Minty/Serialization/Parse.h"
#include "Minty/Serialization/ToString.h"

namespace Minty
{
	/// <summary>
	/// Determines how the anchor is applied to the UI element.
	/// </summary>
	enum class AnchorMode : Int
	{
		Empty = 0,

		Top = 0b000001,
		Middle = 0b000010,
		Bottom = 0b000100,
		Left = 0b001000,
		Center = 0b010000,
		Right = 0b100000,

		VerticalMask = 0b000111,
		HorizontalMask = 0b111000,

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

	MINTY_ENUM_FLAGS_OPERATORS(AnchorMode);

	String to_string(AnchorMode const obj);
	AnchorMode parse_to_anchor_mode(String const& string);
	Bool parse_try_anchor_mode(String const& string, AnchorMode& value);
	template<>
	inline AnchorMode parse_to<AnchorMode>(String const& string) { return parse_to_anchor_mode(string); }
	template<>
	inline Bool parse_try<AnchorMode>(String const& string, AnchorMode& value) { return parse_try_anchor_mode(string, value); }
}