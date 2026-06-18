#pragma once

/**
 * @file FileFlags.h
 * @brief Header file for file flag definitions.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.h"
#include "Core/Serialize/Parser.h"
#include "Core/Type/Enum.h"

namespace Minty
{
    /**
     * @enum FileFlagsEnum
     * @brief Enumeration for file access and mode flags.
     */
    enum class FileFlagsEnum : UInt
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

    MINTY_ENABLE_ENUM_OPERATORS(FileFlagsEnum)

    struct FileFlags
    {
        FileFlagsEnum value;

        constexpr FileFlags() : value(FileFlagsEnum::None) {}
        constexpr FileFlags(FileFlagsEnum f) : value(f) {}
        constexpr FileFlagsEnum operator()() const { return value; }

        constexpr FileFlags operator|(FileFlagsEnum other) const { return value | other; }
        constexpr FileFlags operator&(FileFlagsEnum other) const { return value & other; }
        constexpr FileFlags operator~() const { return ~value; }

        constexpr Bool has_flag(FileFlagsEnum flag) const
        {
            return (value & flag) == flag;
        }
    };

    template <>
    struct Parser<FileFlagsEnum>
    {
        static Bool parse(StringView const str, FileFlagsEnum &value);
        static String to_string(FileFlagsEnum const &value);
    };

    template<>
    struct Parser<FileFlags>
    {
        inline static Bool parse(StringView const str, FileFlags &value) { return Parser<FileFlagsEnum>::parse(str, value.value); }
        inline static String to_string(FileFlags const &value) { return Parser<FileFlagsEnum>::to_string(value.value); }
    };
}
