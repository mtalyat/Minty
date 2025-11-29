#ifndef MINTY_DATA_LIST_H
#define MINTY_DATA_LIST_H

/**
 * @file List.h
 * @brief Header file for the List class.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Memory/DefaultAllocator.h"
#include <iterator>

namespace Minty
{
	/**
	 * @brief A doubly linked list implementation.
	 * @tparam T The type of elements stored in the list.
	 * @tparam Allocator The allocator type to use for memory management.
	 */
	template<typename T, typename Allocator = DefaultAllocator>
	class List
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

#pragma region Iterators

	public:
		class Iterator
		{
			friend class List;

		public:
			using iterator_category = std::bidirectional_iterator_tag;
			using value_type = T;
			using difference_type = std::ptrdiff_t;
			using pointer = value_type*;
			using reference = value_type&;
			using node_type = Node;
			using node_pointer = node_type*;

		private:
			node_pointer mp_node;

		private:
			constexpr explicit Iterator(node_pointer const ptr)
				: mp_node(ptr)
			{
			}

		public:
			constexpr reference operator*() const
			{
				return mp_node->data;
			}

			Iterator& operator++()
			{
				if (mp_node)
				{
					mp_node = mp_node->next;
				}
				return *this;
			}

			Iterator operator++(int)
			{
				Iterator temp = *this;
				if (mp_node)
				{
					mp_node = mp_node->next;
				}
				return temp;
			}

			Iterator& operator--()
			{
				if (mp_node)
				{
					mp_node = mp_node->prev;
				}
				return *this;
			}

			Iterator operator--(int)
			{
				Iterator temp = *this;
				if (mp_node)
				{
					mp_node = mp_node->prev;
				}
				return temp;
			}

			constexpr Iterator operator+(Size const value)
			{
				Node* node = mp_node;
				for (Size i = 0; i < value; ++i)
				{
					if (node)
					{
						node = node->next;
					}
				}
				return Iterator(node);
			}

			constexpr Iterator operator-(Size const value)
			{
				Node* node = mp_node;
				for (Size i = 0; i < value; ++i)
				{
					if (node)
					{
						node = node->prev;
					}
				}
				return Iterator(node);
			}

			constexpr Bool operator==(Iterator const& other) const { return mp_node == other.mp_node; }
			constexpr Bool operator!=(Iterator const& other) const { return mp_node != other.mp_node; }
		};

		class ConstIterator
		{
			friend class List;

		public:
			using iterator_category = std::bidirectional_iterator_tag;
			using value_type = T const;
			using difference_type = std::ptrdiff_t;
			using pointer = value_type*;
			using reference = value_type&;
			using node_type = Node;
			using node_pointer = node_type*;

		private:
			node_pointer mp_node;

		private:
			constexpr explicit ConstIterator(node_pointer const ptr)
				: mp_node(ptr)
			{
			}

		public:
			constexpr reference operator*() const
			{
				return mp_node->data;
			}

			ConstIterator& operator++()
			{
				if (mp_node)
				{
					mp_node = mp_node->next;
				}
				return *this;
			}

			ConstIterator operator++(int)
			{
				ConstIterator temp = *this;
				if (mp_node)
				{
					mp_node = mp_node->next;
				}
				return temp;
			}

			ConstIterator& operator--()
			{
				if (mp_node)
				{
					mp_node = mp_node->prev;
				}
				return *this;
			}

			ConstIterator operator--(int)
			{
				ConstIterator temp = *this;
				if (mp_node)
				{
					mp_node = mp_node->prev;
				}
				return temp;
			}

			constexpr ConstIterator operator+(Size const value)
			{
				Node* node = mp_node;
				for (Size i = 0; i < value; ++i)
				{
					if (node)
					{
						node = node->next;
					}
				}
				return ConstIterator(node);
			}

			constexpr ConstIterator operator-(Size const value)
			{
				Node* node = mp_node;
				for (Size i = 0; i < value; ++i)
				{
					if (node)
					{
						node = node->prev;
					}
				}
				return ConstIterator(node);
			}

			constexpr Bool operator==(ConstIterator const& other) const { return mp_node == other.mp_node; }
			constexpr Bool operator!=(ConstIterator const& other) const { return mp_node != other.mp_node; }
		};

		class ReverseIterator
		{
			friend class List;

		public:
			using iterator_category = std::bidirectional_iterator_tag;
			using value_type = T;
			using difference_type = std::ptrdiff_t;
			using pointer = value_type*;
			using reference = value_type&;
			using node_type = Node;
			using node_pointer = node_type*;

		private:
			node_pointer mp_node;

		private:
			constexpr explicit ReverseIterator(node_pointer const ptr)
				: mp_node(ptr)
			{
			}

		public:
			constexpr reference operator*() const
			{
				return mp_node->data;
			}

			ReverseIterator& operator++()
			{
				if (mp_node)
				{
					mp_node = mp_node->prev;
				}
				return *this;
			}

			ReverseIterator operator++(int)
			{
				ReverseIterator temp = *this;
				if (mp_node)
				{
					mp_node = mp_node->prev;
				}
				return temp;
			}

			ReverseIterator& operator--()
			{
				if (mp_node)
				{
					mp_node = mp_node->next;
				}
				return *this;
			}

			ReverseIterator operator--(int)
			{
				ReverseIterator temp = *this;
				if (mp_node)
				{
					mp_node = mp_node->next;
				}
				return temp;
			}

			constexpr ReverseIterator operator+(Size const value)
			{
				Node* node = mp_node;
				for (Size i = 0; i < value; ++i)
				{
					if (node)
					{
						node = node->prev;
					}
				}
				return ReverseIterator(node);
			}

			constexpr ReverseIterator operator-(Size const value)
			{
				Node* node = mp_node;
				for (Size i = 0; i < value; ++i)
				{
					if (node)
					{
						node = node->next;
					}
				}
				return ReverseIterator(node);
			}

			constexpr Bool operator==(ReverseIterator const& other) const { return mp_node == other.mp_node; }
			constexpr Bool operator!=(ReverseIterator const& other) const { return mp_node != other.mp_node; }
		};

		class ConstReverseIterator
		{
			friend class List;

		public:
			using iterator_category = std::bidirectional_iterator_tag;
			using value_type = T const;
			using difference_type = std::ptrdiff_t;
			using pointer = value_type*;
			using reference = value_type&;
			using node_type = Node;
			using node_pointer = node_type*;

		private:
			node_pointer mp_node;

		private:
			constexpr explicit ConstReverseIterator(node_pointer const ptr)
				: mp_node(ptr)
			{
			}

		public:
			constexpr reference operator*() const
			{
				return mp_node->data;
			}

			ConstReverseIterator& operator++()
			{
				if (mp_node)
				{
					mp_node = mp_node->prev;
				}
				return *this;
			}

			ConstReverseIterator operator++(int)
			{
				ConstReverseIterator temp = *this;
				if (mp_node)
				{
					mp_node = mp_node->prev;
				}
				return temp;
			}

			ConstReverseIterator& operator--()
			{
				if (mp_node)
				{
					mp_node = mp_node->next;
				}
				return *this;
			}

			ConstReverseIterator operator--(int)
			{
				ConstReverseIterator temp = *this;
				if (mp_node)
				{
					mp_node = mp_node->next;
				}
				return temp;
			}

			constexpr ConstReverseIterator operator+(Size const value)
			{
				Node* node = mp_node;
				for (Size i = 0; i < value; ++i)
				{
					if (node)
					{
						node = node->prev;
					}
				}
				return ConstReverseIterator(node);
			}

			constexpr ConstReverseIterator operator-(Size const value)
			{
				Node* node = mp_node;
				for (Size i = 0; i < value; ++i)
				{
					if (node)
					{
						node = node->next;
					}
				}
				return ConstReverseIterator(node);
			}

			constexpr Bool operator==(ConstReverseIterator const& other) const { return mp_node == other.mp_node; }
			constexpr Bool operator!=(ConstReverseIterator const& other) const { return mp_node != other.mp_node; }
		};

		inline Iterator begin() { return Iterator(mp_head); }
		inline Iterator end() { return Iterator(nullptr); }
		inline ConstIterator begin() const { return ConstIterator(mp_head); }
		inline ConstIterator end() const { return ConstIterator(nullptr); }
		inline ReverseIterator rbegin() { return ReverseIterator(mp_tail); }
		inline ReverseIterator rend() { return ReverseIterator(nullptr); }
		inline ConstReverseIterator rbegin() const { return ConstReverseIterator(mp_tail); }
		inline ConstReverseIterator rend() const { return ConstReverseIterator(nullptr); }

