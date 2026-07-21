#pragma once

/**
 * @file KeyModifier.hpp
 * @brief Header file defining the KeyModifier enum class.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include "Core/Serialize/Parser.hpp"
#include "Core/Type/Enum.hpp"

namespace Minty
{
    /**
     * @brief An enum class representing the modifier keys that can be held during a key event.
     */
    enum class KeyModifierFlagsEnum : Int
	{
		/**
		 * @brief No modifier keys are held.
		 */
		None = 0x0,

		/**
		 * @brief The Shift key is held.
		 */
		Shift = 0x1,

		/**
		 * @brief The Control key is held.
		 */
		Control = 0x2,

		/**
		 * @brief The Alt key is held.
		 */
		Alt = 0x4,

		/**
		 * @brief The Super (Windows/Command) key is held.
		 */
		Super = 0x8,

		/**
		 * @brief The Caps Lock key is active.
		 */
		CapsLock = 0x10,

		/**
		 * @brief The Num Lock key is active.
		 */
		NumLock = 0x20,

        Count = 7
	};

    MINTY_ENABLE_ENUM_OPERATORS(KeyModifierFlagsEnum)

    struct KeyModifier
    {
        KeyModifierFlagsEnum flags;

        constexpr KeyModifier() : flags(KeyModifierFlagsEnum::None) {}
        constexpr KeyModifier(KeyModifierFlagsEnum const flags) : flags(flags) {}

        constexpr operator KeyModifierFlagsEnum() const { return flags; }
        constexpr Bool operator==(KeyModifier const& other) const { return flags == other.flags; }
        constexpr Bool operator!=(KeyModifier const& other) const { return flags != other.flags; }

        constexpr Bool is_shift() const { return (static_cast<Int>(flags) & static_cast<Int>(KeyModifierFlagsEnum::Shift)) != 0; }
        constexpr Bool is_control() const { return (static_cast<Int>(flags) & static_cast<Int>(KeyModifierFlagsEnum::Control)) != 0; }
        constexpr Bool is_alt() const { return (static_cast<Int>(flags) & static_cast<Int>(KeyModifierFlagsEnum::Alt)) != 0; }
        constexpr Bool is_super() const { return (static_cast<Int>(flags) & static_cast<Int>(KeyModifierFlagsEnum::Super)) != 0; }
        constexpr Bool is_caps_lock() const { return (static_cast<Int>(flags) & static_cast<Int>(KeyModifierFlagsEnum::CapsLock)) != 0; }
        constexpr Bool is_num_lock() const { return (static_cast<Int>(flags) & static_cast<Int>(KeyModifierFlagsEnum::NumLock)) != 0; }
    };

    template<>
    struct Parser<KeyModifierFlagsEnum>
    {
        static Bool parse(StringView const str, KeyModifierFlagsEnum& value);
        static String to_string(KeyModifierFlagsEnum const& obj);
    };

    template<>
    struct Parser<KeyModifier>
    {
        inline static Bool parse(StringView const str, KeyModifier& value) { return Parser<KeyModifierFlagsEnum>::parse(str, value.flags); }
        inline static String to_string(KeyModifier const& obj) { return Parser<KeyModifierFlagsEnum>::to_string(obj.flags); }
    };
}