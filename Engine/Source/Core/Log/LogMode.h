#pragma once

#include "Platform/Type/Primitive.h"
#include "Platform/Macro/Build.h"
#include "Core/Serialize/Parser.h"

namespace Minty
{
    enum class LogModeEnum
    {
        /**
         * @brief No logging.
         */
        None = 0x0,

        /**
         * @brief Log to the console.
         */
        Console = 0x1,

        /**
         * @brief Log to a file.
         */
        File = 0x2,

        /**
         * @brief Log to both the console and a file.
         */
        Both = 0x3,

        /**
         * @brief Default log mode based on the build configuration.
         * In debug builds, the default is to log to both the console and a file.
         * In release builds, the default is to log to the console.
         */
#if defined(MINTY_DEBUG)
        Default = Both,
#else
        Default = Console,
#endif
    };

    struct LogMode
    {
        LogModeEnum value;

        constexpr LogMode() : value(LogModeEnum::Default) {}
        constexpr LogMode(LogModeEnum const mode) : value(mode) {}
        constexpr operator LogModeEnum() const { return value; }

        constexpr Bool operator==(LogModeEnum const mode) const { return value == mode; }
        constexpr Bool operator!=(LogModeEnum const mode) const { return value != mode; }

        constexpr Bool has_flag(LogModeEnum const mode) const { return (static_cast<Size>(value) & static_cast<Size>(mode)) != 0; }
    };

    template <>
    struct Parser<LogModeEnum>
    {
        static Bool parse(StringView const str, LogModeEnum &value);
        static String to_string(LogModeEnum const &value);
    };

    template<>
    struct Parser<LogMode>
    {
        static Bool parse(StringView const str, LogMode &value) { return Parser<LogModeEnum>::parse(str, value.value); }
        static String to_string(LogMode const &value) { return Parser<LogModeEnum>::to_string(value.value); }
    };
}