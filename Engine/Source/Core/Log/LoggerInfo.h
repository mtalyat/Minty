#pragma once

#include "Core/Type/Severity.h"

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
    };
}