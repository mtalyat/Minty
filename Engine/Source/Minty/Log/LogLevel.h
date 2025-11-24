#ifndef MINTY_LOG_LOGLEVEL_H
#define MINTY_LOG_LOGLEVEL_H

#include "Minty/Core/Types.h"
#include "Minty/Core/Macro.h"
#include "Minty/Core/Enum.h"

namespace Minty
{
    /**
     * @enum LogLevel
     * @brief Represents different levels of logging severity.
     */
    enum class LogLevel : UInt
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

    MINTY_ENABLE_ENUM_OPERATORS(LogLevel)
}

#endif // MINTY_LOG_LOGLEVEL_H