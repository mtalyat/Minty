#pragma once
#include "Minty/Core/Base.h"
#include "Minty/Core/Constant.h"
#include "Minty/Core/Macro.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Tuple.h"
#include "Minty/Data/Vector.h"
#include <utility>

namespace Minty
{
	/// <summary>
	/// A collection of text.
	/// </summary>
	class String
	{
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

		/// <summary>
		/// Gets an Iterator to the beginning of the String.
		/// </summary>
		/// <returns>An Iterator pointing to the first character.</returns>
		Iterator begin() { return Iterator(mp_data); }

		/// <summary>
		/// Gets an Iterator to the end of the String.
		/// </summary>
		/// <returns>An Iterator pointing to the null terminating character.</returns>
		Iterator end() { return Iterator(mp_data + m_size); }

		/// <summary>
		/// Gets an Iterator to the beginning of the String.
		/// </summary>
		/// <returns>An Iterator pointing to the first character.</returns>
		ConstIterator begin() const { return ConstIterator(mp_data); }

		/// <summary>
		/// Gets an Iterator to the end of the String.
		/// </summary>
		/// <returns>An Iterator pointing to the null terminating character.</returns>
		ConstIterator end() const { return ConstIterator(mp_data + m_size); }

#pragma endregion

#pragma region Variables

	private:
		Allocator m_allocator;
		Size m_capacity;
		Size m_size;
		Char* mp_data;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates an empty String.
		/// </summary>
		/// <param name="allocator">The Allocator to use.</param>
		constexpr String(Allocator const allocator = Allocator::Default)
			: m_allocator(allocator)
			, m_capacity(0)
			, m_size(0)
			, mp_data(nullptr)
		{
		}

		/// <summary>
		/// Creates a String and reserves the given capacity.
		/// </summary>
		/// <param name="capacity">The amount of characters to allocate.</param>
		/// <param name="allocator">The Allocator to use.</param>
		String(Size const capacity, Allocator const allocator = Allocator::Default);

		/// <summary>
		/// Creates a String and copies the given data.
		/// </summary>
		/// <param name="data">The text to copy.</param>
		/// <param name="allocator">The Allocator to use.</param>
		String(Char const* const data, Allocator const allocator = Allocator::Default);

		/// <summary>
		/// Creates a string with the given character repeated the given amount of times.
		/// </summary>
		/// <param name="character">The character to repeat.</param>
		/// <param name="count">The number of characters to repeat.</param>
		/// <param name="allocator">The Allocator to use.</param>
		String(Char const character, Size const count, Allocator const allocator = Allocator::Default);

		/// <summary>
		/// Copies the given String.
		/// </summary>
		/// <param name="other">The String to copy.</param>
		String(String const& other)
			: m_allocator(other.m_allocator)
			, m_capacity(other.m_capacity)
			, m_size(other.m_size)
			, mp_data(static_cast<Char*>(allocate((m_capacity + 1) * sizeof(Char), m_allocator)))
		{
			memcpy(mp_data, other.mp_data, m_size * sizeof(Char));
			mp_data[m_size] = '\0';
		}

		/// <summary>
		/// Moves the given String.
		/// </summary>
		/// <param name="other">The String to move.</param>
		String(String&& other) noexcept
			: m_allocator(other.m_allocator)
			, m_capacity(other.m_capacity)
			, m_size(other.m_size)
			, mp_data(other.mp_data)
		{
			other.m_allocator = Allocator::Default;
			other.m_capacity = 0;
			other.m_size = 0;
			other.mp_data = nullptr;
		}

		~String()
		{
			if (mp_data)
			{
				deallocate(mp_data, (m_capacity + 1) * sizeof(Char), m_allocator);
			}
		}

#pragma endregion

#pragma region Operators

	public:
		String& operator=(String const& other)
		{
			if (this != &other)
			{
				if (m_capacity < other.m_size || m_allocator != other.m_allocator || !mp_data)
				{
					deallocate(mp_data, (m_capacity + 1) * sizeof(Char), m_allocator);
					m_allocator = other.m_allocator;
					m_capacity = other.m_capacity;
					mp_data = static_cast<Char*>(allocate((m_capacity + 1) * sizeof(Char), m_allocator));
				}
				m_size = other.m_size;
				memcpy(mp_data, other.mp_data, m_size * sizeof(Char));
				mp_data[m_size] = '\0';
			}
			return *this;
		}

		String& operator=(String&& other) noexcept
		{
			if (this != &other)
			{
				if (mp_data)
				{
					deallocate(mp_data, (m_capacity + 1) * sizeof(Char), m_allocator);
				}
				m_allocator = other.m_allocator;
				m_capacity = other.m_capacity;
				m_size = other.m_size;
				mp_data = other.mp_data;
				other.m_capacity = 0;
				other.m_size = 0;
				other.mp_data = nullptr;
			}
			return *this;
		}

