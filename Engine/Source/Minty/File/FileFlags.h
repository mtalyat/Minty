#ifndef MINTY_FILE_FILEFLAGS_H
#define MINTY_FILE_FILEFLAGS_H

/**
 * @file FileFlags.h
 * @brief Header file for file flag definitions.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Enum.h"
#include "Minty/Serialization/Parser.h"

namespace Minty
{
    /**
     * @enum FileFlags
     * @brief Enumeration for file access and mode flags.
     */
    enum class FileFlags
    {
        /**
         * @brief No flags set.
         */
        None = 0x0,

        /**
         * @brief Open file for reading.
         */
        Read = 0x1,

        /**
         * @brief Open file for writing.
         */
        Write = 0x2,

        /**
         * @brief Open file for both reading and writing.
         */
        ReadWrite = 0x3,

        /**
         * @brief Set the file position to the end when opened.
         */
        AtEnd = 0x4,

        /**
         * @brief Open file in append mode.
         */
        Append = 0x8,

        /**
         * @brief Open file in binary mode.
         */
        Binary = 0x10,

        /**
         * @brief Truncate file to zero length if it exists.
         */
        Truncate = 0x20,
    };

    MINTY_ENABLE_ENUM_OPERATORS(FileFlags)
    
    template<>
    struct Parser<FileFlags>
    {
        static Bool parse(StringView const str, FileFlags &value);
        static String to_string(FileFlags const &value);
    };
}

#endif // MINTY_FILE_FILEFLAGS_H