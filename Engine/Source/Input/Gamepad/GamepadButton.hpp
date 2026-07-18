#pragma once

/**
 * @file GamepadButton.h
 * @brief Header file for gamepad button enumeration.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include "Core/Serialize/Parser.hpp"
#include "Core/Type/Enum.hpp"

namespace Minty
{
	/**
	 * @brief A button on a gamepad.
	 */
	enum class GamepadButtonEnum : Int
	{
		ButtonSouth = 0,
		ButtonEast = 1,
		ButtonWest = 2,
		ButtonNorth = 3,
		LeftBumper = 4,
		RightBumper = 5,
		Back = 6,
		Start = 7,
		Home = 8,
		LeftThumb = 9,
		RightThumb = 10,
		DpadUp = 11,
		DpadRight = 12,
		DpadDown = 13,
		DpadLeft = 14,

		Count
	};

	MINTY_ENABLE_ENUM_OPERATORS(GamepadButtonEnum)

	struct GamepadButton
	{
		GamepadButtonEnum button;

		constexpr GamepadButton() : button(GamepadButtonEnum::ButtonSouth) {}
		constexpr GamepadButton(GamepadButtonEnum const button) : button(button) {}

		constexpr operator GamepadButtonEnum() const { return button; }
		constexpr Bool operator==(GamepadButton const& other) const { return button == other.button; }
		constexpr Bool operator!=(GamepadButton const& other) const { return button != other.button; }
	};

	template<>
	struct Parser<GamepadButtonEnum>
	{
		static Bool parse(StringView const str, GamepadButtonEnum& value);
		static String to_string(GamepadButtonEnum const& obj);
	};
	
	template<>
	struct Parser<GamepadButton>
	{
		inline static Bool parse(StringView const str, GamepadButton& value) { return Parser<GamepadButtonEnum>::parse(str, value.button); }
		inline static String to_string(GamepadButton const& obj) { return Parser<GamepadButtonEnum>::to_string(obj.button); }
	};
}
