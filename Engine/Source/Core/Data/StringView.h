#pragma once

/**
 * @file StringView.h
 * @brief Header file for the StringView class, which provides a non-owning view of a string.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.h"
#include "Platform/Macro/Keyword.h"
#include "Core/Constant/Invalid.h"
#include "Core/Data/Vector.h"
#include "Core/Debug/Debug.h"

namespace Minty
{
    /**
     * @class StringView
     * @brief A non-owning view of a string, consisting of a pointer to the character data and a size.
     */
    class StringView
    {
#pragma region Type

    public:
        using Iterator = Char const *;
        using ConstIterator = Char const *;

#pragma endregion

#pragma region Constructors

    public:
        constexpr StringView() : mp_data{nullptr}, m_size{0} {}

        constexpr StringView(Char const *cstr) : mp_data{cstr}, m_size{0}
        {
            while (mp_data[m_size] != '\0')
            {
                ++m_size;
            }
        }

        constexpr StringView(Char const *data, Size size) : mp_data{data}, m_size{size} {}

#pragma endregion

#pragma region Iterators

    public:
        constexpr Iterator begin() const { return mp_data; }

        constexpr Iterator end() const { return mp_data + m_size; }

        constexpr ConstIterator cbegin() const { return mp_data; }

        constexpr ConstIterator cend() const { return mp_data + m_size; }

#pragma endregion

#pragma region Operators

    public:
        inline Char const& operator[](Size const index) const { return this->at(index); }
        inline Bool operator==(StringView const &other) const noexcept { return compare(other) == 0; }
        inline Bool operator!=(StringView const &other) const noexcept { return compare(other) != 0; }
        inline Bool operator<(StringView const &other) const noexcept { return compare(other) < 0; }
        inline Bool operator<=(StringView const &other) const noexcept { return compare(other) <= 0; }
        inline Bool operator>(StringView const &other) const noexcept { return compare(other) > 0; }
        inline Bool operator>=(StringView const &other) const noexcept { return compare(other) >= 0; }

#pragma endregion

#pragma region Accessors

    public:
        constexpr Size get_size() const { return m_size; }

        constexpr Char const *get_data() const { return mp_data; }

        constexpr Bool is_empty() const { return get_size() == 0; }

        constexpr Char front() const { return mp_data[0]; }

        constexpr Char back() const { return mp_data[m_size - 1]; }

#pragma endregion

#pragma region Methods

    public:
		/**
		 * @brief Gets the character at the specified index.
		 * @param index Index of the character.
         * @return The character at the specified index.
		 */
        inline Char index(Size const index) const
        {
            MINTY_ASSERT_A(index < m_size, ErrorCodeEnum::Argument_OutOfRange, index);
            return mp_data[index];
        }

        /**
         * @brief Gets the character at the specified index.
         * @param index Index of the character.
         * @return The character at the specified index.
         */
        inline Char const& at(Size const index) const
        {
            MINTY_ASSERT_A(index < m_size, ErrorCodeEnum::Argument_OutOfRange, index);
            return mp_data[index];
        }

		/**
		 * @brief Extracts a substring from the string.
		 * @param startIndex The starting index of the substring.
		 * @param count The number of characters to include in the substring.
		 * @return The extracted substring.
		 */
		constexpr StringView sub(Size const startIndex, Size const count = INVALID_SIZE) const noexcept
        {
            return peek(startIndex, count);
        }

		/**
		 * @brief Peeks at a portion of the string without creating a new String.
		 * @param startIndex The starting index of the portion.
		 * @param count The number of characters to include in the portion.
		 * @return A StringView representing the portion of the string.
		 */
		constexpr StringView peek(Size const startIndex, Size const count = INVALID_SIZE) const noexcept
		{
			return StringView(mp_data + startIndex, (count == INVALID_SIZE || startIndex + count > m_size) ? (m_size - startIndex) : count);
		}

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
		Size find_last(Char const c, Size const startIndex = INVALID_SIZE) const noexcept;
		
		/**
		 * @brief Finds the last occurrence of a substring.
		 * @param str The substring to find.
		 * @param startIndex The index to start the search from.
		 * @return The index of the last occurrence, or INVALID_INDEX if not found.
		 */
		Size find_last(StringView const str, Size const startIndex = INVALID_SIZE) const noexcept;

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
		Size find_last_of(StringView const chars, Size const startIndex = INVALID_SIZE) const noexcept;

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
		Size find_last_not_of(StringView const chars, Size const startIndex = INVALID_SIZE) const noexcept;

        /**
         * @brief Compares this StringView with another.
         * @param other The other StringView to compare with.
         * @return An integer less than, equal to, or greater than zero if this StringView is found,
         *  respectively, to be less than, to match, or be greater than the other StringView.
         */
        Int compare(StringView const &other) const noexcept;

        /**
         * @brief Checks if the string view starts with the specified prefix.
         * @param prefix The prefix to check.
         * @return True if the string view starts with the prefix, false otherwise.
         */
        Bool starts_with(StringView const prefix) const noexcept;

        /**
         * @brief Checks if the string view starts with the specified character.
         * @param c The character to check.
         * @return True if the string view starts with the character, false otherwise.
         */
        inline Bool starts_with(Char const c) const noexcept { return !is_empty() && mp_data[0] == c; }

        /**
         * @brief Checks if the string view ends with the specified suffix.
         * @param suffix The suffix to check.
         * @return True if the string view ends with the suffix, false otherwise.
         */
        Bool ends_with(StringView const suffix) const noexcept;
        
        /**
         * @brief Checks if the string view ends with the specified character.
         * @param c The character to check.
         * @return True if the string view ends with the character, false otherwise.
         */
        inline Bool ends_with(Char const c) const noexcept { return !is_empty() && mp_data[m_size - 1] == c; }

#pragma endregion

#pragma region Variables

    private:
        Char const *mp_data;
        Size m_size;

#pragma endregion
    };
}

namespace std
{
    template <>
    struct hash<Minty::StringView>
    {
        std::size_t operator()(Minty::StringView const &str) const
        {
            std::size_t hash = 0;
            for (std::size_t i = 0; i < str.get_size(); ++i)
            {
                hash = hash * 31 + static_cast<std::size_t>(str[i]);
            }
            return hash;
        }
    };
}