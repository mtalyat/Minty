#pragma once

/**
 * @file MouseButton.h
 * @brief Header file defining the MouseButton enum class.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.h"
#include "Core/Serialize/Parser.h"
#include "Core/Type/Enum.h"

namespace Minty
{
    /**
     * @brief An enum class representing the buttons on a mouse.
     */
    enum class MouseButtonEnum
	{
		Button1 = 0,
		Button2 = 1,
		Button3 = 2,
		Button4 = 3,
		Button5 = 4,
		Button6 = 5,
		Button7 = 6,
		Button8 = 7,

        Count,

		Left = Button1,
		Right = Button2,
		Middle = Button3,
		X1 = Button4,
		X2 = Button5
	};

    MINTY_ENABLE_ENUM_OPERATORS(MouseButtonEnum)

    struct MouseButton
    {
        MouseButtonEnum button;

        constexpr MouseButton() : button(MouseButtonEnum::Button1) {}
        constexpr MouseButton(MouseButtonEnum const button) : button(button) {}

        constexpr operator MouseButtonEnum() const { return button; }
        constexpr Bool operator==(MouseButton const& other) const { return button == other.button; }
        constexpr Bool operator!=(MouseButton const& other) const { return button != other.button; }
    };

    template<>
    struct Parser<MouseButtonEnum>
    {
        static Bool parse(StringView const str, MouseButtonEnum& value);
        static String to_string(MouseButtonEnum const& obj);
    };

    template<>
    struct Parser<MouseButton>
    {
        inline static Bool parse(StringView const str, MouseButton& value) { return Parser<MouseButtonEnum>::parse(str, value.button); }
        inline static String to_string(MouseButton const& obj) { return Parser<MouseButtonEnum>::to_string(obj.button); }
    };
}