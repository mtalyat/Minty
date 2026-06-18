#pragma once

/**
 * @file Map.h
 * @brief Header file for the Map class.
 * @author Mitchell Talyat
 */

#include "Core/Memory/DefaultAllocator.h"
#include "Core/Constant/Default.h"
#include "Core/Debug/Debug.h"
#include "Platform/Type/Primitive.h"
#include "Tuple.h"

namespace Minty
{
	// TODO: make override for String, that has duplicate functions for StringView
	// This is to avoid allocating memory for a String every time we want to use a StringView as a key, which is common when using Strings as keys

	/**
	 * @brief A hash map implementation using separate chaining for collision resolution.
	 * @tparam Key The type of keys stored in the map.
	 * @tparam Value The type of values stored in the map.
	 * @tparam Allocator The allocator type to use for memory management.
	 */
	template <typename Key, typename Value, typename Allocator = DefaultAllocator>
	class Map
	{
#pragma region Types

	private:
		struct Node
		{
			Tuple<Key, Value> data;
			Node *next;

			Node(Key const &key, Value const &value)
				: data(key, value), next(nullptr)
			{
			}

			Node(Key const &key, Value &&value)
				: data(key, std::move(value)), next(nullptr)
			{
			}

			Key const &get_key() const
			{
				return data.get_first();
			}

			Value &get_value()
			{
				return data.get_second();
			}

			Value const &get_value() const
			{
				return data.get_second();
			}
		};

#pragma endregion

#pragma region Iterators

	public:
		class Iterator
		{
			friend class Map;

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
			Tuple<Key, Value> &operator*() const
			{
				MINTY_ASSERT(mp_current, ErrorCodeEnum::Object_InvalidState);
				return mp_current->data;
			}