#pragma endregion

#pragma region Constructors

	public:
		/**
		 * @brief Creates an empty List.
		 */
		constexpr List()
			: mp_head(nullptr)
			, mp_tail(nullptr)
			, m_size(0)
		{
		}

		/**
		 * @brief Creates a List with the given size, initializing all elements to the given value.
		 * @param size The number of elements in the List.
		 */
		template<typename... Args>
		List(Size const size, Args&&... value)
			: mp_head(nullptr)
			, mp_tail(nullptr)
			, m_size(0)
		{
			resize(size, std::forward<Args>(value)...);
		}

		/**
		 * @brief Creates a List from an initializer list.
		 * @param list The initializer list of elements.
		 */
		List(std::initializer_list<T> const& list)
			: mp_head(nullptr)
			, mp_tail(nullptr)
			, m_size(0)
		{
			for (T const& value : list)
			{
				add(value);
			}
		}

		/**
		 * @brief Copies the given List.
		 * @param other The List to copy.
		 */
		List(List const& other)
			: mp_head(nullptr)
			, mp_tail(nullptr)
			, m_size(0)
		{
			Node* node = other.mp_head;
			while (node)
			{
				add(node->data);
				node = node->next;
			}
		}

		/**
		 * @brief Moves the given List.
		 * @param other The List to move.
		 */
		List(List&& other) noexcept
			: mp_head(other.mp_head)
			, mp_tail(other.mp_tail)
			, m_size(other.m_size)
		{
			other.mp_head = nullptr;
			other.mp_tail = nullptr;
			other.m_size = 0;
		}

		~List()
		{
			clear();
		}

