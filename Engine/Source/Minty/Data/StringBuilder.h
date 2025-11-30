#ifndef MINTY_STRING_BUILDER_H
#define MINTY_STRING_BUILDER_H

/**
 * @file StringBuilder.h
 * @brief Header file for string builder utilities.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Data/String.h"
#include "Minty/Data/StringView.h"
#include "Minty/Memory/AllocatorType.h"

namespace Minty
{
    class String;

    /**
     * @brief Class representing a string builder utility.
     */
    class StringBuilder
    {
#pragma region Constructors

    public:
        /**
         * @brief Constructs a StringBuilder with an optional allocator.
         * @param allocator The allocator to use for memory management. Default is Allocator::Default.
         */
        explicit StringBuilder();

        /**
         * @brief Constructs a StringBuilder with an initial capacity and an optional allocator.
         * @param initialCapacity The initial capacity of the string builder.
         * @param allocator The allocator to use for memory management. Default is Allocator::Default.
         */
        explicit StringBuilder(Size const initialCapacity);

        /**
         * @brief Constructs a StringBuilder with an initial string and an optional allocator.
         * @param initialString The initial string to initialize the string builder with.
         * @param allocator The allocator to use for memory management. Default is Allocator::Default.
         */
        StringBuilder(StringView const& initialString);
        
        ~StringBuilder();

#pragma endregion

#pragma region Accessors

    public:
        /**
         * @brief Gets a C-style string representing the current contents of the StringBuilder.
         * @return A pointer to the C-style string data.
         */
        Char const* get_data() const noexcept { return mp_data; }

        /**
         * @brief Gets the size of the StringBuilder.
         * @return The size.
         */
        Size get_size() const noexcept { return m_size; }

        /**
         * @brief Gets the length of the StringBuilder.
         * @return The length.
         */
        Size get_length() const noexcept { return m_size; }

        /**
         * @brief Gets the capacity of the StringBuilder.
         * @return The capacity.
         */
        Size get_capacity() const noexcept { return m_capacity; }

#pragma endregion

#pragma region Methods

        /**
         * @brief Reserves capacity for the StringBuilder.
         * @param newCapacity The new capacity to reserve.
         */
        void reserve(Size const newCapacity);

        /**
         * @brief Clears the contents of the StringBuilder.
         */
        void clear() noexcept;

        /**
         * @brief Appends a character to the end of the StringBuilder.
         * @param c The character to append.
         */
        void append(Char const c);

        /**
         * @brief Appends a string to the end of the StringBuilder.
         * @param str The string to append.
         */
        void append(StringView const& str);

        template<typename T>
        void append(T const& value)
        {
            append(Minty::to_string(value));
        }

        /**
		 * @brief Gets the character at the specified index.
		 * @param index Index of the character.
		 */
        Char index(Size const index) const;

		/**
		 * @brief Gets a const reference to the character at the specified index.
		 * @param index Index of the character.
		 */
		Char const& at(Size const index) const;

		/**
		 * @brief Gets a reference to the character at the specified index.
		 * @param index Index of the character.
		 */
        inline Char& at(Size const index) { return const_cast<Char&>(static_cast<StringBuilder const&>(*this).at(index)); }

		/**
		 * @brief Compares this String with another.
		 * @param other The other String to compare with.
		 * @return An integer less than, equal to, or greater than zero if this String is found, 
		 *  respectively, to be less than, to match, or be greater than the other String.
		 */
		Int compare(StringView const other) const noexcept;

		/**
		 * @brief Gets a reference to the first character.
		 * @return Reference to the first character.
		 */
		inline Char& front() { return at(0); }

		/**
		 * @brief Gets the first character.
		 * @return The first character.
		 */
		inline Char front() const { return at(0); }

		/**
		 * @brief Gets a reference to the last character.
		 * @return Reference to the last character.
		 */
		inline Char& back() { return at(m_size - 1); }

		/**
		 * @brief Gets the last character.
		 * @return The last character.
		 */
		inline Char back() const { return at(m_size - 1); }

		/**
		 * @brief Finds the first occurrence of a character or substring.
		 * @param c The character to find.
		 * @param startIndex The index to start the search from.
		 * @return The index of the first occurrence, or SIZE_MAX if not found.
		 */
		Size find_first(Char const c, Size const startIndex = 0) const noexcept;
		
		/**
		 * @brief Finds the first occurrence of a substring.
		 * @param str The substring to find.
		 * @param startIndex The index to start the search from.
		 * @return The index of the first occurrence, or INVALID_INDEX if not found.
		 */
		Size find_first(StringView const str, Size const startIndex = 0) const noexcept;

		/**
		 * @brief Finds the last occurrence of a character or substring.
		 * @param c The character to find.
		 * @param startIndex The index to start the search from.
		 * @return The index of the last occurrence, or INVALID_INDEX if not found.
		 */
		Size find_last(Char const c, Size const startIndex = INVALID_INDEX) const noexcept;
		
		/**
		 * @brief Finds the last occurrence of a substring.
		 * @param str The substring to find.
		 * @param startIndex The index to start the search from.
		 * @return The index of the last occurrence, or INVALID_INDEX if not found.
		 */
		Size find_last(StringView const str, Size const startIndex = INVALID_INDEX) const noexcept;

		/**
		 * @brief Finds the first occurrence of any character from a set.
		 * @param chars The set of characters to find.
		 * @param startIndex The index to start the search from.
		 * @return The index of the first occurrence, or INVALID_INDEX if not found.
		 */
		Size find_first_of(StringView const chars, Size const startIndex = 0) const noexcept;

		/**
		 * @brief Finds the last occurrence of any character from a set.
		 * @param chars The set of characters to find.
		 * @param startIndex The index to start the search from.
		 * @return The index of the last occurrence, or INVALID_INDEX if not found.
		 */
		Size find_last_of(StringView const chars, Size const startIndex = INVALID_INDEX) const noexcept;

		/**
		 * @brief Finds the first occurrence of any character not in a set.
		 * @param chars The set of characters to exclude.
		 * @param startIndex The index to start the search from.
		 * @return The index of the first occurrence, or INVALID_INDEX if not found.
		 */
		Size find_first_not_of(StringView const chars, Size const startIndex = 0) const noexcept;

		/**
		 * @brief Finds the last occurrence of any character not in a set.
		 * @param chars The set of characters to exclude.
		 * @param startIndex The index to start the search from.
		 * @return The index of the last occurrence, or INVALID_INDEX if not found.
		 */
		Size find_last_not_of(StringView const chars, Size const startIndex = INVALID_INDEX) const noexcept;

		/**
		 * @brief Extracts a substring from the string.
		 * @param startIndex The starting index of the substring.
		 * @param count The number of characters to include in the substring.
		 * @return The extracted substring.
		 */
		String sub(Size const startIndex, Size const count = INVALID_INDEX) const noexcept;

		/**
		 * @brief Checks if the string starts with a given substring.
		 * @param str The substring to check.
		 * @return True if the string starts with the substring, false otherwise.
		 */
		Bool starts_with(StringView const str) const noexcept;

		/**
		 * @brief Checks if the string ends with a given substring.
		 * @param str The substring to check.
		 * @return True if the string ends with the substring, false otherwise.
		 */
		Bool ends_with(StringView const str) const noexcept;

        /**
         * @brief Converts all characters in the StringBuilder to lowercase.
         */
        void to_lower();

        /**
         * @brief Converts all characters in the StringBuilder to uppercase.
         */
        void to_upper();

        /**
         * @brief Trims characters from the start of the StringBuilder.
         * @param chars The set of characters to trim. Default is whitespace characters.
         */
        void trim_start(StringView const chars = TEXT_WHITESPACE);

        /**
         * @brief Trims characters from the end of the StringBuilder.
         * @param chars The set of characters to trim. Default is whitespace characters.
         */
        void trim_end(StringView const chars = TEXT_WHITESPACE);

        /**
         * @brief Trims characters from both the start and end of the StringBuilder.
         * @param chars The set of characters to trim. Default is whitespace characters.
         */
        void trim(StringView const chars = TEXT_WHITESPACE);

        /**
         * @brief Strips characters from the StringBuilder.
         * @param chars The set of characters to strip. Default is whitespace characters.
         */
        void strip(StringView const chars = TEXT_WHITESPACE);

        /**
         * @brief Replaces occurrences of a target string with a replacement string in the StringBuilder.
         * @param target The string to be replaced.
         * @param replacement The string to replace with.
         */
        void replace(StringView const target, StringView const replacement);

        /**
         * @brief Converts the StringBuilder to a StringView.
         * @return The resulting StringView.
         */
        inline StringView to_view() const { return StringView(mp_data, m_size); }

        /**
         * @brief Converts the StringBuilder to a String.
         * @return The resulting String.
         */
        inline String to_string() const { return String(to_view()); }

#pragma endregion

#pragma region Variables

    private:
        Char* mp_data;
        Size m_size;
        Size m_capacity;

#pragma endregion
    };
}

#endif // MINTY_STRING_BUILDER_H