			Tuple<Key, Value> *operator->() const
			{
				MINTY_ASSERT(mp_current, ErrorCodeEnum::Object_InvalidState);
				return &mp_current->data;
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
			friend class Map;

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
			Tuple<Key, Value> const &operator*() const
			{
				MINTY_ASSERT(mp_current, ErrorCodeEnum::Object_InvalidState);
				return mp_current->data;
			}

			Tuple<Key, Value> const *operator->() const
			{
				MINTY_ASSERT(mp_current, ErrorCodeEnum::Object_InvalidState);
				return &mp_current->data;
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
		 * @brief Creates an empty Map.
		 */
		Map()
			: m_capacity(0), m_size(0), mp_table(nullptr), m_allocator()
		{
		}

		/**
		 * @brief Creates a Map with the given capacity.
		 * @param capacity The starting capacity to use.
		 */
		Map(Size const capacity)
			: m_capacity(0), m_size(0), mp_table(nullptr), m_allocator()
		{
			reserve(capacity);
		}

		/**
		 * @brief Creates a Map from an initializer list of key-value pairs.
		 * @param list The initializer list of key-value pairs.
		 */
		Map(std::initializer_list<Tuple<Key, Value>> const &list)
			: m_capacity(0), m_size(0), mp_table(nullptr), m_allocator()
		{
			reserve(list.size() * 2);
			for (Tuple<Key, Value> const &pair : list)
			{
				add(pair.get_first(), pair.get_second());
			}
		}

		/**
		 * @brief Copies the given Map.
		 * @param other The Map to copy.
		 */
		Map(Map const &other)
			: m_capacity(other.m_capacity), m_size(other.m_size), mp_table(nullptr), m_allocator()
		{
			if(m_capacity == 0)
			{
				return;
			}
			
			mp_table = m_allocator.construct_array<Node *>(m_capacity);

			for (Size i = 0; i < m_capacity; ++i)
			{
				Node *node = other.mp_table[i];
				Node *prev = nullptr;
				while (node)
				{
					Node *const newNode = m_allocator.construct<Node>(node->get_key(), node->get_value());
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
		 * @brief Moves the given Map.
		 * @param other The Map to move.
		 */
		Map(Map &&other) noexcept
			: m_capacity(other.m_capacity), m_size(other.m_size), mp_table(other.mp_table), m_allocator(std::move(other.m_allocator))
		{
			other.m_capacity = 0;
			other.m_size = 0;
			other.mp_table = nullptr;
		}

		~Map()
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
		Map &operator=(Map const &other)
		{
			if (this != &other)
			{
				clear();
				m_allocator.destruct_array(mp_table, m_capacity);
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
							Node *const newNode = m_allocator.construct<Node>(node->get_key(), node->get_value());
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

		Map &operator=(Map &&other) noexcept
		{
			if (this != &other)
			{
				clear();
				m_allocator.destruct_array(mp_table, m_capacity);
				m_capacity = other.m_capacity;
				m_size = other.m_size;
				mp_table = other.mp_table;
				other.m_capacity = 0;
				other.m_size = 0;
				other.mp_table = nullptr;
			}
			return *this;
		}

		constexpr Value &operator[](Key const &key)
		{
			if (!contains(key))
			{
				add(key, Value());
			}
			return at(key);
		}

		constexpr Value const &operator[](Key const &key) const
		{
			return at(key);
		}

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the capacity of this Map.
		 * @returns The capacity.
		 */
		inline Size get_capacity() const { return m_capacity; }

		/**
		 * @brief Gets the size of this Map.
		 * @returns The size.
		 */
		inline Size get_size() const { return m_size; }

		/**
		 * @brief Checks if the Map is empty.
		 * @returns True if the Map is empty, false otherwise.
		 */
		Bool is_empty() const { return m_size == 0; }

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Hashes the given key to an index in the table.
		 * @param key The key to hash.
		 */
		void reserve(Size const capacity)
		{
			// do nothing if smaller or same size
			if (capacity <= m_capacity)
			{
				return;
			}

			Node **newTable = m_allocator.construct_array<Node *>(capacity);

			if (m_capacity > 0)
			{
				for (Size i = 0; i < m_capacity; ++i)
				{
					Node *node = mp_table[i];
					while (node)
					{
						Node *next = node->next;
						Size index = hash(node->get_key(), capacity);
						node->next = newTable[index];
						newTable[index] = node;
						node = next;
					}
				}
				m_allocator.destruct_array(mp_table, m_capacity);
			}
			m_capacity = capacity;
			mp_table = newTable;
		}

		/**
		 * @brief Adds a key-value pair to the Map.
		 * @param key The key of the pair.
		 * @param value The value of the pair.
		 */
		void add(Key const &key, Value const &value)
		{
			MINTY_ASSERT(!contains(key), ErrorCodeEnum::Argument_KeyAlreadyExists);

			// rehash if necessary
			if (m_size >= m_capacity * DEFAULT_LOAD_FACTOR)
			{
				rehash();
			}

			// insert into bucket
			Size index = hash(key);
			Node *const node = m_allocator.construct<Node>(key, std::move(value));
			node->next = mp_table[index];
			mp_table[index] = node;

			// add to size
			++m_size;
		}

		/**
		 * @brief Adds a key-value pair to the Map.
		 * @param key The key of the pair.
		 * @param value The value of the pair.
		 */
		void add(Key const &key, Value &&value)
		{
			MINTY_ASSERT(!contains(key), ErrorCodeEnum::Argument_KeyAlreadyExists);

			// rehash if necessary
			if (m_size >= m_capacity * DEFAULT_LOAD_FACTOR)
			{
				rehash();
			}

			// insert into bucket
			Size index = hash(key);
			Node *const node = m_allocator.construct<Node>(std::move(key), std::move(value));
			node->next = mp_table[index];
			mp_table[index] = node;

			// add to size
			++m_size;
		}

		/**
		 * @brief Adds a key-value pair to the Map.
		 * @param key The key of the pair.
		 * @param value The value of the pair.
		 */
		Bool remove(Key const &key)
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
				if (node->get_key() == key)
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
		 * @brief Gets the Value with the given Key.
		 * @param key The Key of the Value to get.
		 */
		Value &at(Key const &key)
		{
			MINTY_ASSERT(m_size > 0, ErrorCodeEnum::Object_EmptyContainer);

			Size index = hash(key);
			Node *node = mp_table[index];

			while (node)
			{
				if (node->get_key() == key)
				{
					return node->get_value();
				}
				node = node->next;
			}

			MINTY_ABORT(ErrorCodeEnum::Argument_KeyNotFound);
		}

		/**
		 * @brief Gets the Value with the given Key.
		 * @param key The Key of the Value to get.
		 */
		Value const &at(Key const &key) const
		{
			MINTY_ASSERT(m_size > 0, ErrorCodeEnum::Object_EmptyContainer);

			Size index = hash(key);
			Node const *node = mp_table[index];

			while (node)
			{
				if (node->get_key() == key)
				{
					return node->get_value();
				}
				node = node->next;
			}

			MINTY_ABORT(ErrorCodeEnum::Argument_KeyNotFound);
		}

		/**
		 * @brief Finds the first occurrence of the given Key.
		 * @param key The Key to find.
		 */
		Iterator find(Key const &key)
		{
			if (m_size == 0)
			{
				return end();
			}

			Size index = hash(key);
			Node *node = mp_table[index];
			while (node)
			{
				if (node->get_key() == key)
				{
					return Iterator(mp_table, m_capacity, index, node);
				}
				node = node->next;
			}
			return end();
		}

		/**
		 * @brief Finds the first occurrence of the given Key.
		 * @param key The Key to find.
		 */
		ConstIterator find(Key const &key) const
		{
			if (m_size == 0)
			{
				return end();
			}

			Size index = hash(key);
			Node const *node = mp_table[index];
			while (node)
			{
				if (node->get_key() == key)
				{
					return ConstIterator(mp_table, m_capacity, index, node);
				}
				node = node->next;
			}
			return end();
		}

		/**
		 * @brief Checks if the Map contains the given Key.
		 * @param key The Key to check for.
		 */
		inline Bool contains(Key const &key) const { return find(key) != end(); }

		/**
		 * @brief Clears all key-value pairs from the Map.
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
		Size hash(Key const &key, Size const capacity) const
		{
			return std::hash<Key>{}(key) % capacity;
		}

		Size hash(Key const &key) const
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
