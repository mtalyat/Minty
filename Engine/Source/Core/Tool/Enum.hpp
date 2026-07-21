#pragma once

/**
 * @file Enum.hpp
 * @brief Header file defining macros for enum classes.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.hpp"
#include "Core/Data/StringView.hpp"
#include "Core/Data/String.hpp"

namespace Minty
{
    namespace Internal
    {
        /**
         * @brief Parses a string view to get the corresponding enum value.
         * @param view The string view representing the enum.
         * @param enumStrings An array of C-style strings representing the enum names.
         * @param enumCount The number of enum entries.
         * @return The corresponding enum value, or enumCount if not found.
         */
        Size parse_enum(StringView const view, Char const *const *const enumStrings, Size const enumCount);

        /**
         * @brief Tries to parse a string view to get the corresponding enum value.
         * @param view The string view representing the enum.
         * @param enumStrings An array of C-style strings representing the enum names.
         * @param enumCount The number of enum entries.
         * @param outValue Reference to store the parsed enum value.
         * @return True if parsing was successful, false otherwise.
         */
        Bool try_parse_enum(StringView const view, Char const *const *const enumStrings, Size const enumCount, Size &outValue);

        /**
         * @brief Parses a string view to get the corresponding enum flags value.
         * @param view The string view representing the enum flags.
         * @param enumStrings An array of C-style strings representing the enum names.
         * @param enumCount The number of enum entries.
         * @return The corresponding enum flags value.
         */
        Size parse_enum_flags(StringView const view, Char const *const *const enumStrings, Size const enumCount);

        /**
         * @brief Tries to parse a string view to get the corresponding enum flags value.
         * @param view The string view representing the enum flags.
         * @param enumStrings An array of C-style strings representing the enum names.
         * @param enumCount The number of enum entries.
         * @param outValue Reference to store the parsed enum flags value.
         * @return True if parsing was successful, false otherwise.
         */
        Bool try_parse_enum_flags(StringView const view, Char const *const *const enumStrings, Size const enumCount, Size &outValue);

        /**
         * @brief Converts an enum value to its string representation.
         * @param value The enum value.
         * @param enumStrings An array of C-style strings representing the enum names.
         * @param enumCount The number of enum entries.
         * @return The string representation of the enum value.
         */
        String to_string_enum(Size const value, Char const *const *const enumStrings, Size const enumCount);

        /**
         * @brief Converts an enum flags value to its string representation.
         * @param value The enum flags value.
         * @param enumStrings An array of C-style strings representing the enum names.
         * @param enumCount The number of enum entries.
         * @return The string representation of the enum flags value.
         */
        String to_string_enum_flags(Size const value, Char const *const *const enumStrings, Size const enumCount);
    }

    namespace Tool
    {
        /**
         * @brief Parses a string view to get the corresponding enum value of type T.
         * @tparam T The enum type.
         * @param view The string view representing the enum.
         * @param enumStrings An array of C-style strings representing the enum names.
         * @param enumCount The number of enum entries.
         * @return The corresponding enum value of type T.
         */
        template<typename T>
        inline T parse_enum(StringView const view, Char const *const *const enumStrings, Size const enumCount)
        {
            return static_cast<T>(Internal::parse_enum(view, enumStrings, enumCount));
        }

        /**
         * @brief Tries to parse a string view to get the corresponding enum value of type T.
         * @tparam T The enum type.
         * @param view The string view representing the enum.
         * @param enumStrings An array of C-style strings representing the enum names.
         * @param enumCount The number of enum entries.
         * @param outValue Reference to store the parsed enum value of type T.
         * @return True if parsing was successful, false otherwise.
         */
        template<typename T>
        inline Bool try_parse_enum(StringView const view, Char const *const *const enumStrings, Size const enumCount, T &outValue)
        {
            Size tempValue;
            Bool result = Internal::try_parse_enum(view, enumStrings, enumCount, tempValue);
            outValue = static_cast<T>(tempValue);
            return result;
        }

        /**
         * @brief Parses a string view to get the corresponding enum flags value of type T.
         * @tparam T The enum type.
         * @param view The string view representing the enum flags.
         * @param enumStrings An array of C-style strings representing the enum names.
         * @param enumCount The number of enum entries.
         * @return The corresponding enum flags value of type T.
         */
        template<typename T>
        inline T parse_enum_flags(StringView const view, Char const *const *const enumStrings, Size const enumCount)
        {
            return static_cast<T>(Internal::parse_enum_flags(view, enumStrings, enumCount));
        }

        /**
         * @brief Tries to parse a string view to get the corresponding enum flags value of type T.
         * @tparam T The enum type.
         * @param view The string view representing the enum flags.
         * @param enumStrings An array of C-style strings representing the enum names.
         * @param enumCount The number of enum entries.
         * @param outValue Reference to store the parsed enum flags value of type T.
         * @return True if parsing was successful, false otherwise.
         */
        template<typename T>
        inline Bool try_parse_enum_flags(StringView const view, Char const *const *const enumStrings, Size const enumCount, T &outValue)
        {
            Size tempValue;
            Bool result = Internal::try_parse_enum_flags(view, enumStrings, enumCount, tempValue);
            outValue = static_cast<T>(tempValue);
            return result;
        }

        /**
         * @brief Converts an enum value of type T to its string representation.
         * @tparam T The enum type.
         * @param value The enum value of type T.
         * @param enumStrings An array of C-style strings representing the enum names.
         * @param enumCount The number of enum entries.
         * @return The string representation of the enum value.
         */
        template<typename T>
        inline String to_string_enum(T const value, Char const *const *const enumStrings, Size const enumCount)
        {
            return Internal::to_string_enum(static_cast<Size>(value), enumStrings, enumCount);
        }

        /**
         * @brief Converts an enum flags value of type T to its string representation.
         * @tparam T The enum type.
         * @param value The enum flags value of type T.
         * @param enumStrings An array of C-style strings representing the enum names.
         * @param enumCount The number of enum entries.
         * @return The string representation of the enum flags value.
         */
        template<typename T>
        inline String to_string_enum_flags(T const value, Char const *const *const enumStrings, Size const enumCount)
        {
            return Internal::to_string_enum_flags(static_cast<Size>(value), enumStrings, enumCount);
        }
    }
}
