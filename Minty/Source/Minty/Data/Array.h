#pragma once
#include "Minty/Core/Types.h"
#include "Minty/Core/Macro.h"

namespace Minty
{
	/// <summary>
	/// Holds a collection of elements with a constant size.
	/// </summary>
	/// <typeparam name="T">The type of elements.</typeparam>
	/// <typeparam name="S">The number of elements.</typeparam>
	template<typename T, Size S>
	class Array
	{
#pragma region Iterators

	public:
		class Iterator
		{
		public:
			using iterator_category = std::forward_iterator_tag;
			using value_type = T;
			using difference_type = std::ptrdiff_t;
			using pointer = value_type*;
			using reference = value_type&;

		private:
			pointer mp_ptr;

		public:
			constexpr explicit Iterator(pointer const ptr)
				: mp_ptr(ptr)
			{}

			constexpr reference operator*() const
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

			constexpr Iterator operator+(Size const value)
			{
				return Iterator(mp_ptr + value);
			}

			constexpr Bool operator==(Iterator const& other) const { return mp_ptr == other.mp_ptr; }
			constexpr Bool operator!=(Iterator const& other) const { return mp_ptr != other.mp_ptr; }
		};

		class ConstIterator
		{
		public:
			using iterator_category = std::forward_iterator_tag;
			using value_type = T;
			using difference_type = std::ptrdiff_t;
			using pointer = value_type const*;
			using reference = value_type const&;

		private:
			pointer mp_ptr;

		public:
			constexpr explicit ConstIterator(pointer const data)
				: mp_ptr(data)
			{}

			constexpr reference operator*()
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

			constexpr ConstIterator operator+(Size const value)
			{
				return ConstIterator(mp_ptr + value);
			}

			constexpr Bool operator==(ConstIterator const& other) const { return mp_ptr == other.mp_ptr; }
			constexpr Bool operator!=(ConstIterator const& other) const { return mp_ptr != other.mp_ptr; }
		};

		/// <summary>
		/// Gets an Iterator to the beginning of the Array.
		/// </summary>
		/// <returns>An Iterator pointing to the first character.</returns>
		constexpr Iterator begin() { return Iterator(m_data); }

		/// <summary>
		/// Gets an Iterator to the end of the Array.
		/// </summary>
		/// <returns>An Iterator pointing to the null terminating character.</returns>
		constexpr Iterator end() { return Iterator(m_data + S); }

		/// <summary>
		/// Gets an Iterator to the beginning of the Array.
		/// </summary>
		/// <returns>An Iterator pointing to the first character.</returns>
		constexpr ConstIterator cbegin() const { return ConstIterator(m_data); }

		/// <summary>
		/// Gets an Iterator to the end of the Array.
		/// </summary>
		/// <returns>An Iterator pointing to the null terminating character.</returns>
		constexpr ConstIterator cend() const { return ConstIterator(m_data + S); }

#pragma endregion

#pragma region Variables

	private:
		T m_data[S];

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates an empty Array.
		/// </summary>
		constexpr Array()
			: m_data()
		{}

		/// <summary>
		/// Creates an Array and fills it with the given value.
		/// </summary>
		/// <param name="value"></param>
		constexpr Array(T const& value)
			: m_data()
		{
			for (Size i = 0; i < S; ++i)
			{
				m_data[i] = value;
			}
		}

		/// <summary>
		/// Creates an Array with the given values.
		/// </summary>
		/// <param name="list">The values to set the Array data to.</param>
		constexpr Array(std::initializer_list<T> const& list)
			: m_data()
		{
			MINTY_ASSERT(list.size() == S, "Initializer list size does not match Array size.");

			Size i = 0;
			for (T const& value : list)
			{
				m_data[i++] = value;
			}
		}

		/// <summary>
		/// Copies the given Array.
		/// </summary>
		/// <param name="other">The Array to copy.</param>
		constexpr Array(Array const& other)
			: m_data()
		{
			for (Size i = 0; i < S; ++i)
			{
				m_data[i] = other.m_data[i];
			}
		}

