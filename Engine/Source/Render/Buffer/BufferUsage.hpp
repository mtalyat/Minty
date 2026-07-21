#pragma once

/**
 * @file BufferUsage.hpp
 * @brief Header file defining the BufferUsage enum.
 * @author Mitchell Talyat
 */

#include "Core/Serialize/Parser.hpp"
#include "Core/Type/Enum.hpp"

namespace Minty
{
    /**
	 * @brief Describes how a buffer is used.
     */
    enum class BufferUsageFlagsEnum
    {
        /**
         * @brief Invalid.
         */
        Undefined = 0x0,

        /**
		 * @brief Transfer source buffer.
         */
        TransferSrc = 0x1,

        /**
         * @brief Transfer destination buffer.
         */
        TransferDst = 0x2,

        /**
		 * @brief Vertex buffer.
         */
        Vertex = 0x4,

        /**
		 * @brief Index buffer.
         */
        Index = 0x8,

        /**
		 * @brief Uniform buffer.
         */
        Uniform =  0x10,

        Count = 5,

		Max = Uniform,
    };

    MINTY_ENABLE_ENUM_OPERATORS(BufferUsageFlagsEnum)

    struct BufferUsageFlags
    {
        BufferUsageFlagsEnum value = BufferUsageFlagsEnum::Undefined;

        constexpr BufferUsageFlags() = default;
        constexpr BufferUsageFlags(BufferUsageFlagsEnum const usage) : value(usage) {}
        constexpr operator BufferUsageFlagsEnum() const { return value; }

        constexpr Bool has_flag(BufferUsageFlagsEnum const flag) const
        {
            return (value & flag) != BufferUsageFlagsEnum::Undefined;
        }
    };

    template<>
    struct Parser<BufferUsageFlagsEnum>
    {
        static Bool parse(StringView const str, BufferUsageFlagsEnum& value);
        static String to_string(BufferUsageFlagsEnum const& obj);
    };

    template<>
    struct Parser<BufferUsageFlags>
    {
        inline static Bool parse(StringView const str, BufferUsageFlags& value) { return Parser<BufferUsageFlagsEnum>::parse(str, value.value); }
        inline static String to_string(BufferUsageFlags const& obj) { return Parser<BufferUsageFlagsEnum>::to_string(obj.value); }
    };
}
