#pragma once

/**
 * @file Set.h
 * @brief Header file defining the Set class.
 * @author Mitchell Talyat
 */

#include "Platform/Type/Primitive.h"
#include "Core/Debug/Debug.h"
#include "Core/Memory/DefaultAllocator.h"

namespace Minty
{
	/**
	 * @brief A Set is a collection of unique keys, stored in a hash table.
	 * @tparam T The type of the keys.
	 * @tparam AllocatorType The allocator type to use for memory management.
	 */
	template <typename T, typename Allocator = DefaultAllocator>
	class Set
	{
#pragma region Types

	private:
		struct Node
		{
			T key;
			Node *next;

			Node(T const &key)
				: key(key), next(nullptr)
			{
			}

			Node(T &&key)
				: key(std::move(key)), next(nullptr)
			{
			}
		};

#pragma endregion

#pragma region Iterators

	public:
		class Iterator
		{
			friend class Set;

		private:
			Node **mp_table;
			Size m_capacity;
			Size m_bucketIndex;
			Node *mp_current;

		private:
			void advance()
			{
				while (!mp_current && m_bucketIndex < m_capacity)
				{
					mp_current = mp_table[m_bucketIndex];
					if (!mp_current)
					{
						++m_bucketIndex;
					}
				}
			}

		private:
			Iterator(Node **const table, Size const capacity, Size const bucketIndex, Node *const current)
				: mp_table(table), m_capacity(capacity), m_bucketIndex(bucketIndex), mp_current(current)
			{
				// if no current given, advance to next
				if (bucketIndex < m_capacity && !mp_current)
				{
					advance();
				}
			}

		public:
			T &operator*() const
			{
				MINTY_ASSERT(mp_current, ErrorCodeEnum::Object_InvalidState);
				return mp_current->key;
			}

			T *operator->() const
			{
				MINTY_ASSERT(mp_current, ErrorCodeEnum::Object_InvalidState);
				return &mp_current->key;
			}

			Iterator &operator++()
			{
				if (mp_current)
				{
					mp_current = mp_current->next;
					if (!mp_current)
					{
						++m_bucketIndex;
						advance();
					}
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
				for (Size i = 0; i < value; ++i)
				{
					++temp;
				}
				return temp;
			}

			Bool operator==(Iterator const &other) const
			{
				return mp_table == other.mp_table && m_capacity == other.m_capacity && m_bucketIndex == other.m_bucketIndex && mp_current == other.mp_current;
			}

			Bool operator!=(Iterator const &other) const
			{
				return !(*this == other);
			}
		};

		class ConstIterator
		{
			friend class Set;

		private:
			Node *const *mp_table;
			Size m_capacity;
			Size m_bucketIndex;
			Node const *mp_current;

		private:
			void advance()
			{
				while (!mp_current && m_bucketIndex < m_capacity)
				{
					mp_current = mp_table[m_bucketIndex];
					if (!mp_current)
					{
						++m_bucketIndex;
					}
				}
			}

		private:
			ConstIterator(Node *const *const table, Size const capacity, Size const bucketIndex, Node const *const current)
				: mp_table(table), m_capacity(capacity), m_bucketIndex(bucketIndex), mp_current(current)
			{
				// if no current given, advance to next
				if (bucketIndex < m_capacity && !mp_current)
				{
					advance();
				}
			}

		public:
			T const &operator*() const
			{
				MINTY_ASSERT(mp_current, ErrorCodeEnum::Object_InvalidState);
				return mp_current->key;
			}

			T const *operator->() const
			{
				MINTY_ASSERT(mp_current, ErrorCodeEnum::Object_InvalidState);
				return &mp_current->key;
			}

			ConstIterator &operator++()
			{
				if (mp_current)
				{
					mp_current = mp_current->next;
					if (!mp_current)
					{
						++m_bucketIndex;
						advance();
					}
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
				for (Size i = 0; i < value; ++i)
				{
					++temp;
				}
				return temp;
			}

			Bool operator==(ConstIterator const &other) const
			{
				return mp_table == other.mp_table && m_capacity == other.m_capacity && m_bucketIndex == other.m_bucketIndex && mp_current == other.mp_current;
			}

			Bool operator!=(ConstIterator const &other) const
			{
				return !(*this == other);
			}
		};

