#pragma once

/**
 * @file FlagsEnum.h
 * @brief Header file defining utilities for enums.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include <type_traits>

namespace Minty
{
    template<typename Enum>
    struct EnableEnumOperators
    {
        static constexpr Bool enable = false;
    };

    template<typename Enum>
    constexpr std::enable_if_t<Minty::EnableEnumOperators<Enum>::enable, Enum>
    operator|(Enum const lhs, Enum const rhs)
    {
        using Underlying = std::underlying_type_t<Enum>;
        return static_cast<Enum>(static_cast<Underlying>(lhs) | static_cast<Underlying>(rhs));
    }

    template<typename Enum>
    constexpr std::enable_if_t<Minty::EnableEnumOperators<Enum>::enable, Enum>
    operator|=(Enum& lhs, Enum const rhs)
    {
        using Underlying = std::underlying_type_t<Enum>;
        lhs = static_cast<Enum>(static_cast<Underlying>(lhs) | static_cast<Underlying>(rhs));
        return lhs;
    }

    template<typename Enum>
    constexpr std::enable_if_t<Minty::EnableEnumOperators<Enum>::enable, Enum>
    operator&(Enum const lhs, Enum const rhs)
    {
        using Underlying = std::underlying_type_t<Enum>;
        return static_cast<Enum>(static_cast<Underlying>(lhs) & static_cast<Underlying>(rhs));
    }

    template<typename Enum>
    constexpr std::enable_if_t<Minty::EnableEnumOperators<Enum>::enable, Enum>
    operator&=(Enum& lhs, Enum const rhs)
    {
        using Underlying = std::underlying_type_t<Enum>;
        lhs = static_cast<Enum>(static_cast<Underlying>(lhs) & static_cast<Underlying>(rhs));
        return lhs;
    }

    template<typename Enum>
    constexpr std::enable_if_t<Minty::EnableEnumOperators<Enum>::enable, Enum>
    operator^(Enum const lhs, Enum const rhs)
    {
        using Underlying = std::underlying_type_t<Enum>;
        return static_cast<Enum>(static_cast<Underlying>(lhs) ^ static_cast<Underlying>(rhs));
    }

    template<typename Enum>
    constexpr std::enable_if_t<Minty::EnableEnumOperators<Enum>::enable, Enum>
    operator^=(Enum& lhs, Enum const rhs)
    {
        using Underlying = std::underlying_type_t<Enum>;
        lhs = static_cast<Enum>(static_cast<Underlying>(lhs) ^ static_cast<Underlying>(rhs));
        return lhs;
    }

    template<typename Enum>
    constexpr std::enable_if_t<Minty::EnableEnumOperators<Enum>::enable, Enum>
    operator~(Enum const value)
    {
        using Underlying = std::underlying_type_t<Enum>;
        return static_cast<Enum>(~static_cast<Underlying>(value));
    }
    
    template<typename Enum>
    constexpr std::enable_if_t<Minty::EnableEnumOperators<Enum>::enable, Enum>
    operator+(Enum const lhs, Enum const rhs)
    {
        using Underlying = std::underlying_type_t<Enum>;
        return static_cast<Enum>(static_cast<Underlying>(lhs) + static_cast<Underlying>(rhs));
    }

    template<typename Enum>
    constexpr std::enable_if_t<Minty::EnableEnumOperators<Enum>::enable, Enum>
    operator-(Enum const lhs, Enum const rhs)
    {
        using Underlying = std::underlying_type_t<Enum>;
        return static_cast<Enum>(static_cast<Underlying>(lhs) - static_cast<Underlying>(rhs));
    }

    template<typename Enum>
    constexpr std::enable_if_t<Minty::EnableEnumOperators<Enum>::enable, Bool>
    operator==(Enum const lhs, Enum const rhs)
    {
        using Underlying = std::underlying_type_t<Enum>;
        return static_cast<Bool>(static_cast<Underlying>(lhs) == static_cast<Underlying>(rhs));
    }

    template<typename Enum>
    constexpr std::enable_if_t<Minty::EnableEnumOperators<Enum>::enable, Bool>
    operator!=(Enum const lhs, Enum const rhs)
    {
        using Underlying = std::underlying_type_t<Enum>;
        return static_cast<Bool>(static_cast<Underlying>(lhs) != static_cast<Underlying>(rhs));
    }

    template<typename Enum>
    constexpr std::enable_if_t<Minty::EnableEnumOperators<Enum>::enable, Bool>
    operator<(Enum const lhs, Enum const rhs)
    {
        using Underlying = std::underlying_type_t<Enum>;
        return static_cast<Bool>(static_cast<Underlying>(lhs) < static_cast<Underlying>(rhs));
    }

    template<typename Enum>
    constexpr std::enable_if_t<Minty::EnableEnumOperators<Enum>::enable, Bool>
    operator>(Enum const lhs, Enum const rhs)
    {
        using Underlying = std::underlying_type_t<Enum>;
        return static_cast<Bool>(static_cast<Underlying>(lhs) > static_cast<Underlying>(rhs));
    }

    template<typename Enum>
    constexpr std::enable_if_t<Minty::EnableEnumOperators<Enum>::enable, Bool>
    operator<=(Enum const lhs, Enum const rhs)
    {
        using Underlying = std::underlying_type_t<Enum>;
        return static_cast<Bool>(static_cast<Underlying>(lhs) <= static_cast<Underlying>(rhs));
    }

    template<typename Enum>
    constexpr std::enable_if_t<Minty::EnableEnumOperators<Enum>::enable, Bool>
    operator>=(Enum const lhs, Enum const rhs)
    {
        using Underlying = std::underlying_type_t<Enum>;
        return static_cast<Bool>(static_cast<Underlying>(lhs) >= static_cast<Underlying>(rhs));
    }
}

#define MINTY_ENABLE_ENUM_OPERATORS(EnumType) \
    template<> \
    struct EnableEnumOperators<EnumType> \
    { \
        static constexpr Bool enable = true; \
    };