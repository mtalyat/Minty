#ifndef MINTY_TOOL_STRING_H
#define MINTY_TOOL_STRING_H

/**
 * @file String.h
 * @brief Header file for string utilities in the Minty Tool module.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.h"
#include "Core/Data/String.h"
#include "Core/Data/StringView.h"
#include "Core/Data/Tuple.h"
#include "Core/Data/Vector.h"
#include "Core/Constant/Default.h"

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
    Size find_last(Char const* const text, Size const length, Char const c, Size const startIndex = INVALID_SIZE) noexcept;

    /**
     * @brief Finds the last occurrence of a substring.
     * @param text The text to search within.
     * @param length The length of the text.
     * @param str The substring to find.
     * @param startIndex The index to start the search from.
     * @return The index of the last occurrence, or INVALID_INDEX if not found.
     */
    Size find_last(Char const* const text, Size const length, StringView const str, Size const startIndex = INVALID_SIZE) noexcept;

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
    Size find_last_of(Char const* const text, Size const length, StringView const chars, Size const startIndex = INVALID_SIZE) noexcept;

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
    Size find_last_not_of(Char const* const text, Size const length, StringView const chars, Size const startIndex = INVALID_SIZE) noexcept;

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

    Tuple<Size, Size> find_group(StringView const str, Char const open, Char const close, Size const index = 0);

    Vector<Tuple<Size, Size>> find_groups(StringView const str, Char const open, Char const close, Size const index = 0);

    Vector<StringView> split_by_indices(StringView const str, Vector<Size> const &indices, Size delimiterSize);

    Vector<StringView> split(StringView const str, Char const delimiter);

    Vector<StringView> split_smart(StringView const str, Char const delimiter, StringView const open = DEFAULT_TEXT_OPEN, StringView const close = DEFAULT_TEXT_CLOSE);

    Vector<StringView> split(StringView const str, StringView const delimiter);

    Vector<StringView> split_smart(StringView const str, StringView const delimiter, StringView const open = DEFAULT_TEXT_OPEN, StringView const close = DEFAULT_TEXT_CLOSE);

    inline Vector<StringView> split(StringView const str) { return split(str, DEFAULT_TEXT_WHITESPACE); }

    Vector<StringView> split_lines(StringView const str);

    // Converts a string to a safe string by escaping special characters.
    String to_safe_string(StringView const str);

    // Converts a string to an unsafe string by unescaping special characters.
    String to_unsafe_string(StringView const str);
}

#endif // MINTY_TOOL_STRING_H