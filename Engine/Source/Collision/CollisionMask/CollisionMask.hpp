#pragma once

#include "Platform/Type/Primitive.hpp"
#include "Core/Serialize/Parser.hpp"

namespace Minty
{
    using CollisionType = UInt;
    using MaskType = UInt;

    constexpr CollisionType COLLISION_DEFAULT = 0;
    constexpr CollisionType COLLISION_COUNT = 32;

    constexpr MaskType MASK_DEFAULT = 0;
    constexpr MaskType MASK_NONE = 0;
    constexpr MaskType MASK_ALL = ~0;

    struct Collision;

    template<typename T = MaskType>
    struct Mask
    {
        T value;

        constexpr Mask() : value(MASK_DEFAULT) {}
        constexpr Mask(T mask) : value(mask) {}
        constexpr operator T() const { return value; }

        constexpr Mask operator~() const { return Mask(~value); }
        constexpr Bool operator&(Mask const &other) const { return (value & other.value) != 0; }
        constexpr Mask &operator&=(Mask const &other)
        {
            value &= other.value;
            return *this;
        }
        constexpr Bool operator|(Mask const &other) const { return (value | other.value) != 0; }
        constexpr Mask &operator|=(Mask const &other)
        {
            value |= other.value;
            return *this;
        }
        constexpr Mask operator^(Mask const &other) const { return Mask(value ^ other.value); }
        constexpr Mask &operator^=(Mask const &other)
        {
            value ^= other.value;
            return *this;
        }
        constexpr Bool operator==(Mask const &other) const { return value == other.value; }
        constexpr Bool operator!=(Mask const &other) const { return value != other.value; }
        constexpr Bool operator&(T const &other) const { return (value & other) != 0; }
        constexpr Mask &operator&=(T const &other)
        {
            value &= other;
            return *this;
        }
        constexpr Bool operator|(T const &other) const { return (value | other) != 0; }
        constexpr Mask &operator|=(T const &other)
        {
            value |= other;
            return *this;
        }
        constexpr Mask operator^(T const &other) const { return Mask(value ^ other); }
        constexpr Mask &operator^=(T const &other)
        {
            value ^= other;
            return *this;
        }
        constexpr Bool operator==(T const &other) const { return value == other; }
        constexpr Bool operator!=(T const &other) const { return value != other; }

        constexpr Bool has_collision(CollisionType const collision) const;
    };

    struct Collision
    {
        CollisionType value;

        constexpr Collision() : value(COLLISION_DEFAULT) {}
        constexpr Collision(CollisionType collision) : value(collision) {}
        constexpr operator CollisionType() const { return value; }

        constexpr Bool operator==(Collision const &other) const { return value == other.value; }
        constexpr Bool operator!=(Collision const &other) const { return value != other.value; }
        constexpr Bool operator<(Collision const &other) const { return value < other.value; }
        constexpr Bool operator>(Collision const &other) const { return value > other.value; }
        constexpr Bool operator<=(Collision const &other) const { return value <= other.value; }
        constexpr Bool operator>=(Collision const &other) const { return value >= other.value; }
        constexpr Bool operator==(CollisionType const &other) const { return value == other; }
        constexpr Bool operator!=(CollisionType const &other) const { return value != other; }
        constexpr Bool operator<(CollisionType const &other) const { return value < other; }
        constexpr Bool operator>(CollisionType const &other) const { return value > other; }
        constexpr Bool operator<=(CollisionType const &other) const { return value <= other; }
        constexpr Bool operator>=(CollisionType const &other) const { return value >= other; }

        template<typename T = MaskType>
        constexpr Mask<T> to_mask() const;
    };

    using CollisionMask = Mask<MaskType>;

    template<typename T>
    constexpr Bool Minty::Mask<T>::has_collision(CollisionType const collision) const
    {
        return (value & (1 << collision)) != 0;
    }

    template<typename T>
    constexpr Mask<T> Minty::Collision::to_mask() const
    {
        return Mask<T>(1 << value);
    }

    template<>
    struct Parser<Collision>
    {
        static Bool parse(StringView const str, Collision &value);
        static String to_string(Collision const &value);
    };

    template<>
    struct Parser<CollisionMask>
    {
        static Bool parse(StringView const str, CollisionMask &value);
        static String to_string(CollisionMask const &value);
    };
}