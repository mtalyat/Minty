#pragma once

#include "Core/Type/Severity.h"
#include "Core/Data/Path.h"
#include "Core/Log/LogMode.h"

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
        SeverityFlags enabledLevels = SeverityFlagsEnum::Default;

        /**
         * @brief The log mode that determines where to log messages (console, file, or both).
         */
        LogMode logMode = LogModeEnum::Default;

        /**
         * @brief The file path for the log file.
         */
        Path path = {};
    };
}