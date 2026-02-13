#ifndef MINTY_DATA_QUEUE_H
#define MINTY_DATA_QUEUE_H

/**
 * @file Queue.h
 * @brief Header file for the Queue class.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Debug/Debug.h"
#include "Minty/Memory/DebugAllocator.h"
#include "Minty/Memory/HeapAllocator.h"

namespace Minty
{
	/**
	 * @class Queue
	 * @brief A simple FIFO queue implementation using a doubly linked list.
	 * @tparam T The type of elements stored in the queue.
	 */
	template<typename T, typename Allocator = DefaultAllocator>
	class Queue
	{
#pragma region Types

	private:
		struct Node
		{
			T data;
			Node* next;
			Node* prev;
			Node(T const& data)
				: data(data)
				, next(nullptr)
				, prev(nullptr)
			{
			}

			Node(T&& data)
				: data(std::move(data))
				, next(nullptr)
				, prev(nullptr)
			{
			}
		};

#pragma endregion

#pragma region Constructors

	public:
		/**
		 * @brief Creates an empty Queue.
		 */
		constexpr Queue()
			: mp_head(nullptr)
			, mp_tail(nullptr)
			, m_size(0)
			, m_allocator()
		{
		}

		/**
		 * @brief Copies the given Queue.
		 * @param other The Queue to copy.
		 */
		Queue(Queue const& other)
			: mp_head(nullptr)
			, mp_tail(nullptr)
			, m_size(0)
			, m_allocator()
		{
			Node* node = other.mp_head;
			while (node)
			{
				push(node->data);
				node = node->next;
			}
		}

		/**
		 * @brief Moves the given Queue.
		 * @param other The Queue to move.
		 */
		Queue(Queue&& other) noexcept
			: mp_head(other.mp_head)
			, mp_tail(other.mp_tail)
			, m_size(other.m_size)
			, m_allocator(std::move(other.m_allocator))
		{
			other.mp_head = nullptr;
			other.mp_tail = nullptr;
			other.m_size = 0;
		}

		~Queue()
		{
			Node* node = mp_head;
			while (node)
			{
				Node* temp = node;
				node = node->next;
				m_allocator.destruct(temp);
			}
		}

#pragma endregion

#pragma region Operators

	public:
		Queue& operator=(Queue const& other)
		{
			if (this != &other)
			{
				Node* node = mp_head;
				while (node)
				{
					Node* temp = node;
					node = node->next;
					m_allocator.destruct(temp);
				}
				mp_head = nullptr;
				mp_tail = nullptr;
				m_size = 0;
				node = other.mp_head;
				while (node)
				{
					push(node->data);
					node = node->next;
				}
			}
			return *this;
		}

		Queue& operator=(Queue&& other) noexcept
		{
			if (this != &other)
			{
				Node* node = mp_head;
				while (node)
				{
					Node* temp = node;
					node = node->next;
					m_allocator.destruct(temp);
				}
				mp_head = other.mp_head;
				mp_tail = other.mp_tail;
				m_size = other.m_size;
				other.mp_head = nullptr;
				other.mp_tail = nullptr;
				other.m_size = 0;
			}
			return *this;
		}

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the size of this Queue.
		 * @returns The size.
		 */
		inline Size get_size() const { return m_size; }
		
		/**
		 * @brief Checks if this Queue is empty.
		 * @returns True if the Queue is empty.
		 */
		inline Bool is_empty() const { return m_size == 0; }

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Pushes the given value to the Queue.
		 * @param value The value to push.
		 */
		void push(T const& value)
		{
			Node* const node = m_allocator.construct<Node>(value);
			if (mp_head == nullptr)
			{
				mp_head = node;
				mp_tail = node;
			}
			else
			{
				mp_tail->next = node;
				node->prev = mp_tail;
				mp_tail = node;
			}
			++m_size;
		}

		/**
		 * @brief Pushes the given value to the Queue.
		 * @param value The value to push.
		 */
		void push(T&& value)
		{
			Node* const node = m_allocator.construct<Node>(std::move(value));
			if (mp_head == nullptr)
			{
				mp_head = node;
				mp_tail = node;
			}
			else
			{
				mp_tail->next = node;
				node->prev = mp_tail;
				mp_tail = node;
			}
			++m_size;
		}

		/**
		 * @brief Pops the next value from the Queue.
		 * @returns The popped value.
		 */
		T pop()
		{
			MINTY_ASSERT(m_size > 0, ErrorCode::Object_EmptyContainer);

			// get the node to remove
			Node* node = mp_head;
			mp_head = node->next;
			if (mp_head)
			{
				mp_head->prev = nullptr;
			}
			else
			{
				mp_tail = nullptr;
			}

			// get the data
			T data = std::move(node->data);
			m_allocator.destruct(node);
			
			// update size
			--m_size;

			return data;
		}

		/**
		 * @brief Gets the next element to be popped in the Queue.
		 * @returns A reference to the next element.
		 */
		T& peek()
		{
			MINTY_ASSERT(m_size > 0, ErrorCode::Object_EmptyContainer);
			return mp_head->data;
		}

		/**
		 * @brief Gets the next element to be popped in the Queue.
		 * @returns A const reference to the next element.
		 */
		T const& peek() const
		{
			MINTY_ASSERT(m_size > 0, ErrorCode::Object_EmptyContainer);
			return mp_head->data;
		}
		
		/**
		 * @brief Clears all elements from the Queue.
		 */
		void clear()
		{
			Node* node = mp_head;
			while (node)
			{
				Node* temp = node;
				node = node->next;
				m_allocator.destruct(temp);
			}
			mp_head = nullptr;
			mp_tail = nullptr;
			m_size = 0;
		}

#pragma endregion

#pragma region Variables

	private:
		Node* mp_head;
		Node* mp_tail;
		Size m_size;
		Allocator m_allocator;

#pragma endregion
	};
}

#endif // MINTY_DATA_QUEUE_H