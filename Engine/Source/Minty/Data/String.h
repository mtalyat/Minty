#ifndef MINTY_STRING_H
#define MINTY_STRING_H

/**
 * @file String.h
 * @brief Header file for string utilities.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Constant.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/StringView.h"

namespace Minty
{
	/**
	 * @class String
	 * @brief Class representing an immutable string.
	 */
    class String
    {
#pragma region Constructors

    public:
		/**
		 * @brief Creates an empty String.
		 */
        String();

		/**
		 * @brief Creates a String from a StringView.
		 * @param view The StringView to create the String from.
		 */
        String(StringView const view);

		/**
		 * @brief Creates a String from a C-style string.
		 * @param cstr The C-style string.
		 */
        String(Char const* const cstr);

		/**
		 * @brief Creates a String from a character with a specified length.
		 * @param c The character to repeat.
		 * @param count The number of times to repeat the character.
		 */
        explicit String(Char const c, Size const count = 1);

		/**
		 * @brief Copy constructor.
		 * @param other The String to copy from.
		 */
        String(String const& other);

		/**
		 * @brief Move constructor.
		 * @param other The String to move from.
		 */
        String(String&& other) noexcept;

        ~String();

#pragma endregion

#pragma region Iterators

	public:
		class Iterator
		{
			friend class String;

		public:
			using iterator_category = std::forward_iterator_tag;
			using value_type = Char;
			using difference_type = std::ptrdiff_t;
			using pointer = value_type*;
			using reference = value_type&;

		private:
			pointer mp_ptr;

		private:
			explicit Iterator(pointer const ptr)
				: mp_ptr(ptr)
			{
			}

		public:
			reference operator*() const
			{
				return *mp_ptr;
			}

			Iterator& operator++()
			{
				++mp_ptr;
				return *this;
			}

			Iterator operator++(int)
			{
				Iterator temp = *this;
				++mp_ptr;
				return temp;
			}

			Iterator operator+(Size const value)
			{
				return Iterator(mp_ptr + value);
			}

			Bool operator==(Iterator const& other) const { return mp_ptr == other.mp_ptr; }
			Bool operator!=(Iterator const& other) const { return mp_ptr != other.mp_ptr; }
		};

		class ConstIterator
		{
			friend class String;

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

		Iterator begin() { return Iterator(mp_data); }
		Iterator end() { return Iterator(mp_data + m_size); }
		ConstIterator begin() const { return ConstIterator(mp_data); }
		ConstIterator end() const { return ConstIterator(mp_data + m_size); }

#pragma endregion

#pragma region Operators

	public:
        operator StringView() const noexcept { return StringView(mp_data, m_size); }
        String& operator=(String const& other);
        String& operator=(String&& other) noexcept;
        Char& operator[](Size const index) { return at(index); }
		Char operator[](Size const index) const { return this->index(index); }
		Bool operator==(StringView const other) const noexcept { return compare(other) == 0; }
		Bool operator!=(StringView const other) const noexcept { return !(*this == other); }
		Bool operator<(StringView const other) const noexcept { return compare(other) < 0; }
		Bool operator<=(StringView const other) const noexcept { return compare(other) <= 0; }
		Bool operator>(StringView const other) const noexcept { return compare(other) > 0; }
		Bool operator>=(StringView const other) const noexcept { return compare(other) >= 0; }
		String operator+(StringView const other) const;
        
#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the underlying string data.
		 * @return Pointer to the string data.
		 */
        inline Char const* get_data() const noexcept { return mp_data; }

		/**
		 * @brief Gets the underlying string data.
		 * @return Pointer to the string data.
		 */
		inline Char* get_data() noexcept { return mp_data; }

		/**
		 * @brief Gets the size of the string.
		 * @return Size of the string.
		 */
        inline Size get_size() const noexcept { return m_size; }

		/**
		 * @brief Gets the length of the string.
		 * @return Length of the string.
		 */
        inline Size get_length() const noexcept { return m_size; }

        /**
		 * @brief Gets the capacity of the string.
		 * @return Capacity of the string.
		 */
        inline Size get_capacity() const noexcept { return m_capacity; }

		/**
		 * @brief Gets a StringView of the string.
		 * @return StringView of the string.
		 */
        inline StringView get_view() const noexcept { return StringView(mp_data, m_size); }

		/**
		 * @brief Checks if the string is empty.
		 * @return True if the string is empty, false otherwise.
		 */
        inline Bool is_empty() const noexcept { return m_size == 0; }

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
		Char const& at(Size const index) const;

		/**
		 * @brief Gets a reference to the character at the specified index.
		 * @param index Index of the character.
		 */
        inline Char& at(Size const index) { return const_cast<Char&>(static_cast<String const&>(*this).at(index)); }

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
		 * @brief Checks if the string contains a given substring.
		 * @param str The substring to check.
		 * @return True if the string contains the substring, false otherwise.
		 */
		inline Bool contains(StringView const str) const noexcept { return find_first(str) != INVALID_INDEX; }

#pragma endregion

#pragma region Variables

    private:
        Char* mp_data;
        Size m_size;
        Size m_capacity;
        
#pragma endregion
    };
}

namespace std
{
	template<>
	struct hash<Minty::String>
	{
		std::size_t operator()(Minty::String const& str) const
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

#endif // MINTY_STRING_H