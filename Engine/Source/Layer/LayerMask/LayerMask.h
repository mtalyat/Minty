#pragma once

#include "Platform/Type/Primitive.h"
#include "Core/Serialize/Parser.h"

namespace Minty
{
    using LayerType = UInt;
    using MaskType = UInt;

    constexpr LayerType LAYER_DEFAULT = 0;
    constexpr LayerType LAYER_COUNT = 32;

    constexpr MaskType MASK_DEFAULT = 0;
    constexpr MaskType MASK_NONE = 0;
    constexpr MaskType MASK_ALL = ~0;

    struct Layer;

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

        constexpr Bool has_layer(LayerType const layer) const;
    };

    struct Layer
    {
        LayerType value;

        constexpr Layer() : value(LAYER_DEFAULT) {}
        constexpr Layer(LayerType layer) : value(layer) {}
        constexpr operator LayerType() const { return value; }

        constexpr Bool operator==(Layer const &other) const { return value == other.value; }
        constexpr Bool operator!=(Layer const &other) const { return value != other.value; }
        constexpr Bool operator<(Layer const &other) const { return value < other.value; }
        constexpr Bool operator>(Layer const &other) const { return value > other.value; }
        constexpr Bool operator<=(Layer const &other) const { return value <= other.value; }
        constexpr Bool operator>=(Layer const &other) const { return value >= other.value; }
        constexpr Bool operator==(LayerType const &other) const { return value == other; }
        constexpr Bool operator!=(LayerType const &other) const { return value != other; }
        constexpr Bool operator<(LayerType const &other) const { return value < other; }
        constexpr Bool operator>(LayerType const &other) const { return value > other; }
        constexpr Bool operator<=(LayerType const &other) const { return value <= other; }
        constexpr Bool operator>=(LayerType const &other) const { return value >= other; }

        template<typename T = MaskType>
        constexpr Mask<T> to_mask() const;
    };

    using LayerMask = Mask<MaskType>;

    template<typename T>
    constexpr Bool Minty::Mask<T>::has_layer(LayerType const layer) const
    {
        return (value & (1 << layer)) != 0;
    }

    template<typename T>
    constexpr Mask<T> Minty::Layer::to_mask() const
    {
        return Mask<T>(1 << value);
    }

    template<>
    struct Parser<Layer>
    {
        static Bool parse(StringView const str, Layer &value);
        static String to_string(Layer const &value);
    };

    template<>
    struct Parser<LayerMask>
    {
        static Bool parse(StringView const str, LayerMask &value);
        static String to_string(LayerMask const &value);
    };
}