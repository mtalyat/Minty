#ifndef MINTY_TOOL_ENUM_H
#define MINTY_TOOL_ENUM_H

/**
 * @file Enum.h
 * @brief Header file defining macros for enum classes.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Data/StringView.h"
#include "Minty/Data/String.h"

namespace Minty::Tool
{
    /**
     * @brief Parses a string view to get the corresponding enum value.
     * @param view The string view representing the enum.
     * @param enumStrings An array of C-style strings representing the enum names.
     * @param enumCount The number of enum entries.
     * @return The corresponding enum value, or enumCount if not found.
     */
    Size parse_enum(StringView const view, Char const* const* const enumStrings, Size const enumCount);

    /**
     * @brief Tries to parse a string view to get the corresponding enum value.
     * @param view The string view representing the enum.
     * @param enumStrings An array of C-style strings representing the enum names.
     * @param enumCount The number of enum entries.
     * @param outValue Reference to store the parsed enum value.
     * @return True if parsing was successful, false otherwise.
     */
    Bool try_parse_enum(StringView const view, Char const* const* const enumStrings, Size const enumCount, Size& outValue);

    /**
     * @brief Parses a string view to get the corresponding enum flags value.
     * @param view The string view representing the enum flags.
     * @param enumStrings An array of C-style strings representing the enum names.
     * @param enumCount The number of enum entries.
     * @return The corresponding enum flags value.
     */
    Size parse_enum_flags(StringView const view, Char const* const* const enumStrings, Size const enumCount);

    /**
     * @brief Tries to parse a string view to get the corresponding enum flags value.
     * @param view The string view representing the enum flags.
     * @param enumStrings An array of C-style strings representing the enum names.
     * @param enumCount The number of enum entries.
     * @param outValue Reference to store the parsed enum flags value.
     * @return True if parsing was successful, false otherwise.
     */
    Bool try_parse_enum_flags(StringView const view, Char const* const* const enumStrings, Size const enumCount, Size& outValue);

    /**
     * @brief Converts an enum value to its string representation.
     * @param value The enum value.
     * @param enumStrings An array of C-style strings representing the enum names.
     * @param enumCount The number of enum entries.
     * @return The string representation of the enum value.
     */
    String to_string_enum(Size const value, Char const* const* const enumStrings, Size const enumCount);

    /**
     * @brief Converts an enum flags value to its string representation.
     * @param value The enum flags value.
     * @param enumStrings An array of C-style strings representing the enum names.
     * @param enumCount The number of enum entries.
     * @return The string representation of the enum flags value.
     */
    String to_string_enum_flags(Size const value, Char const* const* const enumStrings, Size const enumCount);
}

#endif // MINTY_TOOL_ENUM_H