#pragma once
#include "Minty/Core/Constant.h"
#include "Minty/Core/Macro.h"
#include "Minty/Core/Types.h"
#include <utility>

namespace Minty
{
	/// <summary>
	/// A collection of text.
	/// </summary>
	class String
	{
#pragma region Variables

	private:
		Size m_capacity;
		Size m_size;
		Char* mp_data;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates an empty String.
		/// </summary>
		constexpr String()
			: m_capacity(0)
			, m_size(0)
			, mp_data(nullptr)
		{}

		/// <summary>
		/// Creates a String and reserves the given capacity.
		/// </summary>
		/// <param name="capacity">The amount of characters to allocate.</param>
		String(Size const capacity);

		/// <summary>
		/// Creates a String and copies the given data.
		/// </summary>
		/// <param name="data">The text to copy.</param>
		String(Char const* data);

		/// <summary>
		/// Copies the given String.
		/// </summary>
		/// <param name="other">The String to copy.</param>
		String(String const& other)
			: m_capacity(other.m_capacity)
			, m_size(other.m_size)
			, mp_data(new Char[m_capacity + 1])
		{
			memcpy(mp_data, other.mp_data, m_size * sizeof(Char));
			mp_data[m_size] = '\0';
		}

		/// <summary>
		/// Moves the given String.
		/// </summary>
		/// <param name="other">The String to move.</param>
		String(String&& other) noexcept
			: m_capacity(other.m_capacity)
			, m_size(other.m_size)
			, mp_data(other.mp_data)
		{
			other.m_capacity = 0;
			other.m_size = 0;
			other.mp_data = nullptr;
		}

		~String();

#pragma endregion

#pragma region Operators

	public:
		String& operator=(String const& other)
		{
			if (this != &other)
			{
				if (m_capacity < other.m_size)
				{
					delete[] mp_data;
					mp_data = new Char[other.m_capacity + 1];
					m_capacity = other.m_capacity;
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
					delete[] mp_data;
				}
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
		void resize(Size const size);

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
		/// Gets the sub string starting from the given index.
		/// </summary>
		/// <param name="start">The index of the first character.</param>
		/// <param name="length">The number of characters to use.</param>
		/// <returns>A new String with the text within the given range.</returns>
		String sub(Size const start, Size const length) const;

		/// <summary>
		/// Finds the first occurrence of the given sub string.
		/// </summary>
		/// <param name="sub">The text to find.</param>
		/// <returns>The index to the found text, or INVALID_INDEX if not found.</returns>
		Size find(String const& sub) const;

		/// <summary>
		/// Checks if this String contains the given sub string.
		/// </summary>
		/// <param name="sub">The text to check.</param>
		/// <returns>True if found.</returns>
		Bool contains(String const& sub) const
		{
			return find(sub) != INVALID_INDEX;
		}

#pragma endregion
	};
}