#ifndef MINTY_TOOL_STRING_H
#define MINTY_TOOL_STRING_H

/**
 * @file String.h
 * @brief Header file for string utilities in the Minty Tool module.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Data/String.h"
#include "Minty/Data/StringView.h"
#include "Minty/Data/Tuple.h"
#include "Minty/Data/Vector.h"

namespace Minty::Tool
{
    /**
     * @brief Finds the first occurrence of a character or substring.
     * @param text The text to search within.
     * @param length The length of the text.
     * @param c The character to find.
     * @param startIndex The index to start the search from.
     * @return The index of the first occurrence, or SIZE_MAX if not found.
     */
    Size find_first(Char const* const text, Size const length, Char const c, Size const startIndex = 0) noexcept;

    /**
     * @brief Finds the first occurrence of a substring.
     * @param text The text to search within.
     * @param length The length of the text.
     * @param str The substring to find.
     * @param startIndex The index to start the search from.
     * @return The index of the first occurrence, or INVALID_INDEX if not found.
     */
    Size find_first(Char const* const text, Size const length, StringView const str, Size const startIndex = 0) noexcept;

    /**
     * @brief Finds the last occurrence of a character or substring.
     * @param text The text to search within.
     * @param length The length of the text.
     * @param c The character to find.
     * @param startIndex The index to start the search from.
     * @return The index of the last occurrence, or INVALID_INDEX if not found.
     */
    Size find_last(Char const* const text, Size const length, Char const c, Size const startIndex = INVALID_INDEX) noexcept;

    /**
     * @brief Finds the last occurrence of a substring.
     * @param text The text to search within.
     * @param length The length of the text.
     * @param str The substring to find.
     * @param startIndex The index to start the search from.
     * @return The index of the last occurrence, or INVALID_INDEX if not found.
     */
    Size find_last(Char const* const text, Size const length, StringView const str, Size const startIndex = INVALID_INDEX) noexcept;

    /**
     * @brief Finds the first occurrence of any character from a set.
     * @param text The text to search within.
     * @param length The length of the text.
     * @param chars The set of characters to find.
     * @param startIndex The index to start the search from.
     * @return The index of the first occurrence, or INVALID_INDEX if not found.
     */
    Size find_first_of(Char const* const text, Size const length, StringView const chars, Size const startIndex = 0) noexcept;

    /**
     * @brief Finds the last occurrence of any character from a set.
     * @param text The text to search within.
     * @param length The length of the text.
     * @param chars The set of characters to find.
     * @param startIndex The index to start the search from.
     * @return The index of the last occurrence, or INVALID_INDEX if not found.
     */
    Size find_last_of(Char const* const text, Size const length, StringView const chars, Size const startIndex = INVALID_INDEX) noexcept;

    /**
     * @brief Finds the first occurrence of any character not in a set.
     * @param text The text to search within.
     * @param length The length of the text.
     * @param chars The set of characters to exclude.
     * @param startIndex The index to start the search from.
     * @return The index of the first occurrence, or INVALID_INDEX if not found.
     */
    Size find_first_not_of(Char const* const text, Size const length, StringView const chars, Size const startIndex = 0) noexcept;

    /**
     * @brief Finds the last occurrence of any character not in a set.
     * @param text The text to search within.
     * @param length The length of the text.
     * @param chars The set of characters to exclude.
     * @param startIndex The index to start the search from.
     * @return The index of the last occurrence, or INVALID_INDEX if not found.
     */
    Size find_last_not_of(Char const* const text, Size const length, StringView const chars, Size const startIndex = INVALID_INDEX) noexcept;

    /**
     * @brief Checks if the text starts with a given character or substring.
     * @param text The text to check.
     * @param length The length of the text.
     * @param c The character to check.
     * @return True if the text starts with the character, false otherwise.
     */
    inline Bool starts_with(Char const* const text, Size const length, Char const c) noexcept { return length > 0 && text[0] == c; }

    /**
     * @brief Checks if the text starts with a given substring.
     * @param text The text to check.
     * @param length The length of the text.
     * @param str The substring to check.
     * @return True if the text starts with the substring, false otherwise.
     */
    Bool starts_with(Char const* const text, Size const length, StringView const str) noexcept;

    /**
     * @brief Checks if the text ends with a given character or substring.
     * @param text The text to check.
     * @param length The length of the text.
     * @param c The character to check.
     * @return True if the text ends with the character, false otherwise.
     */
    inline Bool ends_with(Char const* const text, Size const length, Char const c) noexcept { return length > 0 && text[length - 1] == c; }

    /**
     * @brief Checks if the text ends with a given substring.
     * @param text The text to check.
     * @param length The length of the text.
     * @param str The substring to check.
     * @return True if the text ends with the substring, false otherwise.
     */
    Bool ends_with(Char const* const text, Size const length, StringView const str) noexcept;

    /**
     * @brief Compares the text with another substring.
     * @param text The text to compare.
     * @param length The length of the text.
     * @param other The substring to compare with.
     * @return Negative value if text < other, zero if text == other, positive value if text > other.
     */
    Int compare(Char const* const text, Size const length, StringView const other) noexcept;

    Tuple<Size, Size> find_group(String const &str, Char const open, Char const close, Size const index = 0);

    Vector<Tuple<Size, Size>> find_groups(String const &str, Char const open, Char const close, Size const index = 0);

    Vector<String> split_by_indices(String const &str, Vector<Size> const &indices, Size delimiterSize);

    Vector<String> split(String const &str, Char const delimiter);

    Vector<String> split_smart(String const &str, Char const delimiter, String const &open = TEXT_OPEN, String const &close = TEXT_CLOSE);

    Vector<String> split(String const &str, String const &delimiter);

    Vector<String> split_smart(String const &str, String const &delimiter, String const &open = TEXT_OPEN, String const &close = TEXT_CLOSE);

    Vector<String> split(String const &str);

    Vector<String> split_lines(String const &str);

    // Converts a string to a safe string by escaping special characters.
    String to_safe_string(StringView const str);

    // Converts a string to an unsafe string by unescaping special characters.
    String to_unsafe_string(StringView const str);
}

#endif // MINTY_TOOL_STRING_H