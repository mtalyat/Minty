#pragma once
#include "Minty/Core/Base.h"
#include "Minty/Core/Types.h"
#include "Minty/Core/Macro.h"

namespace Minty
{
	/// <summary>
	/// Holds a collection of elements with a dynamic size, as a first in, last out queue.
	/// </summary>
	/// <typeparam name="T">Then type of element.</typeparam>
	template<typename T>
	class Stack
	{
#pragma region Variables

	private:
		Allocator m_allocator;
		Size m_capacity;
		Size m_size;
		T* mp_data;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates an empty Stack.
		/// </summary>
		/// <param name="allocator">The memory allocator to use.</param>
		constexpr Stack(Allocator const allocator = Allocator::Default)
			: m_allocator(allocator)
			, m_capacity(0)
			, m_size(0)
			, mp_data(nullptr)
		{
		}

		/// <summary>
		/// Creates an empty Stack with the given capacity.
		/// </summary>
		/// <param name="capacity">The maximum number of elements.</param>
		/// <param name="allocator">The memory allocator to use.</param>
		Stack(Size const capacity, Allocator const allocator = Allocator::Default)
			: m_allocator(allocator)
			, m_capacity(0)
			, m_size(0)
			, mp_data(nullptr)
		{
			reserve(capacity);
		}

		/// <summary>
		/// Copies the given Stack.
		/// </summary>
		/// <param name="other">The Stack to copy.</param>
		Stack(Stack const& other)
			: m_capacity(0)
			, m_size(0)
			, mp_data(nullptr)
		{
			reserve(other.m_capacity);
			m_size = other.m_size;

			for (Size i = 0; i < m_size; ++i)
			{
				mp_data[i] = other.mp_data[i];
			}
		}

		/// <summary>
		/// Moves the given Stack.
		/// </summary>
		/// <param name="other">The Stack to move.</param>
		Stack(Stack&& other)
			: m_capacity(other.m_capacity)
			, m_size(other.m_size)
			, mp_data(other.mp_data)
		{
			other.m_capacity = 0;
			other.m_size = 0;
			other.mp_data = nullptr;
		}

		constexpr ~Stack()
		{
			if (mp_data)
			{
				deallocate(mp_data, m_capacity * sizeof(T), m_allocator);
			}
		}

#pragma endregion

#pragma region Operators

	public:
		constexpr Stack& operator=(Stack const& other)
		{
			if (this != &other)
			{
				if (mp_data)
				{
					destruct_array(mp_data, m_size, m_allocator);
					mp_data = nullptr;
				}
				m_allocator = other.m_allocator;
				m_capacity = other.m_capacity;
				m_size = other.m_size;
				if (other.mp_data)
				{
					mp_data = construct_array<T>(m_size, m_allocator);
					for (Size i = 0; i < m_size; ++i)
					{
						mp_data[i] = other.mp_data[i];
					}
				}

			}
			return *this;
		}

		constexpr Stack& operator=(Stack&& other) noexcept
		{
			if (this != &other)
			{
				if (mp_data)
				{
					destruct_array(mp_data, m_size, m_allocator);
					mp_data = nullptr;
				}
				m_allocator = other.m_allocator;
				m_capacity = other.m_capacity;
				m_size = other.m_size;
				mp_data = other.mp_data;
				other.m_allocator = Allocator::Default;
				other.m_capacity = 0;
				other.m_size = 0;
				other.mp_data = nullptr;
			}
			return *this;
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the capacity of this Stack.
		/// </summary>
		/// <returns>The maximum number of elements.</returns>
		constexpr Size get_capacity() const { return m_capacity; }

		/// <summary>
		/// Gets the size of this Stack.
		/// </summary>
		/// <returns>The number of elements.</returns>
		constexpr Size get_size() const { return m_size; }

		/// <summary>
		/// Gets the internal pointer to the data.
		/// </summary>
		/// <returns>A pointer to the data.</returns>
		constexpr T* get_data() { return mp_data; }

		/// <summary>
		/// Gets the internal pointer to the data.
		/// </summary>
		/// <returns>A pointer to the data.</returns>
		constexpr T const* get_data() const { return mp_data; }

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Resizes the internal array to the given capacity, if it is larger than the current capacity.
		/// </summary>
		/// <param name="capacity">The new capacity of the Stack.</param>
		void reserve(Size const capacity)
		{
			// do nothing if smaller or equal capacity
			if (capacity <= m_capacity)
			{
				return;
			}

			// create new array
			T* newData = construct_array<T>(capacity, m_allocator);

			// move data over, if it exists
			if (mp_data)
			{
				for (Size i = 0; i < m_size; ++i)
				{
					newData[i] = std::move(mp_data[i]);
				}
				destruct_array(mp_data, m_size, m_allocator);
			}

			// replace data
			mp_data = newData;
			m_capacity = capacity;
		}

		/// <summary>
		/// Adds an element to the end of the Stack.
		/// </summary>
		/// <param name="value">The value to push.</param>
		void push(T const& value)
		{
			// if larger than capacity, reserve more
			if (m_size >= m_capacity)
			{
				if (m_capacity == 0)
				{
					reserve(DEFAULT_COLLECTION_SIZE);
				}
				else
				{
					reserve(m_capacity * 2);
				}
			}

			// push value
			mp_data[m_size++] = value;
		}

		/// <summary>
		/// Adds an element to the end of the Stack.
		/// </summary>
		/// <param name="value">The value to push.</param>
		void push(T&& value)
		{
			// if larger than capacity, reserve more
			if (m_size >= m_capacity)
			{
				if (m_capacity == 0)
				{
					reserve(DEFAULT_COLLECTION_SIZE);
				}
				else
				{
					reserve(m_capacity * 2);
				}
			}

			// push value
			mp_data[m_size++] = std::move(value);
		}

		/// <summary>
		/// Removes the element at the given index.
		/// </summary>
		/// <param name="index">The index to pop the element from.</param>
		T pop()
		{
			MINTY_ASSERT(m_size > 0, "There are no items to pop.");

			// decrement size
			--m_size;

			// return last object
			return std::move(mp_data[m_size]);
		}

		/// <summary>
		/// Checks if this Stack is empty.
		/// </summary>
		/// <returns>True, if the size is zero.</returns>
		Bool is_empty() const { return m_size == 0; }

		/// <summary>
		/// Gets the top element of the Stack.
		/// </summary>
		/// <returns>The topmost element of the Stack.</returns>
		constexpr T& peek()
		{
			MINTY_ASSERT(m_size > 0, "There are no items to peek.");
			return mp_data[m_size - 1];
		}

		/// <summary>
		/// Gets the top element of the Stack.
		/// </summary>
		/// <returns>The topmost element of the Stack.</returns>
		constexpr T const& peek() const
		{
			MINTY_ASSERT(m_size > 0, "There are no items to peek.");
			return mp_data[m_size - 1];
		}

		/// <summary>
		/// Removes all elements from the Stack.
		/// </summary>
		void clear()
		{
			for (Size i = 0; i < m_size; ++i)
			{
				mp_data[i].~T();
			}
			m_size = 0;
		}

#pragma endregion
	};
}