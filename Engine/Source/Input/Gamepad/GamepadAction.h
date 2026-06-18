#pragma once

/**
 * @file GamepadAction.h
 * @brief Header file defining the GamepadAction enum class.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.h"
#include "Core/Serialize/Parser.h"
#include "Core/Type/Enum.h"

namespace Minty
{
    /**
     * @brief An enum class representing the actions that can be performed on a key.
     */
	enum class GamepadActionEnum : Int
	{
		Up = 0,
		Down = 1,

        Count
	};

    MINTY_ENABLE_ENUM_OPERATORS(GamepadActionEnum)

    struct GamepadAction
    {
        GamepadActionEnum action;

        constexpr GamepadAction() : action(GamepadActionEnum::Up) {}
        constexpr GamepadAction(GamepadActionEnum const action) : action(action) {}

        constexpr operator GamepadActionEnum() const { return action; }
        constexpr Bool operator==(GamepadAction const& other) const { return action == other.action; }
        constexpr Bool operator!=(GamepadAction const& other) const { return action != other.action; }

        constexpr Bool is_up() const { return action == GamepadActionEnum::Up; }
        constexpr Bool is_down() const { return action == GamepadActionEnum::Down; }
    };

    template<>
    struct Parser<GamepadActionEnum>
    {
        static Bool parse(StringView const str, GamepadActionEnum& value);
        static String to_string(GamepadActionEnum const& obj);
    };
	
	template<>
	struct Parser<GamepadAction>
	{
		inline static Bool parse(StringView const str, GamepadAction& value) { return Parser<GamepadActionEnum>::parse(str, value.action); }
		inline static String to_string(GamepadAction const& obj) { return Parser<GamepadActionEnum>::to_string(obj.action); }
	};
}