#pragma endregion

#pragma region Operators

	public:
		List& operator=(List const& other)
		{
			if (this != &other)
			{
				Node* node = mp_head;
				while (node)
				{
					Node* temp = node;
					node = node->next;
					Allocator::destruct<Node>(temp);
				}
				mp_head = nullptr;
				mp_tail = nullptr;
				m_size = 0;
				node = other.mp_head;
				while (node)
				{
					add(node->data);
					node = node->next;
				}
			}
			return *this;
		}

		List& operator=(List&& other) noexcept
		{
			if (this != &other)
			{
				Node* node = mp_head;
				while (node)
				{
					Node* temp = node;
					node = node->next;
					Allocator::destruct<Node>(temp);
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

		constexpr T& operator[](Size const index) { return at(index); }

		constexpr T const& operator[](Size const index) const { return at(index); }

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the element at the given index.
		 * @param index The index of the element to get.
		 */
		inline Size get_size() const { return m_size; }

		/**
		 * @brief Peeks at the last element in the List without removing it.
		 * @returns A reference to the last element.
		 */
		inline Bool is_empty() const { return m_size == 0; }

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Clears all elements from the List.
		 * @tparam Args Additional arguments for value construction.
		 * @param index The index to get.
		 * @param value The value to initialize new elements with.
		 */
		template<typename... Args>
		void resize(Size const size, Args&&... value)
		{
			if (size < m_size)
			{
				// remove nodes

				// find node to start removing at
				Node* node = mp_head;
				for (Size i = 0; i < size; i++)
				{
					node = node->next;
				}

				// update head and tail
				if (node == mp_head)
				{
					mp_head = nullptr;
					mp_tail = nullptr;
				}
				else
				{
					mp_tail = node->prev;
					mp_tail->next = nullptr;
				}

				// delete nodes
				while (node)
				{
					Node* temp = node;
					node = node->next;
					Allocator::destruct<Node>(temp);
				}
			}
			else if (size > m_size)
			{
				// add nodes
				Node* node = mp_tail;
				for (Size i = 0; i < size - m_size; ++i)
				{
					node = Allocator::construct<Node>(value);
					node->prev = mp_tail;
					if (mp_tail)
					{
						mp_tail->next = node;
					}
					if (!mp_head)
					{
						mp_head = node;
					}
					mp_tail = node;
				}
			}

			m_size = size;
		}

		/**
		 * @brief Gets the element at the given index.
		 * @param index The index of the element to get.
		 */
		void add(T&& value)
		{
			Node* node = Allocator::construct<Node>(value);
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
		 * @brief Adds the given value to the List.
		 * @param value The value to add.
		 */
		void push(T const& value) { add(value); }

		/**
		 * @brief Adds the given value to the List.
		 * @param value The value to add.
		 */
		void push(T&& value) { add(std::move(value)); }

		/**
		 * @brief Inserts the given value at the given index.
		 * @param index The index to insert at.
		 */
		void insert(Size const index, T const& value)
		{
			MINTY_ASSERT(index <= m_size, ErrorCode::Argument_OutOfBounds);
			// add to end
			if (index == m_size)
			{
				add(value);
				return;
			}

			Iterator it = begin() + index;
			insert(it, value);
		}

		/**
		 * @brief Inserts the given value at the given index.
		 * @param index The index to insert at.
		 */
		void insert(Size const index, T&& value)
		{
			MINTY_ASSERT(index <= m_size, ErrorCode::Argument_OutOfBounds);
			// add to end
			if (index == m_size)
			{
				add(std::move(value));
				return;
			}

			Iterator it = begin() + index;
			insert(it, std::move(value));
		}

		/**
		 * @brief Inserts the given value at the given iterator.
		 * @param it The iterator to insert at.
		 */
		template<typename IteratorType>
		typename std::enable_if<!std::is_integral<IteratorType>::value, void>::type
			insert(IteratorType const& it, T const& value)
		{
			// get adjacent nodes
			Node* nextNode = it.mp_node;
			Node* prevNode = nextNode ? nextNode->prev : nullptr;

			// make new node
			Node* newNode = construct<Node>(m_allocator, value);

			// link them together
			newNode->next = nextNode;
			newNode->prev = prevNode;
			if (nextNode)
			{
				nextNode->prev = newNode;
			}
			if (prevNode)
			{
				prevNode->next = newNode;
			}

			// update head and tail
			if (nextNode == mp_head)
			{
				mp_head = newNode;
			}
			if (prevNode == mp_tail)
			{
				mp_tail = newNode;
			}

			++m_size;
		}

		/**
		 * @brief Inserts the given value at the given iterator.
		 * @param it The iterator to insert at.
		 */
		void remove(Size const index)
		{
			MINTY_ASSERT(index < m_size, ErrorCode::Argument_OutOfBounds);

			Iterator it = begin() + index;
			remove(it);
		}

		/**
		 * @brief Removes the range of elements.
		 * @param index The starting index.	
		 */
		void remove(Size const index, Size const count)
		{
			MINTY_ASSERT(index < m_size, ErrorCode::Argument_OutOfBounds);
			MINTY_ASSERT(index + count <= m_size, ErrorCode::Argument_InvalidSize);
			MINTY_ASSERT(count > 0, ErrorCode::Argument_ExpectedNonZero);

			Iterator start = begin() + index;
			Iterator stop = start + count;
			remove(start, stop);
		}

		/**
		 * @brief Pops the last element off the List.
		 */
		void pop()
		{
			Node* node = mp_tail;
			if (node)
			{
				Node* prevNode = node->prev;
				if (prevNode)
				{
					prevNode->next = nullptr;
				}
				else
				{
					// if no previous node, then this is the only node
					mp_head = nullptr;
				}
				mp_tail = prevNode;
				destruct<Node>(node, m_allocator);
				--m_size;
			}
		}

		/**
		 * @brief Gets the element at the given index.
		 * @param index The index of the element to get.
		 * @returns A reference to the element at the given index.
		 */
		T& at(Size const index)
		{
			MINTY_ASSERT(index < m_size, ErrorCode::Argument_OutOfBounds);
			Iterator it = begin() + index;
			return *it;
		}

		/**
		 * @brief Gets the element at the given index.
		 * @param index The index of the element to get.
		 * @returns A reference to the element at the given index.
		 */
		T const& at(Size const index) const
		{
			MINTY_ASSERT(index < m_size, ErrorCode::Argument_OutOfBounds);
			ConstIterator it = begin() + index;
			return *it;
		}

		/**
		 * @brief Gets the first element in the List.
		 * @returns The first element.
		 */
		T& front() { return mp_head->data; }

		/**
		 * @brief Gets the first element in the List.
		 * @returns The first element.
		 */
		T const& front() const { return mp_head->data; }

		/**
		 * @brief Gets the last element in the List.
		 * @returns The last element.
		 */
		T& back() { return mp_tail->data; }

		/**
		 * @brief Gets the last element in the List.
		 * @returns The last element.
		 */
		T const& back() const { return mp_tail->data; }

		/**
		 * @brief Gets the last element in the List.
		 * @returns The last element.
		 */
		T& peek() { return back(); }

		/**
		 * @brief Gets the last element in the List.
		 * @returns The last element.
		 */
		T const& peek() const { return back(); }

		/**
		 * @brief Creates a sublist from the List.
		 * @param index The starting index of the sublist.
		 * @param length The length of the sublist.
		 */
		List<T> sub(Size const index, Size const length) const
		{
			MINTY_ASSERT(index < m_size, ErrorCode::Argument_OutOfBounds);
			MINTY_ASSERT(index + length <= m_size, ErrorCode::Argument_InvalidSize);
			MINTY_ASSERT(length > 0, ErrorCode::Argument_ExpectedNonZero);
			List<T> result;
			ConstIterator it = begin() + index;
			for (Size i = 0; i < length; ++i)
			{
				result.add(*it);
				++it;
			}
			return result;
		}

		/**
		 * @brief Finds a value in the List.
		 * @param value The value to find.
		 * @returns An iterator to the found value, or end() if not found.
		 */
		Iterator find(T const& value)
		{
			Iterator it = begin();
			while (it != end())
			{
				if (*it == value)
				{
					return it;
				}
				++it;
			}
			return end();
		}

		/**
		 * @brief Finds a value in the List.
		 * @param value The value to find.
		 * @returns An iterator to the found value, or end() if not found.
		 */
		ConstIterator find(T const& value) const
		{
			ConstIterator it = begin();
			while (it != end())
			{
				if (*it == value)
				{
					return it;
				}
				++it;
			}
			return end();
		}

		/**
		 * @brief Checks if the List contains the given value.
		 * @param value The value to check for.
		 * @returns True if the value is found, false otherwise.
		 */
		inline Bool contains(T const& value) const { return find(value) != end(); }

		/**
		 * @brief Clears all elements from the List.
		 */
		void clear()
		{
			// remove nodes
			Node* node = mp_head;

			// update head and tail
			mp_head = nullptr;
			mp_tail = nullptr;

			// delete nodes
			while (node)
			{
				Node* temp = node;
				node = node->next;
				destruct<Node>(temp, m_allocator);
			}

			m_size = 0;
		}

#pragma endregion

#pragma region Variables

	private:
		Node* mp_head;
		Node* mp_tail;
		Size m_size;

#pragma endregion
	};
}

#endif // MINTY_DATA_LIST_H