		Char operator[](Size const index) const
		{
			return at(index);
		}

		Bool operator==(String const& other) const
		{
			return m_size == other.m_size && memcmp(mp_data, other.mp_data, m_size * sizeof(Char)) == 0;
		}

		Bool operator!=(String const& other) const
		{
			return !(*this == other);
		}

		Bool operator<(String const& other) const
		{
			Size const length = m_size < other.m_size ? m_size : other.m_size;
			int result = std::memcmp(mp_data, other.mp_data, length);

			if (result < 0) {
				return true;
			}
			else if (result > 0) {
				return false;
			}
			return m_size < other.m_size;
		}

		Bool operator>(String const& other) const
		{
			return other < *this;
		}

		Bool operator<=(String const& other) const
		{
			return !(other < *this);
		}

		Bool operator>=(String const& other) const
		{
			return !(*this < other);
		}

		String operator+(String const& other) const;

		String& operator+=(String const& other)
		{
			return append(other);
		}

		friend std::ostream& operator<<(std::ostream& stream, String const& str);

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the capacity of the String.
		/// </summary>
		/// <returns>The capacity.</returns>
		constexpr Size get_capacity() const { return m_capacity; }

		/// <summary>
		/// Gets the size of the String.
		/// </summary>
		/// <returns>The size.</returns>
		constexpr Size get_size() const { return m_size; }

		/// <summary>
		/// Gets the data of the String.
		/// </summary>
		/// <returns>The pointer to the internal text data.</returns>
		constexpr Char* get_data() const { return mp_data; }

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Allocates characters using the given capacity.
		/// </summary>
		/// <param name="capacity">The new capacity.</param>
		void reserve(Size const capacity);

		/// <summary>
		/// Resizes the String to the given size. Reallocates if necessary.
		/// </summary>
		/// <param name="size">The new size.</param>
		/// <param name="value">The character to fill the new space with.</param>
		void resize(Size const size, Char const value = ' ');

		/// <summary>
		/// Adds the given String to the end of this String.
		/// </summary>
		/// <param name="other">The other String to add.</param>
		/// <returns>This String.</returns>
		String& append(String const& other);

		/// <summary>
		/// Adds the given Char to the end of this String.
		/// </summary>
		/// <param name="character">The character to add.</param>
		/// <returns>This String.</returns>
		String& append(Char const character);

		/// <summary>
		/// Checks if this String is empty.
		/// </summary>
		/// <returns>True if the String is empty.</returns>
		constexpr Bool is_empty() const { return m_size == 0; }

		/// <summary>
		/// Gets the character at the given index.
		/// </summary>
		/// <param name="index">The index.</param>
		/// <returns>The character.</returns>
		constexpr Char at(Size const index) const
		{
			MINTY_ASSERT(index < m_size, "The given index is out of range.");
			return mp_data[index];
		}

		/// <summary>
		/// Gets the first character in the String.
		/// </summary>
		/// <returns>The first character.</returns>
		constexpr Char front() const { return at(0); }

		/// <summary>
		/// Gets the last character in the String.
		/// </summary>
		/// <returns>The last character.</returns>
		constexpr Char back() const { return at(m_size - 1); }

		/// <summary>
		/// Gets the sub string starting from the given index.
		/// </summary>
		/// <param name="start">The index of the first character.</param>
		/// <param name="length">The number of characters to use.</param>
		/// <returns>A new String with the text within the given range.</returns>
		String sub(Size const start, Size const length) const;

		String trim_start(String const& characters = TEXT_WHITESPACE);

		String trim_end(String const& characters = TEXT_WHITESPACE);

		String trim(String const& whitespace = TEXT_WHITESPACE);

		/// <summary>
		/// Finds the first occurrence of the given sub string.
		/// </summary>
		/// <param name="sub">The text to find.</param>
		/// <param name="index">The index of the first character to start searching at.</param>
		/// <returns>The index to the found text, or INVALID_INDEX if not found.</returns>
		Size find_first(String const& sub, Size const index = 0) const;

		/// <summary>
		/// Finds the first occurrence of the given character.
		/// </summary>
		/// <param name="character">The character to find.</param>
		/// <param name="index">The index of the first character to start searching at.</param>
		/// <returns>The index to the found text, or INVALID_INDEX if not found.</returns>
		Size find_first(Char const character, Size const index = 0) const;

