#pragma once

/**
 * @file StreamDirection.hpp
 * @brief Header file for stream direction enumeration.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include "Core/Type/Enum.hpp"

namespace Minty
{
    /**
     * @enum StreamDirectionEnum
     * @brief Enumeration for stream seek directions.
     */
    enum class StreamDirectionEnum
    {
        /**
         * @brief Beginning of the stream.
         */
        Begin = 0,

        /**
         * @brief Current position in the stream.
         */
        Current = 1,

        /**
         * @brief End of the stream.
         */
        End = 2,

        Count,

        Default = Begin
    };

    MINTY_ENABLE_ENUM_OPERATORS(StreamDirectionEnum)

    struct StreamDirection
    {
        StreamDirectionEnum direction;

        constexpr StreamDirection() : direction(StreamDirectionEnum::Default) {}
        constexpr StreamDirection(StreamDirectionEnum d) : direction(d) {}
        constexpr StreamDirectionEnum operator()() const { return direction; }
    };
}
