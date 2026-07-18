#pragma once

/**
 * @file Handle.h
 * @brief Header file for the Handle type.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include "Core/Constant/Invalid.hpp"
#include <functional>

namespace Minty
{
    template <typename T = void>
    struct Handle
    {
        union
        {
            struct
            {
                Generation generation;
                Index index;
            };
            UInt64 value;
        };
        
        constexpr Handle() : value(0) {}

        constexpr Handle(Generation const gen, Index const idx) : generation(gen), index(idx) {}

        constexpr Handle(UInt64 const value) : value(value) {}

        template<typename U>
        explicit constexpr Handle(Handle<U> const &other) : value(other.value) {}

        template<typename U>
        Handle<U> cast() const
        {
            return Handle<U>(value);
        }

        constexpr Bool operator==(Handle const &other) const
        {
            return value == other.value;
        }

        constexpr Bool operator!=(Handle const &other) const
        {
            return value != other.value;
        }

        constexpr Bool operator<(Handle const &other) const
        {
            return value < other.value;
        }

        constexpr Bool operator>(Handle const &other) const
        {
            return value > other.value;
        }

        constexpr Bool operator<=(Handle const &other) const
        {
            return value <= other.value;
        }

        constexpr Bool operator>=(Handle const &other) const
        {
            return value >= other.value;
        }

        explicit constexpr operator Bool() const
        {
            return value != INVALID_HANDLE;
        }

        constexpr Bool is_valid() const
        {
            return value != INVALID_HANDLE;
        }
    };
}

namespace std
{
    template <typename T>
    struct hash<Minty::Handle<T>>
    {
        size_t operator()(Minty::Handle<T> const &handle) const noexcept
        {
            return std::hash<Minty::UInt64>{}(handle.value);
        }
    };
}