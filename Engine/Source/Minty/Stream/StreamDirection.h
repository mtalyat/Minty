#ifndef MINTY_FILE_FILEDIRECTION_H
#define MINTY_FILE_FILEDIRECTION_H

/**
 * @file FileDirection.h
 * @brief Header file for file direction enumeration.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Enum.h"

namespace Minty
{
    /**
     * @enum FileDirection
     * @brief Enumeration for file seek directions.
     */
    enum class StreamDirection
    {
        /**
         * @brief Beginning of the file.
         */
        Begin = 0,

        /**
         * @brief Current position in the file.
         */
        Current = 1,

        /**
         * @brief End of the file.
         */
        End = 2
    };

    MINTY_ENABLE_ENUM_OPERATORS(StreamDirection)
}

#endif // MINTY_FILE_FILEDIRECTION_H