		/// <summary>
		/// Moves the given Array.
		/// </summary>
		/// <param name="other">The Array to move.</param>
		constexpr Array(Array&& other)
			: m_data()
		{
			for (Size i = 0; i < S; ++i)
			{
				m_data[i] = std::move(other.m_data[i]);
			}
		}

		constexpr ~Array()
		{}

#pragma endregion

#pragma region Operators

	public:
		constexpr Array& operator=(Array const& other)
		{
			if (this != &other)
			{
				for (Size i = 0; i < S; ++i)
				{
					m_data[i] = other.m_data[i];
				}
			}
			return *this;
		}

		constexpr Array& operator=(Array&& other)
		{
			if (this != &other)
			{
				for (Size i = 0; i < S; ++i)
				{
					m_data[i] = std::move(other.m_data[i]);
				}
			}
			return *this;
		}

		constexpr T& operator[](Size const index)
		{
			return at(index);
		}

		constexpr T const& operator[](Size const index) const
		{
			return at(index);
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the size of this Array.
		/// </summary>
		/// <returns>The number of elements.</returns>
		constexpr Size get_size() const { return S; }

		/// <summary>
		/// Gets the internal pointer to the data.
		/// </summary>
		/// <returns>A pointer to the data.</returns>
		constexpr T* get_data() { return m_data; }

		/// <summary>
		/// Gets the internal pointer to the data.
		/// </summary>
		/// <returns>A pointer to the data.</returns>
		constexpr T const* get_data() const { return m_data; }

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Gets the element at the given index.
		/// </summary>
		/// <param name="index">The index of the element.</param>
		/// <returns>The element at the given index.</returns>
		constexpr T& at(Size const index)
		{
			MINTY_ASSERT(index < S, "Index is out of bounds.");
			return m_data[index];
		}

		/// <summary>
		/// Gets the element at the given index.
		/// </summary>
		/// <param name="index">The index of the element.</param>
		/// <returns>The element at the given index.</returns>
		constexpr T const& at(Size const index) const
		{
			MINTY_ASSERT(index < S, "Index is out of bounds.");
			return m_data[index];
		}

		/// <summary>
		/// Creates a Array with the elements from the given start index to the given length.
		/// </summary>
		/// <typeparam name="N">The number of elements to copy.</typeparam>
		/// <param name="start">The starting index to create the Array at.</param>
		/// <returns>An Array with the copied elements in the given range.</returns>
		template<Size N>
		constexpr Array<T, N> sub(Size const start) const
		{
			MINTY_ASSERT(start < S, "Start index is out of bounds.");
			MINTY_ASSERT(start + N <= S, "Start + length index is out of bounds.");

			// create new array
			Array<T, N> result;
			for (Size i = 0; i < N; ++i)
			{
				result[i] = m_data[start + i];
			}

			return result;
		}

		/// <summary>
		/// Finds the first occurrence of the given value.
		/// </summary>
		/// <param name="value">The value to find.</param>
		/// <returns>An Iterator to the value, if found.</returns>
		constexpr Iterator find(T const& value)
		{
			for (Size i = 0; i < S; ++i)
			{
				if (m_data[i] == value)
				{
					return Iterator(m_data + i);
				}
			}

			return end();
		}

		/// <summary>
		/// Finds the first occurrence of the given value.
		/// </summary>
		/// <param name="value">The value to find.</param>
		/// <returns>An Iterator to the value, if found.</returns>
		constexpr ConstIterator find(T const& value) const
		{
			for (Size i = 0; i < S; ++i)
			{
				if (m_data[i] == value)
				{
					return ConstIterator(m_data + i);
				}
			}

			return cend();
		}

		/// <summary>
		/// Checks if the given Value is within this Array.
		/// </summary>
		/// <param name="value">The value to check.</param>
		/// <returns>True, if the value exists.</returns>
		constexpr Bool contains(T const& value) const { return find(value) != end(); }

#pragma endregion
	};
}