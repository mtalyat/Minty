#pragma once

/**
 * @file TextureFilter.hpp
 * @brief TextureFilter enum definition.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include "Core/Serialize/Parser.hpp"
#include "Core/Type/Enum.hpp"

namespace Minty
{
    enum class TextureFilterEnum
    {
        Undefined,
        Nearest, // No interpolation, pixelated look
        Linear,  // Bilinear interpolation, smooth look
        // Anisotropic, // Anisotropic filtering for improved quality at oblique angles

        Count,

        Default = Linear // Default filter to use when one is not specified
    };

    MINTY_ENABLE_ENUM_OPERATORS(TextureFilterEnum)

    struct TextureFilter
    {
        TextureFilterEnum value;

        constexpr TextureFilter()
            : value(TextureFilterEnum::Undefined)
        {
        }

        constexpr TextureFilter(TextureFilterEnum const filter)
            : value(filter)
        {
        }

        constexpr TextureFilter(UInt32 const filter)
            : value(static_cast<TextureFilterEnum>(filter))
        {
        }

        constexpr operator TextureFilterEnum() const
        {
            return value;
        }

        constexpr operator UInt32() const
        {
            return static_cast<UInt32>(value);
        }

        constexpr Bool operator==(TextureFilterEnum const &other) const
        {
            return value == other;
        }

        constexpr Bool operator!=(TextureFilterEnum const &other) const
        {
            return value != other;
        }
    };
	
	template<>
	struct Parser<TextureFilterEnum>
	{
		static Bool parse(StringView const str, TextureFilterEnum& value);
		static String to_string(TextureFilterEnum const& obj);
	};
	
	template<>
	struct Parser<TextureFilter>
	{
		inline static Bool parse(StringView const str, TextureFilter& value) { return Parser<TextureFilterEnum>::parse(str, value.value); }
		inline static String to_string(TextureFilter const& obj) { return Parser<TextureFilterEnum>::to_string(obj.value); }
	};
}