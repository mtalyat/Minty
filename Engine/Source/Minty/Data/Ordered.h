#ifndef MINTY_DATA_ORDERED_H
#define MINTY_DATA_ORDERED_H

/**
 * @file Ordered.h
 * @brief Defines the Ordered class for an ordered set of unique keys.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Debug/Assert.h"
#include "Minty/Memory/DefaultAllocator.h"

namespace Minty
{
	/**
	 * Holds an ordered set of unique keys, preserving insertion order.
	 * @tparam T The type of the keys.
	 * @tparam AllocatorType The allocator type to use for memory management.
	 */
	template<typename T, template<typename> class AllocatorType = DefaultAllocator>
	class Ordered
	{
#pragma region Types

	private:
		struct Node
		{
			T key;
			Node* next;
			Node* prevOrder;
			Node* nextOrder;

			Node(T const& key)
				: key(key)
				, next(nullptr)
				, prevOrder(nullptr)
				, nextOrder(nullptr)
			{
			}

			Node(T&& key)
				: key(std::move(key))
				, next(nullptr)
				, prevOrder(nullptr)
				, nextOrder(nullptr)
			{
			}
		};

		using Allocator = AllocatorType<Node>;
		using AllocatorList = AllocatorType<Node*>;

#pragma endregion

#pragma region Iterators

	public:
		class Iterator
		{
			friend class Ordered;

		private:
			Node* mp_current;

		private:
			Iterator(Node* current)
				: mp_current(current)
			{
			}

		public:
			T& operator*() const
			{
				MINTY_ASSERT(mp_current, ErrorCode::Object_InvalidState);
				return mp_current->key;
			}

			T* operator->() const
			{
				MINTY_ASSERT(mp_current, ErrorCode::Object_InvalidState);
				return &mp_current->key;
			}

			Iterator& operator++()
			{
				if (mp_current)
				{
					mp_current = mp_current->nextOrder;
				}
				return *this;
			}

			Iterator operator++(int)
			{
				Iterator temp = *this;
				++(*this);
				return temp;
			}

			Iterator operator+(Size const value)
			{
				Iterator temp = *this;
				for (Size i = 0; i < value && temp.mp_current; ++i)
				{
					++temp;
				}
				return temp;
			}

			Bool operator==(Iterator const& other) const
			{
				return mp_current == other.mp_current;
			}

			Bool operator!=(Iterator const& other) const
			{
				return !(*this == other);
			}
		};

		class ConstIterator
		{
			friend class Ordered;

		private:
			Node const* mp_current;

		private:
			ConstIterator(Node const* current)
				: mp_current(current)
			{
			}

		public:
			T const& operator*() const
			{
				MINTY_ASSERT(mp_current, ErrorCode::Object_InvalidState);
				return mp_current->key;
			}

			T const* operator->() const
			{
				MINTY_ASSERT(mp_current, ErrorCode::Object_InvalidState);
				return &mp_current->key;
			}

			ConstIterator& operator++()
			{
				if (mp_current)
				{
					mp_current = mp_current->nextOrder;
				}
				return *this;
			}

			ConstIterator operator++(int)
			{
				ConstIterator temp = *this;
				++(*this);
				return temp;
			}

			ConstIterator operator+(Size const value)
			{
				ConstIterator temp = *this;
				for (Size i = 0; i < value && temp.mp_current; ++i)
				{
					++temp;
				}
				return temp;
			}

			Bool operator==(ConstIterator const& other) const
			{
				return mp_current == other.mp_current;
			}

			Bool operator!=(ConstIterator const& other) const
			{
				return !(*this == other);
			}
		};

		Iterator begin()
		{
			return Iterator(mp_head);
		}

		Iterator end()
		{
			return Iterator(nullptr);
		}

		ConstIterator begin() const
		{
			return ConstIterator(mp_head);
		}

		ConstIterator end() const
		{
			return ConstIterator(nullptr);
		}

#pragma endregion

#pragma region Constructors

	public:
		Ordered()
			: m_capacity(0)
			, m_size(0)
			, mp_table(nullptr)
			, mp_head(nullptr)
			, mp_tail(nullptr)
		{
		}

		Ordered(Size const capacity)
			: m_capacity(capacity)
			, m_size(0)
			, mp_table(nullptr)
			, mp_head(nullptr)
			, mp_tail(nullptr)
		{
			reserve(capacity);
		}

		Ordered(std::initializer_list<T> const& list)
			: m_capacity(0)
			, m_size(0)
			, mp_table(nullptr)
			, mp_head(nullptr)
			, mp_tail(nullptr)
		{
			reserve(list.size() * 2);
			for (T const& key : list)
			{
				add(key);
			}
		}

		Ordered(Ordered const& other)
			: m_capacity(other.m_capacity)
			, m_size(0)
			, mp_table(nullptr)
			, mp_head(nullptr)
			, mp_tail(nullptr)
		{
			reserve(m_capacity);
			for (Node const* node = other.mp_head; node; node = node->nextOrder)
			{
				add(node->key);
			}
		}

		Ordered(Ordered&& other) noexcept
			: m_capacity(other.m_capacity)
			, m_size(other.m_size)
			, mp_table(other.mp_table)
			, mp_head(other.mp_head)
			, mp_tail(other.mp_tail)
		{
			other.m_capacity = 0;
			other.m_size = 0;
			other.mp_table = nullptr;
			other.mp_head = nullptr;
			other.mp_tail = nullptr;
		}

		~Ordered()
		{
			clear();
			if (mp_table)
			{
				AllocatorList().destruct_array(mp_table, m_capacity);
				mp_table = nullptr;
			}
		}

#pragma endregion

#pragma region Operators

	public:
		Ordered& operator=(Ordered const& other)
		{
			if (this != &other)
			{
				clear();
				reserve(other.m_capacity);
				for (Node const* node = other.mp_head; node; node = node->nextOrder)
				{
					add(node->key);
				}
			}
			return *this;
		}

		Ordered& operator=(Ordered&& other) noexcept
		{
			if (this != &other)
			{
				clear();
				if (mp_table)
				{
					AllocatorList().destruct_array(mp_table, m_capacity);
				}
				m_capacity = other.m_capacity;
				m_size = other.m_size;
				mp_table = other.mp_table;
				mp_head = other.mp_head;
				mp_tail = other.mp_tail;
				other.m_capacity = 0;
				other.m_size = 0;
				other.mp_table = nullptr;
				other.mp_head = nullptr;
				other.mp_tail = nullptr;
			}
			return *this;
		}

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the current capacity of this Ordered set.
		 * @returns The capacity.
		 */
		inline Size get_capacity() const { return m_capacity; }

		/**
		 * @brief Gets the number of keys in this Ordered set.
		 * @returns The size.
		 */
		inline Size get_size() const { return m_size; }

		/**
		 * @brief Checks if this Ordered set is empty.
		 * @returns True if no keys are in this Ordered set.
		 */
		inline Bool is_empty() const { return m_size == 0; }

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Reserves space for the given number of keys.
		 * @param capacity The capacity to reserve.
		 */
		void reserve(Size const capacity)
		{
			if (capacity <= m_capacity)
			{
				return;
			}

			Node** newTable = AllocatorList().construct_array(capacity);
			for (Size i = 0; i < capacity; ++i)
			{
				newTable[i] = nullptr;
			}

			if (m_capacity > 0 && mp_table)
			{
				for (Node* node = mp_head; node; node = node->nextOrder)
				{
					node->next = nullptr;
				}
				for (Node* node = mp_head; node; node = node->nextOrder)
				{
					Size index = hash(node->key, capacity);
					node->next = newTable[index];
					newTable[index] = node;
				}
				AllocatorList().destruct_array(mp_table, m_capacity);
			}
			mp_table = newTable;
			m_capacity = capacity;
		}

		/**
		 * @brief Adds a key to this Ordered set.
		 * @param key The key to add.
		 */
		Bool add(T const& key)
		{
			if (contains(key))
			{
				return false;
			}

			if (m_size >= m_capacity * DEFAULT_COLLECTION_REHASH_THRESHOLD)
			{
				rehash();
			}

			Size index = hash(key);
			Node* node = Allocator().construct(key);
			node->next = mp_table[index];
			mp_table[index] = node;

			/** Insert into order list */
			node->prevOrder = mp_tail;
			node->nextOrder = nullptr;
			if (mp_tail)
			{
				mp_tail->nextOrder = node;
			}
			else
			{
				mp_head = node;
			}
			mp_tail = node;

			++m_size;
			return true;
		}

		/**
		 * @brief Adds a key to this Ordered set.
		 * @param key The key to add.
		 */
		Bool add(T&& key)
		{
			if (contains(key))
			{
				return false;
			}

			if (m_size >= m_capacity * DEFAULT_COLLECTION_REHASH_THRESHOLD)
			{
				rehash();
			}

			Size index = hash(key);
			Node* node = Allocator().construct(std::move(key));
			node->next = mp_table[index];
			mp_table[index] = node;

			/** Insert into order list */
			node->prevOrder = mp_tail;
			node->nextOrder = nullptr;
			if (mp_tail)
			{
				mp_tail->nextOrder = node;
			}
			else
			{
				mp_head = node;
			}
			mp_tail = node;

			++m_size;
			return true;
		}

		/**
		 * @brief Removes a key from this Ordered set.
		 * @param key The key to remove.
		 */
		Bool remove(T const& key)
		{
			if (m_size == 0)
			{
				return false;
			}

			Size index = hash(key);
			Node* node = mp_table[index];
			Node* prev = nullptr;
			while (node)
			{
				if (node->key == key)
				{
					/** Remove from hash bucket */
					if (prev)
					{
						prev->next = node->next;
					}
					else
					{
						mp_table[index] = node->next;
					}

					/** Remove from order list */
					if (node->prevOrder)
					{
						node->prevOrder->nextOrder = node->nextOrder;
					}
					else
					{
						mp_head = node->nextOrder;
					}
					if (node->nextOrder)
					{
						node->nextOrder->prevOrder = node->prevOrder;
					}
					else
					{
						mp_tail = node->prevOrder;
					}

					Allocator().destruct(node);
					--m_size;
					return true;
				}
				prev = node;
				node = node->next;
			}

			return false;
		}

		/**
		 * @brief Finds a key in this Ordered set.
		 * @param key The key to find.
		 */
		Iterator find(T const& key)
		{
			if (m_size == 0)
			{
				return end();
			}

			Size index = hash(key);
			Node* node = mp_table[index];
			while (node)
			{
				if (node->key == key)
				{
					return Iterator(node);
				}
				node = node->next;
			}
			return end();
		}

		/**
		 * @brief Finds a key in this Ordered set.
		 * @param key The key to find.
		 */
		ConstIterator find(T const& key) const
		{
			if (m_capacity == 0)
			{
				return end();
			}

			Size index = hash(key);
			Node const* node = mp_table[index];
			while (node)
			{
				if (node->key == key)
				{
					return ConstIterator(node);
				}
				node = node->next;
			}
			return end();
		}

		/**
		 * @brief Checks if this Ordered set contains the given key.
		 * @param key The key to check.
		 */
		inline Bool contains(T const& key) const { return find(key) != end(); }

		/**
		 * @brief Clears this Ordered set.
		 */
		void clear()
		{
			Node* node = mp_head;
			while (node)
			{
				Node* temp = node;
				node = node->nextOrder;
				Allocator().destruct(temp);
			}
			if (mp_table)
			{
				for (Size i = 0; i < m_capacity; ++i)
				{
					mp_table[i] = nullptr;
				}
			}
			mp_head = nullptr;
			mp_tail = nullptr;
			m_size = 0;
		}

	private:
		Size hash(T const& key, Size const capacity) const
		{
			return std::hash<T>{}(key) % capacity;
		}

		Size hash(T const& key) const
		{
			return hash(key, m_capacity);
		}

		void rehash()
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

#pragma endregion

#pragma region Variables

	private:
		Size m_capacity;
		Size m_size;
		Node** mp_table;
		Node* mp_head;
		Node* mp_tail;

#pragma endregion
	};
}

#endif // MINTY_DATA_ORDERED_H