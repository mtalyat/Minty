#pragma once

/**
 * @file MouseAction.hpp
 * @brief Header file defining the MouseAction enum class.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include "Core/Serialize/Parser.hpp"
#include "Core/Type/Enum.hpp"

namespace Minty
{
    /**
     * @brief An enum class representing the actions that can be performed on a key.
     */
	enum class MouseActionEnum : Int
	{
		Up = 0,
		Down = 1,

        Count
	};

    MINTY_ENABLE_ENUM_OPERATORS(MouseActionEnum)

    struct MouseAction
    {
        MouseActionEnum action;

        constexpr MouseAction() : action(MouseActionEnum::Up) {}
        constexpr MouseAction(MouseActionEnum const action) : action(action) {}

        constexpr operator MouseActionEnum() const { return action; }
        constexpr Bool operator==(MouseAction const& other) const { return action == other.action; }
        constexpr Bool operator!=(MouseAction const& other) const { return action != other.action; }

        constexpr Bool is_up() const { return action == MouseActionEnum::Up; }
        constexpr Bool is_down() const { return action == MouseActionEnum::Down; }
    };

    template<>
    struct Parser<MouseActionEnum>
    {
        static Bool parse(StringView const str, MouseActionEnum& value);
        static String to_string(MouseActionEnum const& obj);
    };
	
	template<>
	struct Parser<MouseAction>
	{
		inline static Bool parse(StringView const str, MouseAction& value) { return Parser<MouseActionEnum>::parse(str, value.action); }
		inline static String to_string(MouseAction const& obj) { return Parser<MouseActionEnum>::to_string(obj.action); }
	};
}