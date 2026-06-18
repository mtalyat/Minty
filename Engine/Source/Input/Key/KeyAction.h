#pragma once

/**
 * @file KeyAction.h
 * @brief Header file defining the KeyAction enum class.
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
	enum class KeyActionEnum : Int
	{
		Up = 0,
		Down = 1,
		Hold = 2,

        Count
	};

    MINTY_ENABLE_ENUM_OPERATORS(KeyActionEnum)

    struct KeyAction
    {
        KeyActionEnum action;

        constexpr KeyAction() : action(KeyActionEnum::Up) {}
        constexpr KeyAction(KeyActionEnum const action) : action(action) {}

        constexpr operator KeyActionEnum() const { return action; }
        constexpr Bool operator==(KeyAction const& other) const { return action == other.action; }
        constexpr Bool operator!=(KeyAction const& other) const { return action != other.action; }

        constexpr Bool is_up() const { return action == KeyActionEnum::Up; }
        constexpr Bool is_down() const { return action == KeyActionEnum::Down; }
        constexpr Bool is_hold() const { return action == KeyActionEnum::Hold; }
    };

    template<>
    struct Parser<KeyActionEnum>
    {
        static Bool parse(StringView const str, KeyActionEnum& value);
        static String to_string(KeyActionEnum const& obj);
    };
	
	template<>
	struct Parser<KeyAction>
	{
		inline static Bool parse(StringView const str, KeyAction& value) { return Parser<KeyActionEnum>::parse(str, value.action); }
		inline static String to_string(KeyAction const& obj) { return Parser<KeyActionEnum>::to_string(obj.action); }
	};
}