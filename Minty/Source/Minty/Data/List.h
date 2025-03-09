#pragma once
#include "Minty/Core/Base.h"
#include "Minty/Core/Types.h"

namespace Minty
{
	/// <summary>
	/// Provides a collection of elements as a doubly linked list.
	/// </summary>
	/// <typeparam name="T">The type of elements.</typeparam>
	template<typename T>
	class List
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

		/// <summary>
		/// Gets an Iterator to the beginning of the List.
		/// </summary>
		/// <returns>An Iterator pointing to the first element.</returns>
		constexpr Iterator begin() { return Iterator(mp_head); }

		/// <summary>
		/// Gets an Iterator to the end of the List.
		/// </summary>
		/// <returns>An Iterator pointing to the last element + 1.</returns>
		constexpr Iterator end() { return Iterator(nullptr); }

		/// <summary>
		/// Gets an ConstIterator to the beginning of the List.
		/// </summary>
		/// <returns>A ConstIterator pointing to the first element.</returns>
		constexpr ConstIterator begin() const { return ConstIterator(mp_head); }

		/// <summary>
		/// Gets an ConstIterator to the end of the List.
		/// </summary>
		/// <returns>A ConstIterator pointing to the last element + 1.</returns>
		constexpr ConstIterator end() const { return ConstIterator(nullptr); }

		/// <summary>
		/// Gets a ReverseIterator to the beginning of the List.
		/// </summary>
		/// <returns>A ReverseIterator pointing to the first element.</returns>
		constexpr ReverseIterator rbegin() { return ReverseIterator(mp_tail); }

		/// <summary>
		/// Gets an ReverseIterator to the end of the List.
		/// </summary>
		/// <returns>An ReverseIterator pointing to the last element + 1.</returns>
		constexpr ReverseIterator rend() { return ReverseIterator(nullptr); }

		/// <summary>
		/// Gets an ConstReverseIterator to the beginning of the List.
		/// </summary>
		/// <returns>A ConstReverseIterator pointing to the first element.</returns>
		constexpr ConstReverseIterator rbegin() const { return ConstReverseIterator(mp_tail); }

		/// <summary>
		/// Gets an ConstReverseIterator to the end of the List.
		/// </summary>
		/// <returns>A ConstReverseIterator pointing to the last element + 1.</returns>
		constexpr ConstReverseIterator rend() const { return ConstReverseIterator(nullptr); }

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
		/// Creates an empty List.
		/// </summary>
		/// <param name="allocator">The memory allocator to use.</param>
		constexpr List(Allocator const allocator = Allocator::Default)
			: m_allocator(allocator)
			, mp_head(nullptr)
			, mp_tail(nullptr)
			, m_size(0)
		{
		}

		/// <summary>
		/// Creates a List and fills it with the given value.
		/// </summary>
		/// <param name="size">The number of elements to populate.</param>
		/// <param name="value">The value to use.</param>
		/// <param name="allocator">The memory allocator to use.</param>
		List(Size const size, T const& value, Allocator const allocator = Allocator::Default)
			: m_allocator(allocator)
			, mp_head(nullptr)
			, mp_tail(nullptr)
			, m_size(0)
		{
			resize(size);

			Node* node = mp_head;
			while (node)
			{
				node->data = value;
				node = node->next;
			}
		}

		/// <summary>
		/// Creates a List with the given values.
		/// </summary>
		/// <param name="list">The values to set the List data to.</param>
		/// <param name="allocator">The memory allocator to use.</param>
		List(std::initializer_list<T> const& list, Allocator const allocator = Allocator::Default)
			: m_allocator(allocator)
			, mp_head(nullptr)
			, mp_tail(nullptr)
			, m_size(0)
		{
			for (T const& value : list)
			{
				add(value);
			}
		}

		/// <summary>
		/// Copies the given List.
		/// </summary>
		/// <param name="other">The List to copy.</param>
		List(List const& other)
			: m_allocator(other.m_allocator)
			, mp_head(nullptr)
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

