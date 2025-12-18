#ifndef MINTY_DATA_ARRAY_H
#define MINTY_DATA_ARRAY_H

/**
 * @file Array.h
 * @brief Header file for the Array class.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Core/Macro.h"
#include "Minty/Debug/Debug.h"
#include <iterator>

namespace Minty
{
	/**
	 * @class Array
	 * @brief A fixed-size array that holds a specified number of elements.
	 * @tparam T The type of elements stored in the Array.
	 * @tparam S The size of the Array.
	 */
	template <typename T, Size S>
	class Array
	{
#pragma region Iterators

	public:
		class Iterator
		{
			friend class Array;

		public:
			using iterator_category = std::bidirectional_iterator_tag;
			using value_type = T;
			using difference_type = std::ptrdiff_t;
			using pointer = value_type *;
			using reference = value_type &;

		private:
			pointer mp_ptr;

		private:
			constexpr explicit Iterator(pointer const ptr)
				: mp_ptr(ptr)
			{
			}

		public:
			constexpr reference operator*() const
			{
				return *mp_ptr;
			}

			Iterator &operator++()
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

			Iterator &operator--()
			{
				--mp_ptr;
				return *this;
			}

			Iterator operator--(int)
			{
				Iterator temp = *this;
				--mp_ptr;
				return temp;
			}

			constexpr Iterator operator+(Size const value)
			{
				return Iterator(mp_ptr + value);
			}

			constexpr Iterator operator-(Size const value)
			{
				return Iterator(mp_ptr - value);
			}

			constexpr Bool operator==(Iterator const &other) const { return mp_ptr == other.mp_ptr; }
			constexpr Bool operator!=(Iterator const &other) const { return mp_ptr != other.mp_ptr; }
		};

		class ConstIterator
		{
			friend class Array;

		public:
			using iterator_category = std::bidirectional_iterator_tag;
			using value_type = T;
			using difference_type = std::ptrdiff_t;
			using pointer = value_type const *;
			using reference = value_type const &;

		private:
			pointer mp_ptr;

		private:
			constexpr explicit ConstIterator(pointer const data)
				: mp_ptr(data)
			{
			}

		public:
			constexpr reference operator*()
			{
				return *mp_ptr;
			}

			ConstIterator &operator++()
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

			ConstIterator &operator--()
			{
				--mp_ptr;
				return *this;
			}

			ConstIterator operator--(int)
			{
				ConstIterator temp = *this;
				--mp_ptr;
				return temp;
			}

			constexpr ConstIterator operator+(Size const value)
			{
				return ConstIterator(mp_ptr + value);
			}

			constexpr ConstIterator operator-(Size const value)
			{
				return ConstIterator(mp_ptr - value);
			}

			constexpr Bool operator==(ConstIterator const &other) const { return mp_ptr == other.mp_ptr; }
			constexpr Bool operator!=(ConstIterator const &other) const { return mp_ptr != other.mp_ptr; }
		};

		class ReverseIterator
		{
			friend class Array;

		public:
			using iterator_category = std::bidirectional_iterator_tag;
			using value_type = T;
			using difference_type = std::ptrdiff_t;
			using pointer = value_type *;
			using reference = value_type &;

		private:
			pointer mp_ptr;

		private:
			constexpr explicit ReverseIterator(pointer const ptr)
				: mp_ptr(ptr)
			{
			}

		public:
			constexpr reference operator*() const
			{
				return *mp_ptr;
			}

			ReverseIterator &operator++()
			{
				--mp_ptr;
				return *this;
			}

			ReverseIterator operator++(int)
			{
				ReverseIterator temp = *this;
				--mp_ptr;
				return temp;
			}

			ReverseIterator &operator--()
			{
				++mp_ptr;
				return *this;
			}

			ReverseIterator operator--(int)
			{
				ReverseIterator temp = *this;
				++mp_ptr;
				return temp;
			}

			constexpr ReverseIterator operator+(Size const value)
			{
				return ReverseIterator(mp_ptr - value);
			}

			constexpr ReverseIterator operator-(Size const value)
			{
				return ReverseIterator(mp_ptr + value);
			}

			constexpr Bool operator==(ReverseIterator const &other) const { return mp_ptr == other.mp_ptr; }
			constexpr Bool operator!=(ReverseIterator const &other) const { return mp_ptr != other.mp_ptr; }
		};

		class ConstReverseIterator
		{
			friend class Array;

		public:
			using iterator_category = std::bidirectional_iterator_tag;
			using value_type = T;
			using difference_type = std::ptrdiff_t;
			using pointer = value_type const *;
			using reference = value_type const &;

		private:
			pointer mp_ptr;

		private:
			constexpr explicit ConstReverseIterator(pointer const data)
				: mp_ptr(data)
			{
			}

		public:
			constexpr reference operator*()
			{
				return *mp_ptr;
			}

			ConstReverseIterator &operator++()
			{
				--mp_ptr;
				return *this;
			}

			ConstReverseIterator operator++(int)
			{
				ConstReverseIterator temp = *this;
				--mp_ptr;
				return temp;
			}

			ConstReverseIterator &operator--()
			{
				++mp_ptr;
				return *this;
			}

			ConstReverseIterator operator--(int)
			{
				ConstReverseIterator temp = *this;
				++mp_ptr;
				return temp;
			}

			constexpr ConstReverseIterator operator+(Size const value)
			{
				return ConstReverseIterator(mp_ptr - value);
			}

			constexpr ConstReverseIterator operator-(Size const value)
			{
				return ConstReverseIterator(mp_ptr + value);
			}

			constexpr Bool operator==(ConstReverseIterator const &other) const { return mp_ptr == other.mp_ptr; }
			constexpr Bool operator!=(ConstReverseIterator const &other) const { return mp_ptr != other.mp_ptr; }
		};

		constexpr Iterator begin() { return Iterator(m_data); }
		constexpr Iterator end() { return Iterator(m_data + S); }
		constexpr ConstIterator begin() const { return ConstIterator(m_data); }
		constexpr ConstIterator end() const { return ConstIterator(m_data + S); }
		constexpr ReverseIterator rbegin() { return ReverseIterator(m_data + S - 1); }
		constexpr ReverseIterator rend() { return ReverseIterator(m_data - 1); }
		constexpr ConstReverseIterator rbegin() const { return ConstReverseIterator(m_data + S - 1); }
		constexpr ConstReverseIterator rend() const { return ConstReverseIterator(m_data - 1); }

#pragma endregion

#pragma region Constructors

	public:
		/**
		 * @brief Creates an empty Array.
		 */
		constexpr Array()
			: m_data()
		{
		}

		/**
		 * @brief Creates an Array with all elements set to the given value.
		 * @param value The value to set all elements to.
		 */
		template<typename... Args>
		constexpr Array(Args&&... args)
			: m_data()
		{
			for (Size i = 0; i < S; ++i)
			{
				m_data[i] = T(std::forward<Args>(args)...);
			}
		}

		/**
		 * @brief Creates an Array with the elements from the given initializer list.
		 * @param list The initializer list containing the elements to add to the Array.
		 */
		constexpr Array(std::initializer_list<T> const &list)
			: m_data()
		{
			MINTY_ASSERT(list.size() == S, ErrorCode::Argument_InvalidSize);

			Size i = 0;
			for (T const &value : list)
			{
				m_data[i++] = value;
			}
		}

		/**
		 * @brief Copies the given Array.
		 * @param other The Array to copy.
		 */
		constexpr Array(Array const &other)
			: m_data()
		{
			for (Size i = 0; i < S; ++i)
			{
				m_data[i] = other.m_data[i];
			}
		}

		/**
		 * @brief Moves the given Array.
		 * @param other The Array to move.
		 */
		constexpr Array(Array &&other) noexcept
			: m_data()
		{
			for (Size i = 0; i < S; ++i)
			{
				m_data[i] = std::move(other.m_data[i]);
			}
		}

		constexpr ~Array() = default;

#pragma endregion

#pragma region Operators

	public:
		constexpr Array &operator=(Array const &other)
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

		constexpr Array &operator=(Array &&other) noexcept
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

		constexpr T &operator[](Size const index) { return at(index); }

		constexpr T const &operator[](Size const index) const { return at(index); }

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the size of the Array.
		 * @return The number of elements in the Array.
		 */
		constexpr Size get_size() const { return S; }

		/**
		 * @brief Gets the internal pointer to the data.
		 * @returns A pointer to the data.
		 */
		constexpr T *get_data() { return m_data; }

		/**
		 * @brief Gets the internal pointer to the data.
		 * @returns A const pointer to the data.
		 */
		constexpr T const *get_data() const { return m_data; }

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Gets the element at the given index.
		 * @param index The index of the element.
		 */
		constexpr T &at(Size const index)
		{
			MINTY_ASSERT(index < S, ErrorCode::Argument_OutOfRange);
			return m_data[index];
		}

		/**
		 * @brief Gets the element at the given index.
		 * @param index The index of the element.
		 */
		constexpr T const &at(Size const index) const
		{
			MINTY_ASSERT(index < S, ErrorCode::Argument_OutOfRange);
			return m_data[index];
		}

		/**
		 * @brief Gets the first element in the Array.
		 * @returns The first element.
		 */
		constexpr T &front() { return at(0); }

		/**
		 * @brief Gets the first element in the Array.
		 * @returns The first element.
		 */
		constexpr T const &front() const { return at(0); }

		/**
		 * @brief Gets the last element in the Array.
		 * @returns The last element.
		 */
		constexpr T &back() { return at(S - 1); }

		/**
		 * @brief Gets the last element in the Array.
		 * @returns The last element.
		 */
		constexpr T const &back() const { return at(S - 1); }

		/**
		 * @brief Creates a sub-Array from the given start index and size.
		 * @tparam N The size of the sub-Array.
		 * @param start The starting index of the sub-Array.
		 */
		template <Size N>
		constexpr Array<T, N> sub(Size const start) const
		{
			MINTY_ASSERT(start < S, ErrorCode::Argument_OutOfRange);
			MINTY_ASSERT(start + N <= S, ErrorCode::Argument_InvalidSize);

			// create new array
			Array<T, N> result;
			for (Size i = 0; i < N; ++i)
			{
				result[i] = m_data[start + i];
			}

			return result;
		}

		/**
		 * @brief Finds the first occurrence of the given value.
		 * @param value The value to find.
		 */
		constexpr Iterator find(T const &value)
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

		/**
		 * @brief Finds the first occurrence of the given value.
		 * @param value The value to find.
		 */
		constexpr ConstIterator find(T const &value) const
		{
			for (Size i = 0; i < S; ++i)
			{
				if (m_data[i] == value)
				{
					return ConstIterator(m_data + i);
				}
			}

			return end();
		}

		/**
		 * @brief Checks if the Array contains the given value.
		 * @param value The value to check for.
		 * @returns True if the value is found, false otherwise.
		 */
		constexpr Bool contains(T const &value) const { return find(value) != end(); }

#pragma endregion

#pragma region Variables

	private:
		T m_data[S];

#pragma endregion
	};
}

#endif // MINTY_DATA_ARRAY_H