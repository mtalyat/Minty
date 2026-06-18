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

    struct Mask
    {
        MaskType value;

        constexpr Mask() : value(MASK_DEFAULT) {}
        constexpr Mask(MaskType mask) : value(mask) {}
        constexpr operator MaskType() const { return value; }

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
        constexpr Bool operator&(MaskType const &other) const { return (value & other) != 0; }
        constexpr Mask &operator&=(MaskType const &other)
        {
            value &= other;
            return *this;
        }
        constexpr Bool operator|(MaskType const &other) const { return (value | other) != 0; }
        constexpr Mask &operator|=(MaskType const &other)
        {
            value |= other;
            return *this;
        }
        constexpr Mask operator^(MaskType const &other) const { return Mask(value ^ other); }
        constexpr Mask &operator^=(MaskType const &other)
        {
            value ^= other;
            return *this;
        }
        constexpr Bool operator==(MaskType const &other) const { return value == other; }
        constexpr Bool operator!=(MaskType const &other) const { return value != other; }

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

        constexpr Mask to_mask() const;
    };

    constexpr Bool Minty::Mask::has_layer(LayerType const layer) const
    {
        return (value & (1 << layer)) != 0;
    }

    constexpr Mask Minty::Layer::to_mask() const
    {
        return Mask(1 << value);
    }

    template<>
    struct Parser<Layer>
    {
        static Bool parse(StringView const str, Layer &value);
        static String to_string(Layer const &value);
    };

    template<>
    struct Parser<Mask>
    {
        static Bool parse(StringView const str, Mask &value);
        static String to_string(Mask const &value);
    };
}