		/// <summary>
		/// Finds the first occurrence of a character within the given sub String.
		/// </summary>
		/// <param name="characters">The characters to use.</param>
		/// <param name="index">The starting index.</param>
		/// <returns>The index of the first character found.</returns>
		Size find_first_of(String const& characters, Size const index = 0) const;

		/// <summary>
		/// Finds the first occurrence of a character not within the given sub String.
		/// </summary>
		/// <param name="characters">The characters to use.</param>
		/// <param name="index">The starting index.</param>
		/// <returns>The index of the first character found.</returns>
		Size find_first_not_of(String const& characters, Size const index = 0) const;

		Size find_last(String const& sub, Size const index = INVALID_INDEX) const;

		Size find_last(Char const character, Size const index = INVALID_INDEX) const;

		Size find_last_of(String const& characters, Size const index = INVALID_INDEX) const;

		Size find_last_not_of(String const& characters, Size const index = INVALID_INDEX) const;

		Tuple<Size, Size> find_group(Char const open, Char const close, Size const index = 0) const;

		Vector<Tuple<Size, Size>> find_groups(Char const open, Char const close, Size const index = 0) const;

		/// <summary>
		/// Checks if this String contains the given sub string.
		/// </summary>
		/// <param name="sub">The text to check.</param>
		/// <returns>True if found.</returns>
		Bool contains(String const& sub) const
		{
			return find_first(sub) != INVALID_INDEX;
		}
		
		/// <summary>
		/// Checks if this String contains the given character.
		/// </summary>
		/// <param name="character">The character to check.</param>
		/// <returns>True if found.</returns>
		Bool contains(Char const character) const
		{
			return find_first(character) != INVALID_INDEX;
		}

		/// <summary>
		/// Checks if this String starts with the given sub string.
		/// </summary>
		/// <param name="sub">The text to check.</param>
		/// <returns>True, if this String starts with sub.</returns>
		Bool starts_with(String const& sub) const;

		/// <summary>
		/// Checks if this String ends with the given sub string.
		/// </summary>
		/// <param name="sub">The text to check.</param>
		/// <returns>True, if this String ends with sub.</returns>
		Bool ends_with(String const& sub) const;

#pragma endregion

#pragma region Statics

	public:
		/// <summary>
		/// Converts the given text to upper case.
		/// </summary>
		/// <param name="str">The text to convert.</param>
		/// <returns>A copy of the given String, uppercased.</returns>
		static String to_upper(String const& str);

		/// <summary>
		/// Converts the given text to lower case.
		/// </summary>
		/// <param name="str">The text to convert.</param>
		/// <returns>A copy of the given String, lowercased.</returns>
		static String to_lower(String const& str);

		/// <summary>
		/// Replaces all occurrences of the given text with the replacement text.
		/// </summary>
		/// <param name="str">The text to search within.</param>
		/// <param name="find">The text to find.</param>
		/// <param name="replace">The text to replace it with.</param>
		/// <returns>A new string with the text replaced.</returns>
		static String replace(String const& str, String const& find, String const& replace);

		/// <summary>
		/// Splits the given text into a Vector of Strings using the given delimiter.
		/// </summary>
		/// <param name="str">The String to split.</param>
		/// <param name="delimiter">The delimiter to use.</param>
		/// <returns>A list of Strings, split by the delimiters.</returns>
		static Vector<String> split(String const& str, Char const delimiter);

		/// <summary>
		/// Splits the given text into a Vector of Strings using the given delimiter.
		/// </summary>
		/// <param name="str">The String to split.</param>
		/// <param name="delimiter">The delimiter to use.</param>
		/// <returns>A list of Strings, split by the delimiters.</returns>
		static Vector<String> split(String const& str, String const& delimiter);

		/// <summary>
		/// Splits the given text into a Vector of Strings using whitespace as the delimiter.
		/// </summary>
		/// <param name="str">The String to split.</param>
		/// <returns>A list of Strings, split by whitespace.</returns>
		static Vector<String> split(String const& str);

		/// <summary>
		/// Splits the given text into a Vector of Strings using newlines as the delimiter.
		/// </summary>
		/// <param name="str">The String to split.</param>
		/// <returns>A list of Strings, split by newlines.</returns>
		static Vector<String> split_lines(String const& str);

		/// <summary>
		/// Creates a String from the given bytes.
		/// </summary>
		/// <param name="data">A pointer to the array of bytes.</param>
		/// <param name="size">The number of bytes.</param>
		/// <param name="allocator">The allocator.</param>
		/// <returns>A new null terminated String, with a copy of the given data.</returns>
		static String from_bytes(void const* const data, Size const size, Allocator const allocator = Allocator::Default);

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
			return std::hash<std::string_view>()(std::string_view(str.get_data(), str.get_size()));
		}
	};
}