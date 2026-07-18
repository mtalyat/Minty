#pragma once

/**
 * @file Severity.h
 * @brief Header file defining the Severity enum for logging and error handling.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include "Core/Type/Enum.hpp"

namespace Minty
{
    /**
     * @enum SeverityFlagsEnum
     * @brief Represents different levels of logging severity.
     */
    enum class SeverityFlagsEnum : UInt
    {
        /**
         * @brief No logging.
         */
        None = 0x0,

        /**
         * @brief Debug level for general debugging information.
         */
        Debug = 0x1,

        /**
         * @brief Info level for informational messages.
         */
        Info = 0x2,

        /**
         * @brief Message level for standard messages.
         */
        Message = 0x4,

        /**
         * @brief Warning level for potentially harmful situations.
         */
        Warning = 0x8,

        /**
         * @brief Error level for error events.
         */
        Error = 0x10,

        /**
         * @brief Critical level for critical conditions.
         */
        Critical = 0x20,

        Count = 7,

        /**
         * @brief All log levels enabled.
         */
        All = Debug | Info | Message | Warning | Error | Critical,

    /**
     * @brief Default log level based on build configuration.
     */
#ifdef MINTY_DEBUG
        Default = All,
#else
        Default = Warning | Error | Critical,
#endif
    };

    MINTY_ENABLE_ENUM_OPERATORS(SeverityFlagsEnum)

    struct SeverityFlags
    {
        SeverityFlagsEnum flags;

        constexpr SeverityFlags() : flags(SeverityFlagsEnum::Default) {}
        constexpr SeverityFlags(SeverityFlagsEnum flags) : flags(flags) {}
        constexpr operator SeverityFlagsEnum() const { return flags; }

        constexpr SeverityFlags operator|(SeverityFlagsEnum const other) const { return static_cast<SeverityFlagsEnum>(static_cast<UInt>(flags) | static_cast<UInt>(other)); }
        constexpr SeverityFlags operator&(SeverityFlagsEnum const other) const { return static_cast<SeverityFlagsEnum>(static_cast<UInt>(flags) & static_cast<UInt>(other)); }
        constexpr SeverityFlags operator^(SeverityFlagsEnum const other) const { return static_cast<SeverityFlagsEnum>(static_cast<UInt>(flags) ^ static_cast<UInt>(other)); }
        constexpr SeverityFlags operator~() const { return static_cast<SeverityFlagsEnum>(~static_cast<UInt>(flags)); }

        constexpr Bool has_flag(SeverityFlagsEnum const flag) const { return (static_cast<UInt>(flags) & static_cast<UInt>(flag)) != 0; }
    };
}