		Iterator begin()
		{
			if (m_capacity)
			{
				return Iterator(mp_table, m_capacity, 0, mp_table[0]);
			}
			else
			{
				return end();
			}
		}
		Iterator end() { return Iterator(mp_table, m_capacity, m_capacity, nullptr); }
		ConstIterator begin() const
		{
			if (m_capacity)
			{
				return ConstIterator(mp_table, m_capacity, 0, mp_table[0]);
			}
			else
			{
				return end();
			}
		}
		ConstIterator end() const { return ConstIterator(mp_table, m_capacity, m_capacity, nullptr); }

#pragma endregion

#pragma region Constructors

	public:
		/**
		 * @brief Creates an empty Set.
		 */
		Set()
			: m_capacity(0), m_size(0), mp_table(nullptr), m_allocator()
		{
		}

		/**
		 * @brief Creates a Set with the given capacity.
		 * @param capacity The initial capacity.
		 */
		Set(Size const capacity)
			: m_capacity(0), m_size(0), mp_table(nullptr), m_allocator()
		{
			reserve(capacity);
		}

		/**
		 * @brief Creates a Set with the given initializer list.
		 * @param list The list of keys to add.
		 */
		Set(std::initializer_list<T> const &list)
			: m_capacity(0), m_size(0), mp_table(nullptr), m_allocator()
		{
			reserve(list.size() * 2);
			for (T const &key : list)
			{
				add(key);
			}
		}

		/**
		 * @brief Copy constructor.
		 * @param other The other Set to copy.
		 */
		Set(Set const &other)
			: m_capacity(other.m_capacity), m_size(other.m_size), mp_table(nullptr), m_allocator()
		{
			if (m_capacity == 0)
			{
				return;
			}

			mp_table = m_allocator.construct_array<Node *>(m_capacity, nullptr);

			for (Size i = 0; i < m_capacity; ++i)
			{
				Node *node = other.mp_table[i];
				Node *prev = nullptr;
				while (node)
				{
					Node *newNode = m_allocator.construct<Node>(node->key);
					if (prev)
					{
						prev->next = newNode;
					}
					else
					{
						mp_table[i] = newNode;
					}
					prev = newNode;
					node = node->next;
				}
			}
		}

		/**
		 * @brief Move constructor.
		 * @param other The other Set to move.
		 */
		Set(Set &&other) noexcept
			: m_capacity(other.m_capacity), m_size(other.m_size), mp_table(other.mp_table), m_allocator(std::move(other.m_allocator))
		{
			other.m_capacity = 0;
			other.m_size = 0;
			other.mp_table = nullptr;
		}

		~Set()
		{
			clear();
			if (mp_table)
			{
				m_allocator.destruct_array(mp_table, m_capacity);
			}
		}

#pragma endregion

#pragma region Operators

	public:
		Set &operator=(Set const &other)
		{
			if (this != &other)
			{
				clear();
				m_allocator.destruct_array(mp_table, m_capacity);
				m_allocator = Allocator();
				m_capacity = other.m_capacity;
				m_size = other.m_size;
				if (m_capacity == 0)
				{
					mp_table = nullptr;
				}
				else
				{
					mp_table = m_allocator.construct_array<Node *>(m_capacity, nullptr);
					for (Size i = 0; i < m_capacity; ++i)
					{
						Node *node = other.mp_table[i];
						Node *prev = nullptr;
						while (node)
						{
							Node *const newNode = m_allocator.construct<Node>(node->key);
							if (prev)
							{
								prev->next = newNode;
							}
							else
							{
								mp_table[i] = newNode;
							}
							prev = newNode;
							node = node->next;
						}
					}
				}
			}
			return *this;
		}

		Set &operator=(Set &&other) noexcept
		{
			if (this != &other)
			{
				clear();
				m_allocator.destruct_array(mp_table, m_capacity);
				m_capacity = other.m_capacity;
				m_size = other.m_size;
				mp_table = other.mp_table;
				m_allocator = std::move(other.m_allocator);
				other.m_capacity = 0;
				other.m_size = 0;
				other.mp_table = nullptr;
			}
			return *this;
		}

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the capacity of this Set.
		 * @returns The capacity.
		 */
		inline Size get_capacity() const { return m_capacity; }

		/**
		 * @brief Gets the size of this Set.
		 * @returns The size.
		 */
		inline Size get_size() const { return m_size; }

