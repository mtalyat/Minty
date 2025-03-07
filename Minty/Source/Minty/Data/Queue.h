#pragma once
#include "Minty/Core/Base.h"
#include "Minty/Core/Macro.h"
#include "Minty/Core/Types.h"

namespace Minty
{
	/// <summary>
	/// Provides a collection of elements with a first in, first out queue.
	/// </summary>
	/// <typeparam name="T">The type of elements.</typeparam>
	template<typename T>
	class Queue
	{
#pragma region Classes

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

#pragma region Variables

	private:
		Allocator m_allocator;
		Node* mp_head;
		Node* mp_tail;
		Size m_size;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates an empty Queue.
		/// </summary>
		/// <param name="allocator">The memory allocator to use.</param>
		constexpr Queue(Allocator const allocator = Allocator::Default)
			: m_allocator(allocator)
			, mp_head(nullptr)
			, mp_tail(nullptr)
			, m_size(0)
		{
		}

		/// <summary>
		/// Copies the given Queue.
		/// </summary>
		/// <param name="other">The Queue to copy.</param>
		Queue(Queue const& other)
			: m_allocator(other.m_allocator)
			, mp_head(nullptr)
			, mp_tail(nullptr)
			, m_size(0)
		{
			Node* node = other.mp_head;
			while (node)
			{
				push(node->data);
				node = node->next;
			}
		}

		/// <summary>
		/// Moves the given Queue.
		/// </summary>
		/// <param name="other">The Queue to move.</param>
		Queue(Queue&& other) noexcept
			: m_allocator(other.m_allocator)
			, mp_head(other.mp_head)
			, mp_tail(other.mp_tail)
			, m_size(other.m_size)
		{
			other.m_allocator = Allocator::Default;
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
				destruct<Node>(temp, m_allocator);
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
					destruct<Node>(temp, m_allocator);
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
					destruct<Node>(temp, m_allocator);
				}
				m_allocator = other.m_allocator;
				mp_head = other.mp_head;
				mp_tail = other.mp_tail;
				m_size = other.m_size;
				other.m_allocator = Allocator::Default;
				other.mp_head = nullptr;
				other.mp_tail = nullptr;
				other.m_size = 0;
			}
			return *this;
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the size of this Queue.
		/// </summary>
		/// <returns>The number of elements.</returns>
		Size get_size() const { return m_size; }

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Pushes a copy of the given value to the Queue.
		/// </summary>
		/// <param name="value">The value to push.</param>
		void push(T const& value)
		{
			Node* node = construct<Node>(m_allocator, value);
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

		/// <summary>
		/// Pushes the given value to the Queue.
		/// </summary>
		/// <param name="value">The value to push.</param>
		void push(T&& value)
		{
			Node* node = construct<Node>(m_allocator, std::move(value));
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

		/// <summary>
		/// Pops the next element in the Queue.
		/// </summary>
		T pop()
		{
			MINTY_ASSERT(m_size > 0, "There is nothing to pop.");

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
			destruct<Node>(node, m_allocator);
			
			// update size
			--m_size;

			return data;
		}

		/// <summary>
		/// Checks if this Queue is empty.
		/// </summary>
		/// <returns>True, if size is zero.</returns>
		Bool is_empty() const { return m_size == 0; }

		/// <summary>
		/// Gets the next element to be popped in the Queue.
		/// </summary>
		/// <returns>A reference to the next element.</returns>
		T& peek()
		{
			MINTY_ASSERT(m_size > 0, "There is nothing to peek at.");
			return mp_head->data;
		}

		/// <summary>
		/// Gets the next element to be popped in the Queue.
		/// </summary>
		/// <returns>A reference to the next element.</returns>
		T const& peek() const
		{
			MINTY_ASSERT(m_size > 0, "There is nothing to peek at.");
			return mp_head->data;
		}

		/// <summary>
		/// Pops all elements from this Queue.
		/// </summary>
		void clear()
		{
			Node* node = mp_head;
			while (node)
			{
				Node* temp = node;
				node = node->next;
				destruct<Node>(temp, m_allocator);
			}
			mp_head = nullptr;
			mp_tail = nullptr;
			m_size = 0;
		}

#pragma endregion
	};
}