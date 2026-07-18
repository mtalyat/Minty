#pragma once

/**
 * @file GamepadAxis.h
 * @brief Header file for gamepad axis enumeration.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include "Core/Serialize/Parser.hpp"
#include "Core/Type/Enum.hpp"

namespace Minty
{
	/**
	 * @brief An axis on a gamepad.
	 */
	enum class GamepadAxisEnum : Int
	{
		LeftX = 0,
		LeftY = 1,
		RightX = 2,
		RightY = 3,
		LeftTrigger = 4,
		RightTrigger = 5,

		Count
	};

	MINTY_ENABLE_ENUM_OPERATORS(GamepadAxisEnum)

	struct GamepadAxis
	{
		GamepadAxisEnum axis;

		constexpr GamepadAxis() : axis(GamepadAxisEnum::LeftX) {}
		constexpr GamepadAxis(GamepadAxisEnum const axis) : axis(axis) {}

		constexpr operator GamepadAxisEnum() const { return axis; }
		constexpr Bool operator==(GamepadAxis const& other) const { return axis == other.axis; }
		constexpr Bool operator!=(GamepadAxis const& other) const { return axis != other.axis; }
	};

	template<>
	struct Parser<GamepadAxisEnum>
	{
		static Bool parse(StringView const str, GamepadAxisEnum& value);
		static String to_string(GamepadAxisEnum const& obj);
	};
	
	template<>
	struct Parser<GamepadAxis>
	{
		inline static Bool parse(StringView const str, GamepadAxis& value) { return Parser<GamepadAxisEnum>::parse(str, value.axis); }
		inline static String to_string(GamepadAxis const& obj) { return Parser<GamepadAxisEnum>::to_string(obj.axis); }
	};
}
