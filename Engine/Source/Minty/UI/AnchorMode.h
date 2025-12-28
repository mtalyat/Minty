#ifndef MINTY_UI_ANCHORMODE_H
#define MINTY_UI_ANCHORMODE_H

/**
 * @file AnchorMode.h
 * @brief Header file defining the AnchorMode enum.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Core/Enum.h"
#include "Minty/Serialization/Parser.h"

namespace Minty
{
	/**
	 * @brief Determines how the anchor is applied to the UI element.
	 */
	enum class AnchorMode : Int
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

	MINTY_ENABLE_ENUM_OPERATORS(AnchorMode);

    template<>
    struct Parser<AnchorMode>
    {
        static Bool parse(StringView const str, AnchorMode &value);
        static String to_string(AnchorMode const &value);
    };
}

#endif // MINTY_UI_ANCHORMODE_H