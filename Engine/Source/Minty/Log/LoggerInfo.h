#ifndef MINTY_LOG_LOGGERINFO_H
#define MINTY_LOG_LOGGERINFO_H

#include "Minty/Log/LogLevel.h"

namespace Minty
{
    /**
     * @struct LoggerInfo
     * @brief Configuration information for the Logger.
     */
    struct LoggerInfo
    {
        /**
         * @brief The log levels that are enabled for logging.
         */
        LogLevel enabledLevels = LogLevel::Default;
    };
}

#endif // MINTY_LOG_LOGGERINFO_H