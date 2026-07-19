#pragma once

/**
 * @file KeyAction.h
 * @brief Header file defining the KeyAction enum class.
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
        KeyActionEnum value;

        constexpr KeyAction() : value(KeyActionEnum::Up) {}
        constexpr KeyAction(KeyActionEnum const value) : value(value) {}

        constexpr operator KeyActionEnum() const { return value; }
        constexpr Bool operator==(KeyAction const& other) const { return value == other.value; }
        constexpr Bool operator!=(KeyAction const& other) const { return value != other.value; }

        constexpr Bool is_up() const { return value == KeyActionEnum::Up; }
        constexpr Bool is_down() const { return value == KeyActionEnum::Down; }
        constexpr Bool is_hold() const { return value == KeyActionEnum::Hold; }
        constexpr Bool is_pressed() const { return value == KeyActionEnum::Down || value == KeyActionEnum::Hold; }
        constexpr Bool is_released() const { return value == KeyActionEnum::Up; }
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
		inline static Bool parse(StringView const str, KeyAction& value) { return Parser<KeyActionEnum>::parse(str, value.value); }
		inline static String to_string(KeyAction const& obj) { return Parser<KeyActionEnum>::to_string(obj.value); }
	};
}