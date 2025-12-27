#ifndef MINTY_DATA_STRINGVIEW_H
#define MINTY_DATA_STRINGVIEW_H

/**
 * @file StringView.h
 * @brief Header file for string view utilities.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"

namespace Minty
{
    /**
     * @brief Class representing a view into a string. This is non-owning and lightweight.
     */
    class StringView
    {
#pragma region Iterators

	public:
		class ConstIterator
		{
			friend class StringView;

		public:
			using iterator_category = std::forward_iterator_tag;
			using value_type = Char;
			using difference_type = std::ptrdiff_t;
			using pointer = value_type const*;
			using reference = value_type const&;

		private:
			pointer mp_ptr;

		private:
			explicit ConstIterator(pointer const data)
				: mp_ptr(data)
			{
			}

		public:
			reference operator*()
			{
				return *mp_ptr;
			}

			ConstIterator& operator++()
			{
				++mp_ptr;
				return *this;
			}

			ConstIterator operator++(int)
			{
				ConstIterator temp = *this;
				++mp_ptr;
				return temp;
			}

			ConstIterator operator+(Size const value)
			{
				return ConstIterator(mp_ptr + value);
			}

			Bool operator==(ConstIterator const& other) const { return mp_ptr == other.mp_ptr; }
			Bool operator!=(ConstIterator const& other) const { return mp_ptr != other.mp_ptr; }
		};

		ConstIterator begin() const { return ConstIterator(mp_data); }
		ConstIterator end() const { return ConstIterator(mp_data + m_size); }

#pragma endregion

#pragma region Constructors

    public:
        /**
         * @brief Constructs an empty StringView.
         */
        constexpr explicit StringView()
            : mp_data(nullptr), m_size(0)
        {
        }

        /**
         * @brief Constructs a StringView from a C-style string.
         * @param data Pointer to the C-style string.
         */
        StringView(Char const *const data)
            : mp_data(data), m_size(data ? std::char_traits<Char>::length(data) : 0)
        {
        }

        /**
         * @brief Constructs a StringView from a pointer and size.
         * @param data Pointer to the string data.
         * @param size Size of the string data.
         */
        StringView(Char const *const data, Size const size)
            : mp_data(data), m_size(size)
        {
        }

#pragma endregion

#pragma region Operators

    public:
        inline Char operator[](Size const index) const { return this->index(index); }
        constexpr Bool operator==(StringView const &other) const noexcept { return compare(other) == 0; }
        constexpr Bool operator!=(StringView const &other) const noexcept { return compare(other) != 0; }
        constexpr Bool operator<(StringView const &other) const noexcept { return compare(other) < 0; }
        constexpr Bool operator<=(StringView const &other) const noexcept { return compare(other) <= 0; }
        constexpr Bool operator>(StringView const &other) const noexcept { return compare(other) > 0; }
        constexpr Bool operator>=(StringView const &other) const noexcept { return compare(other) >= 0; }

#pragma endregion

#pragma region Accessors

    public:
        /**
         * @brief Gets the underlying string data.
         * @return Pointer to the string data.
         */
        constexpr Char const *get_data() const noexcept { return mp_data; }

        /**
         * @brief Gets the size of the string view.
         * @return Size of the string view.
         */
        constexpr Size get_size() const noexcept { return m_size; }

        /**
         * @brief Gets the length of the string view.
         * @return Length of the string view.
         */
        constexpr Size get_length() const noexcept { return m_size; }

        /**
         * @brief Checks if the string view is empty.
         * @return True if the string view is empty, false otherwise.
         */
        constexpr Bool is_empty() const noexcept { return m_size == 0; }

#pragma endregion

#pragma region Methods

    public:
		/**
		 * @brief Gets the character at the specified index.
		 * @param index Index of the character.
		 */
        Char index(Size const index) const;

		/**
		 * @brief Gets a const reference to the character at the specified index.
		 * @param index Index of the character.
		 */
		inline Char at(Size const index) const { return this->index(index); }

        /**
         * @brief Gets the first character in the string view.
         * @return The first character.
         */
        inline Char front() const { return this->index(0); }

        /**
         * @brief Gets the last character in the string view.
         * @return The last character.
         */
        inline Char back() const { return this->index(m_size - 1); }

        /**
         * @brief Compares this StringView with another.
         * @param other The other StringView to compare with.
         * @return An integer less than, equal to, or greater than zero if this StringView is found,
         *  respectively, to be less than, to match, or be greater than the other StringView.
         */
        constexpr Int compare(StringView const &other) const noexcept
        {
            if (m_size < other.m_size)
            {
                return -1;
            }
            else if (m_size > other.m_size)
            {
                return 1;
            }

            for (Size i = 0; i < m_size; ++i)
            {
                if (mp_data[i] < other.mp_data[i])
                {
                    return -1;
                }
                else if (mp_data[i] > other.mp_data[i])
                {
                    return 1;
                }
            }
            return 0;
        }

        /**
         * @brief Gets a substring of the string view.
         * @param startIndex The starting index of the substring.
         * @param count The number of characters in the substring. Defaults to SIZE_MAX to get until the end.
         * @return A new StringView representing the substring.
         */
        StringView sub(Size const startIndex, Size const count = SIZE_MAX) const noexcept;

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

#endif // MINTY_DATA_STRINGVIEW_H