		/**
		 * @brief Checks if this Set is empty.
		 * @returns True, if the Set is empty.
		 */
		inline Bool is_empty() const { return m_size == 0; }

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Reserves more space for the Set.
		 * @param capacity The new capacity.
		 */
		void reserve(Size const capacity)
		{
			// do nothing if smaller or same size
			if (capacity <= m_capacity)
			{
				return;
			}

			Node **newTable = m_allocator.construct_array<Node *>(capacity, nullptr);
			if (m_capacity > 0)
			{
				for (Size i = 0; i < m_capacity; ++i)
				{
					Node *node = mp_table[i];
					while (node)
					{
						Node *next = node->next;
						Size index = hash(node->key, capacity);
						node->next = newTable[index];
						newTable[index] = node;
						node = next;
					}
				}
				m_allocator.destruct_array(mp_table, m_capacity);
			}
			mp_table = newTable;
			m_capacity = capacity;
		}

		/**
		 * @brief Adds a copy of the given key to this Set.
		 * @param key The key to add.
		 * @returns True, if the key was added.
		 */
		Bool add(T const &key)
		{
			if (contains(key))
			{
				return false;
			}

			// rehash if necessary
			if (m_size >= m_capacity * DEFAULT_LOAD_FACTOR)
			{
				rehash();
			}

			// insert into bucket
			Size index = hash(key);
			Node *node = m_allocator.construct<Node>(key);
			node->next = mp_table[index];
			mp_table[index] = node;

			// add to size
			++m_size;

			return true;
		}

		/**
		 * @brief Adds the given key to this Set.
		 * @param key The key to add.
		 * @returns True, if the key was added.
		 */
		Bool add(T &&key)
		{
			if (contains(key))
			{
				return false;
			}

			// rehash if necessary
			if (m_size >= m_capacity * DEFAULT_LOAD_FACTOR)
			{
				rehash();
			}

			// insert into bucket
			Size index = hash(key);
			Node *node = m_allocator.construct<Node>(std::move(key));
			node->next = mp_table[index];
			mp_table[index] = node;

			// add to size
			++m_size;
			return true;
		}

		/**
		 * @brief Removes the given key from this Set.
		 * @param key The key to remove.
		 * @returns True, if the key was found and removed.
		 */
		Bool remove(T const &key)
		{
			if (m_size == 0)
			{
				return false;
			}

			Size index = hash(key);
			Node *node = mp_table[index];
			Node *prev = nullptr;
			while (node)
			{
				if (node->key == key)
				{
					if (prev)
					{
						prev->next = node->next;
					}
					else
					{
						mp_table[index] = node->next;
					}
					m_allocator.destruct(node);
					--m_size;
					return true;
				}
				prev = node;
				node = node->next;
			}

			return false;
		}

		/**
		 * @brief Finds the first occurrence of the given T.
		 * @param key The T to find.
		 * @returns An Iterator to the key-value pair with the given T.
		 */
		Iterator find(T const &key)
		{
			if (m_size == 0)
			{
				return end();
			}

			Size index = hash(key);
			Node *node = mp_table[index];
			while (node)
			{
				if (node->key == key)
				{
					return Iterator(mp_table, m_capacity, index, node);
				}
				node = node->next;
			}
			return end();
		}

		/**
		 * @brief Finds the first occurrence of the given T.
		 * @param key The T to find.
		 * @returns A ConstIterator to the key-value pair with the given T.
		 */
		ConstIterator find(T const &key) const
		{
			if (m_capacity == 0)
			{
				return end();
			}

			Size index = hash(key);
			Node const *node = mp_table[index];
			while (node)
			{
				if (node->key == key)
				{
					return ConstIterator(mp_table, m_capacity, index, node);
				}
				node = node->next;
			}
			return end();
		}

		/**
		 * @brief Checks if the given key exists in this Set.
		 * @param key The key to check.
		 * @returns True, if the key exists.
		 */
		Bool contains(T const &key) const { return find(key) != end(); }

		/**
		 * @brief Clears all keys from this Set.
		 */
		void clear()
		{
			if (mp_table)
			{
				for (Size i = 0; i < m_capacity; ++i)
				{
					Node *node = mp_table[i];
					while (node)
					{
						Node *temp = node;
						node = node->next;
						m_allocator.destruct(temp);
					}
					mp_table[i] = nullptr;
				}
			}
			m_size = 0;
		}

	private:
		Size hash(T const &key, Size const capacity) const
		{
			return std::hash<T>{}(key) % capacity;
		}

		Size hash(T const &key) const
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
		Node **mp_table;
		Allocator m_allocator;

#pragma endregion
	};
}
