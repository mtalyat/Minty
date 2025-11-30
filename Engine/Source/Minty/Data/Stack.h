#ifndef MINTY_DATA_STACK_H
#define MINTY_DATA_STACK_H

/**
 * @file Stack.h
 * @brief Header file for the Stack class.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Memory/DefaultAllocator.h"

namespace Minty
{
	/**
	 * @class Stack
	 * @brief A simple stack implementation using a dynamic array.
	 * @tparam T The type of elements stored in the stack.
	 * @tparam Allocator The type of allocator used for memory management.
	 */
	template<typename T, typename Allocator = DefaultAllocator>
	class Stack
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates an empty Stack.
		 */
		explicit Stack()
			: m_capacity(0)
			, m_size(0)
			, mp_data(nullptr)
		{
		}

		/**
		 * @brief Creates a Stack with the given initial capacity.
		 * @param capacity The initial capacity.
		 */
		explicit Stack(Size const capacity)
			: m_capacity(0)
			, m_size(0)
			, mp_data(nullptr)
		{
			reserve(capacity);
		}

		/**
		 * @brief Copies the given Stack.
		 * @param other The Stack to copy.
		 */
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

		/**
		 * @brief Moves the given Stack.
		 * @param other The Stack to move.
		 */
		Stack(Stack&& other)
			: m_capacity(other.m_capacity)
			, m_size(other.m_size)
			, mp_data(other.mp_data)
		{
			other.m_allocator = AllocatorType::Default;
			other.m_capacity = 0;
			other.m_size = 0;
			other.mp_data = nullptr;
		}

		~Stack()
		{
			clear();
			if (mp_data)
			{
				deallocate(mp_data, m_capacity * sizeof(T), m_allocator);
			}
		}

#pragma endregion

#pragma region Operators

	public:
		Stack& operator=(Stack const& other)
		{
			if (this != &other)
			{
				if (mp_data)
				{
					Allocator::deallocate(mp_data);
					mp_data = nullptr;
				}
				m_capacity = other.m_capacity;
				m_size = other.m_size;
				if (other.mp_data)
				{
					mp_data = static_cast<T*>(Allocator::allocate(m_capacity * sizeof(T)));
					for (Size i = 0; i < m_size; ++i)
					{
						new (&mp_data[i]) T(other.mp_data[i]);
					}
				}

			}
			return *this;
		}
		
		Stack& operator=(Stack&& other) noexcept
		{
			if (this != &other)
			{
				if (mp_data)
				{
					Allocator::deallocate(mp_data);
					mp_data = nullptr;
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

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the capacity of this Stack.
		 * @returns The capacity.
		 */
		inline Size get_capacity() const { return m_capacity; }

		/**
		* @brief Gets the size of this Stack.
		* @returns The number of elements.
		*/
		inline Size get_size() const { return m_size; }

		/**
		* @brief Gets the internal pointer to the data.
		* @returns A pointer to the data.
		*/
		inline T* get_data() { return mp_data; }

		/**
		* @brief Gets the internal pointer to the data.
		* @returns A pointer to the data.
		*/
		inline T const* get_data() const { return mp_data; }

		/**
		 * @brief Checks if this Stack is empty.
		 * @returns True, if the size is zero.
		 */
		inline Bool is_empty() const { return m_size == 0; }

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Resizes the internal array to the given capacity, if it is larger than the current capacity.
		 * @param capacity The new capacity of the Stack.
		 */
		void reserve(Size const capacity)
		{
			// do nothing if smaller or equal capacity
			if (capacity <= m_capacity)
			{
				return;
			}

			// create new array
			T* newData = static_cast<T*>(allocate(capacity * sizeof(T), m_allocator));

			// move data over, if it exists
			if (mp_data)
			{
				// copy over existing data
				for (Size i = 0; i < m_size; ++i)
				{
					new (&newData[i]) T(std::move(mp_data[i]));
				}
				deallocate(mp_data, m_capacity * sizeof(T), m_allocator);
			}

			// replace data
			mp_data = newData;
			m_capacity = capacity;
		}

		/**
		 * @brief Adds an element to the end of the Stack.
		 * @param value The value to push.
		 */
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
			Any ptr = &mp_data[m_size++];
			new (ptr) T(value);
		}

		/**
		 * @brief Adds an element to the end of the Stack.
		 * @param value The value to push.
		 */
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
			Any ptr = &mp_data[m_size++];
			new (ptr) T(std::move(value));
		}

		/**
		 * @brief Removes the next element in the Stack.
		 */
		T pop()
		{
			MINTY_ASSERT(m_size > 0, ErrorCode::Object_EmptyContainer);

			// decrement size
			--m_size;

			// return last object
			return std::move(mp_data[m_size]);
		}

		/**
		 * @brief Gets the top element of the Stack.\
		 * @returns The topmost element of the Stack.
		 */
		inline T& peek()
		{
			MINTY_ASSERT(m_size > 0, ErrorCode::Object_EmptyContainer);
			return mp_data[m_size - 1];
		}

		/**
		 * @brief Gets the top element of the Stack.\
		 * @returns The topmost element of the Stack.
		 */
		inline T const& peek() const
		{
			MINTY_ASSERT(m_size > 0, ErrorCode::Object_EmptyContainer);
			return mp_data[m_size - 1];
		}

		/**
		 * @brief Clears the contents of the Stack.
		 */
		void clear()
		{
			for (Size i = 0; i < m_size; ++i)
			{
				mp_data[i].~T();
			}
			m_size = 0;
		}

#pragma endregion

#pragma region Variables

	private:
		Size m_capacity;
		Size m_size;
		T* mp_data;

#pragma endregion
	};
}

#endif // MINTY_DATA_STACK_H