		/// <summary>
		/// Moves the given List.
		/// </summary>
		/// <param name="other">The List to move.</param>
		List(List&& other) noexcept
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

		~List()
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
		List& operator=(List const& other)
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
		/// Gets the size of this List.
		/// </summary>
		/// <returns>The number of elements.</returns>
		Size get_size() const { return m_size; }

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Resizes the List to the given size.
		/// </summary>
		/// <param name="size">The number of elements to exist within the list.</param>
		void resize(Size const size)
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
					destruct<Node>(temp, m_allocator);
				}
			}
			else if (size > m_size)
			{
				// add nodes
				Node* node = mp_tail;
				for (Size i = 0; i < size - m_size; ++i)
				{
					node = construct<Node>(m_allocator, T());
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

		/// <summary>
		/// Adds a copy of the given value to the List.
		/// </summary>
		/// <param name="value">The value to add.</param>
		void add(T const& value)
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
		/// Adds the given value to the List.
		/// </summary>
		/// <param name="value">The value to add.</param>
		void add(T&& value)
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
		/// Adds a copy of the given range of values to the List.
		/// </summary>
		/// <typeparam name="IteratorType">The type of iterator to use.</typeparam>
		/// <param name="begin">The beginning of the range.</param>
		/// <param name="end">The end of the range.</param>
		/// <returns>Nothing.</returns>
		template<typename IteratorType>
		std::enable_if<!std::is_integral<IteratorType>::value, void>::type
			add(IteratorType const& begin, IteratorType const& end)
		{
			for (IteratorType it = begin; it != end; ++it)
			{
				add(*it);
			}
		}

		/// <summary>
		/// Inserts a copy of the given value at the given index.
		/// </summary>
		/// <param name="index">The index to insert at.</param>
		/// <param name="value">The value to insert a copy of.</param>
		void insert(Size const index, T const& value)
		{
			MINTY_ASSERT(index <= m_size, "Index is out of bounds.");
			// add to end
			if (index == m_size)
			{
				add(value);
				return;
			}

			Iterator it = begin() + index;
			insert(it, value);
		}

		/// <summary>
		/// Inserts the given value at the given index.
		/// </summary>
		/// <param name="index">The index to insert at.</param>
		/// <param name="value">The value to insert.</param>
		void insert(Size const index, T&& value)
		{
			MINTY_ASSERT(index <= m_size, "Index is out of bounds.");
			// add to end
			if (index == m_size)
			{
				add(std::move(value));
				return;
			}

			Iterator it = begin() + index;
			insert(it, std::move(value));
		}

		/// <summary>
		/// Inserts a copy of the given value at the given iterator.
		/// </summary>
		/// <param name="it">The iterator to insert at.</param>
		/// <param name="value">The value to insert a copy of.</param>
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

		/// <summary>
		/// Inserts the given value at the given iterator.
		/// </summary>
		/// <param name="it">The iterator to insert at.</param>
		/// <param name="value">The value to insert.</param>
		template<typename IteratorType>
		typename std::enable_if<!std::is_integral<IteratorType>::value, void>::type
			insert(IteratorType const& it, T&& value)
		{
			// get adjacent nodes
			Node* nextNode = it.mp_node;
			Node* prevNode = nextNode ? nextNode->prev : nullptr;

			// make new node
			Node* newNode = construct<Node>(m_allocator, std::move(value));

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

		/// <summary>
		/// Inserts the given range of elements at the given index.
		/// </summary>
		/// <typeparam name="IteratorType">The type of iterator to use.</typeparam>
		/// <param name="index">The index to insert at.</param>
		/// <param name="begin">The beginning of the range.</param>
		/// <param name="end">The end of the range.</param>
		/// <returns>Nothing.</returns>
		template<typename IteratorType>
		typename std::enable_if<!std::is_integral<IteratorType>::value, void>::type
			insert(Size const index, IteratorType const& begin, IteratorType const& end)
		{
			MINTY_ASSERT(index <= m_size, "Index is out of bounds.");

			// add to end
			if (index == m_size)
			{
				add(begin, end);
				return;
			}

			Iterator it = this->begin() + index;
			insert(it, begin, end);
		}

		/// <summary>
		/// Inserts the given range of elements at the given index.
		/// </summary>
		/// <typeparam name="InsertIteratorType">The type of iterator to use to insert at.</typeparam>
		/// <typeparam name="IteratorType">The type of iterator to use.</typeparam>
		/// <param name="it">The iterator to insert at.</param>
		/// <param name="begin">The beginning of the range.</param>
		/// <param name="end">The end of the range.</param>
		/// <returns>Nothing.</returns>
		template<typename InsertIteratorType, typename IteratorType>
		typename std::enable_if<!std::is_integral<InsertIteratorType>::value && !std::is_integral<IteratorType>::value, void>::type
			insert(InsertIteratorType const& it, IteratorType const& begin, IteratorType const& end)
		{
			MINTY_ASSERT(it.mp_node != nullptr, "Iterator is out of bounds.");
			MINTY_ASSERT(begin.mp_node != nullptr, "Begin iterator is out of bounds.");
			MINTY_ASSERT(begin != end, "Begin and end iterators are the same.");

			// get adjacent nodes
			Node* nextNode = it.mp_node;
			Node* prevNode = nextNode ? nextNode->prev : nullptr;

			// make new nodes
			IteratorType newIt = begin;
			Node* subHead = construct<Node>(m_allocator, *newIt);
			Node* subTail = subHead;
			++newIt;
			Size count = 1;
			while (newIt != end)
			{
				Node* node = construct<Node>(m_allocator, *newIt);
				subTail->next = node;
				node->prev = subTail;
				subTail = node;

				++newIt;
				++count;
			}

			// link them together
			subTail->next = nextNode;
			subHead->prev = prevNode;
			if (nextNode)
			{
				nextNode->prev = subTail;
			}
			if (prevNode)
			{
				prevNode->next = subHead;
			}

			// update head and tail
			if (nextNode == mp_head)
			{
				mp_head = subHead;
			}
			if (prevNode == mp_tail)
			{
				mp_tail = subTail;
			}

			m_size += count;
		}

		/// <summary>
		/// Removes the element at the given index.
		/// </summary>
		/// <param name="index">The index to remove at.</param>
		void remove(Size const index)
		{
			MINTY_ASSERT(index < m_size, "Index is out of bounds.");

			Iterator it = begin() + index;
			remove(it);
		}

		/// <summary>
		/// Removes the element at the given iterator.
		/// </summary>
		/// <typeparam name="IteratorType">The iterator to use.</typeparam>
		/// <param name="it">The iterator to remove at.</param>
		/// <returns>Nothing.</returns>
		template<typename IteratorType>
		typename std::enable_if<!std::is_integral<IteratorType>::value, void>::type
			remove(IteratorType const& it)
		{
			// get the node
			Node* node = it.mp_node;

			// get the adjacent nodes
			Node* nextNode = node->next;
			Node* prevNode = node->prev;

			// link them together
			if (nextNode)
			{
				nextNode->prev = prevNode;
			}
			if (prevNode)
			{
				prevNode->next = nextNode;
			}

			// update head and tail
			if (node == mp_head)
			{
				mp_head = nextNode;
			}
			if (node == mp_tail)
			{
				mp_tail = prevNode;
			}

			// delete the node
			destruct<Node>(node, m_allocator);

			--m_size;
		}

		/// <summary>
		/// Removes the number of elements at the given index.
		/// </summary>
		/// <param name="index">The index to remove at.</param>
		/// <param name="count">The number of elements to remove.</param>
		void remove(Size const index, Size const count)
		{
			MINTY_ASSERT(index < m_size, "Index is out of bounds.");
			MINTY_ASSERT(index + count <= m_size, "Index + count is out of bounds.");
			MINTY_ASSERT(count > 0, "Count must be greater than zero.");

			Iterator start = begin() + index;
			Iterator stop = start + count;
			remove(start, stop);
		}

		/// <summary>
		/// Removes the range of elements.
		/// </summary>
		/// <typeparam name="IteratorType">The type of iterator to use.</typeparam>
		/// <param name="begin">The beginning of the range.</param>
		/// <param name="end">The end of the range.</param>
		/// <returns>Nothing.</returns>
		template<typename IteratorType>
		typename std::enable_if<!std::is_integral<IteratorType>::value, void>::type
			remove(IteratorType const& begin, IteratorType const& end)
		{
			MINTY_ASSERT(begin.mp_node != nullptr, "Begin iterator is out of bounds.");
			MINTY_ASSERT(begin != end, "Begin and end iterators are the same.");

			// get the nodes
			Node* startNode = begin.mp_node;
			Node* stopNode = end.mp_node;

			// get count
			Size count = 0;
			Node* node = startNode;
			while (node != stopNode)
			{
				++count;
				node = node->next;
			}

			// get the adjacent nodes
			Node* prevNode = startNode->prev;
			Node* nextNode = stopNode;

			// link them together
			if (nextNode)
			{
				nextNode->prev = prevNode;
			}
			if (prevNode)
			{
				prevNode->next = nextNode;
			}

			// update head and tail
			if (startNode == mp_head)
			{
				mp_head = nextNode;
			}
			if (stopNode == nullptr)
			{
				mp_tail = prevNode;
			}

			// delete the nodes
			node = startNode;
			while (node != stopNode)
			{
				Node* temp = node;
				node = node->next;
				destruct<Node>(temp, m_allocator);
			}

			// update size
			m_size -= count;
		}

		/// <summary>
		/// Checks if this List is empty.
		/// </summary>
		/// <returns>True, if size is zero.</returns>
		Bool is_empty() const { return m_size == 0; }

		/// <summary>
		/// Gets the element at the given index.
		/// </summary>
		/// <param name="index">The index of the element to get.</param>
		/// <returns>The value at the given index.</returns>
		T& at(Size const index)
		{
			MINTY_ASSERT(index < m_size, "Index is out of bounds.");
			Iterator it = begin() + index;
			return *it;
		}

		/// <summary>
		/// Gets the element at the given index.
		/// </summary>
		/// <param name="index">The index of the element to get.</param>
		/// <returns>The value at the given index.</returns>
		T const& at(Size const index) const
		{
			MINTY_ASSERT(index < m_size, "Index is out of bounds.");
			ConstIterator it = begin() + index;
			return *it;
		}

		/// <summary>
		/// Creates a sublist of this List.
		/// </summary>
		/// <param name="index">The index to start the sublist at.</param>
		/// <param name="length">The size of the sublist.</param>
		/// <returns>A new List with the elements from the given range.</returns>
		List<T> sub(Size const index, Size const length) const
		{
			MINTY_ASSERT(index < m_size, "Start index is out of bounds.");
			MINTY_ASSERT(index + length <= m_size, "Index + length is out of bounds.");
			MINTY_ASSERT(length > 0, "Length must be greater than zero.");
			List<T> result;
			ConstIterator it = begin() + index;
			for (Size i = 0; i < length; ++i)
			{
				result.add(*it);
				++it;
			}
			return result;
		}

		/// <summary>
		/// Finds a value in the List.
		/// </summary>
		/// <param name="value">The value to find.</param>
		/// <returns>An iterator to the found value, or end() if not found.</returns>
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

		/// <summary>
		/// Finds a value in the List.
		/// </summary>
		/// <param name="value">The value to find.</param>
		/// <returns>An iterator to the found value, or end() if not found.</returns>
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

		/// <summary>
		/// Checks if this List contains the given value.
		/// </summary>
		/// <param name="value">The value to check.</param>
		/// <returns>True if the value was found.</returns>
		Bool contains(T const& value) const { return find(value) != end(); }

		/// <summary>
		/// Removes all elements from this List.
		/// </summary>
		void clear()
		{
			resize(0);
		}

#pragma endregion
	};
}