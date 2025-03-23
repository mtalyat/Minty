#pragma once
#include "Minty/Core/Base.h"
#include "Minty/Core/Constant.h"
#include "Minty/Core/Macro.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Pair.h"

namespace Minty
{
	/// <summary>
	/// Holds a hash map of key-value pairs.
	/// </summary>
	/// <typeparam name="Key">The type of the keys.</typeparam>
	/// <typeparam name="Value">The type of the values.</typeparam>
	template<typename Key, typename Value>
	class Map
	{
#pragma region Classes

	private:
		struct Node
		{
			Key key;
			Value value;
			Node* next;

			Node(Key const& key, Value const& value)
				: key(key)
				, value(value)
				, next(nullptr)
			{
			}

			Node(Key const& key, Value&& value)
				: key(key)
				, value(std::move(value))
				, next(nullptr)
			{
			}
		};

#pragma endregion

#pragma region Iterators

	public:
		class Iterator
		{
			friend class Map;

		private:
			Node** mp_table;
			Size m_capacity;
			Size m_bucketIndex;
			Node* mp_current;

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
			Iterator(Node** const table, Size const capacity, Size const bucketIndex, Node* const current)
				: mp_table(table)
				, m_capacity(capacity)
				, m_bucketIndex(bucketIndex)
				, mp_current(current)
			{
				// if no current given, advance to next
				if (bucketIndex < m_capacity && !mp_current)
				{
					advance();
				}
			}

		public:
			Pair<Key, Value>& operator*() const
			{
				MINTY_ASSERT(mp_current, "Iterator is invalid.");
				return reinterpret_cast<Pair<Key, Value>&>(*mp_current);
			}

			Pair<Key, Value>* operator->() const
			{
				MINTY_ASSERT(mp_current, "Iterator is invalid.");
				return reinterpret_cast<Pair<Key, Value>*>(mp_current);
			}

			Iterator& operator++()
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

			Bool operator==(Iterator const& other) const
			{
				return mp_table == other.mp_table && m_capacity == other.m_capacity && m_bucketIndex == other.m_bucketIndex && mp_current == other.mp_current;
			}

			Bool operator!=(Iterator const& other) const
			{
				return !(*this == other);
			}
		};

		class ConstIterator
		{
			friend class Map;

		private:
			Node* const* mp_table;
			Size m_capacity;
			Size m_bucketIndex;
			Node const* mp_current;

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
			ConstIterator(Node* const* const table, Size const capacity, Size const bucketIndex, Node const* const current)
				: mp_table(table)
				, m_capacity(capacity)
				, m_bucketIndex(bucketIndex)
				, mp_current(current)
			{
				// if no current given, advance to next
				if (bucketIndex < m_capacity && !mp_current)
				{
					advance();
				}
			}

		public:
			Pair<Key, Value> const& operator*() const
			{
				MINTY_ASSERT(mp_current, "ConstIterator is invalid.");
				return reinterpret_cast<Pair<Key, Value> const&>(*mp_current);
			}

			Pair<Key, Value> const* operator->() const
			{
				MINTY_ASSERT(mp_current, "ConstIterator is invalid.");
				return reinterpret_cast<Pair<Key, Value> const*>(mp_current);
			}

			ConstIterator& operator++()
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

			Bool operator==(ConstIterator const& other) const
			{
				return mp_table == other.mp_table && m_capacity == other.m_capacity && m_bucketIndex == other.m_bucketIndex && mp_current == other.mp_current;
			}

			Bool operator!=(ConstIterator const& other) const
			{
				return !(*this == other);
			}
		};

		/// <summary>
		/// Gets an Iterator to the beginning of the Map.
		/// </summary>
		/// <returns>An Iterator pointing to the first key-value pair.</returns>
		Iterator begin()
		{
			if (mp_table)
			{
				return Iterator(mp_table, m_capacity, 0, mp_table[0]);
			}
			else
			{
				return end();
			}
		}

		/// <summary>
		/// Gets an Iterator to the end of the Map.
		/// </summary>
		/// <returns>An Iterator pointing to the first key-value pair.</returns>
		Iterator end() { return Iterator(mp_table, m_capacity, m_capacity, nullptr); }

		/// <summary>
		/// Gets a ConstIterator to the beginning of the Map.
		/// </summary>
		/// <returns>A ConstIterator pointing to the first key-value pair.</returns>
		ConstIterator begin() const
		{
			if (mp_table)
			{
				return ConstIterator(mp_table, m_capacity, 0, mp_table[0]);
			}
			else
			{
				return end();
			}
		}

		/// <summary>
		/// Gets a ConstIterator to the end of the Map.
		/// </summary>
		/// <returns>A ConstIterator pointing to the first key-value pair.</returns>
		ConstIterator end() const { return ConstIterator(mp_table, m_capacity, m_capacity, nullptr); }

#pragma endregion

#pragma region Variables

	private:
		Allocator m_allocator;
		Size m_capacity;
		Size m_size;
		Node** mp_table;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates an empty Map.
		/// </summary>
		/// <param name="allocator">The memory allocator to use.</param>
		Map(Allocator const allocator = Allocator::Default)
			: m_allocator(allocator)
			, m_capacity(0)
			, m_size(0)
			, mp_table(nullptr)
		{
		}

		/// <summary>
		/// Creates a Map with the given capacity.
		/// </summary>
		/// <param name="capacity">The starting capacity to use.</param>
		/// <param name="allocator">The memory allocator to use.</param>
		Map(Size const capacity, Allocator const allocator = Allocator::Default)
			: m_allocator(allocator)
			, m_capacity(capacity)
			, m_size(0)
			, mp_table(nullptr)
		{
			reserve(capacity);
		}

		/// <summary>
		/// Creates a Map with the given list of key-value pairs.
		/// </summary>
		/// <param name="list">A list of key-value pairs.</param>
		/// <param name="allocator">The memory allocator to use.</param>
		Map(std::initializer_list<Pair<Key, Value>> const& list, Allocator const allocator = Allocator::Default)
			: m_allocator(allocator)
			, m_capacity(0)
			, m_size(0)
			, mp_table(nullptr)
		{
			reserve(list.size() * 2);
			for (Pair<Key, Value> const& pair : list)
			{
				add(pair.first, pair.second);
			}
		}

		Map(Map const& other)
			: m_allocator(other.m_allocator)
			, m_capacity(other.m_capacity)
			, m_size(other.m_size)
			, mp_table(construct_array<Node*>(m_capacity, m_allocator))
		{
			for (Size i = 0; i < m_capacity; ++i)
			{
				Node* node = other.mp_table[i];
				Node* prev = nullptr;
				while (node)
				{
					Node* newNode = construct<Node>(m_allocator, node->key, node->value);
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

		Map(Map&& other) noexcept
			: m_allocator(other.m_allocator)
			, m_capacity(other.m_capacity)
			, m_size(other.m_size)
			, mp_table(other.mp_table)
		{
			other.m_allocator = Allocator::Default;
			other.m_capacity = 0;
			other.m_size = 0;
			other.mp_table = nullptr;
		}

		~Map()
		{
			clear();
		}

#pragma endregion

#pragma region Operators

	public:
		Map& operator=(Map const& other)
		{
			if (this != &other)
			{
				clear();
				m_allocator = other.m_allocator;
				m_capacity = other.m_capacity;
				m_size = other.m_size;
				mp_table = construct_array<Node*>(m_capacity, m_allocator);
				for (Size i = 0; i < m_capacity; ++i)
				{
					Node* node = other.mp_table[i];
					Node* prev = nullptr;
					while (node)
					{
						Node* newNode = construct<Node>(m_allocator, node->key, node->value);
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
			return *this;
		}

		Map& operator=(Map&& other) noexcept
		{
			if (this != &other)
			{
				clear();
				m_allocator = other.m_allocator;
				m_capacity = other.m_capacity;
				m_size = other.m_size;
				mp_table = other.mp_table;
				other.m_allocator = Allocator::Default;
				other.m_capacity = 0;
				other.m_size = 0;
				other.mp_table = nullptr;
			}
			return *this;
		}

		constexpr Value& operator[](Key const& key)
		{
			if (!contains(key))
			{
				add(key, Value());
			}
			return at(key);
		}

		constexpr Value const& operator[](Key const& key) const
		{
			return at(key);
		}

#pragma endregion

#pragma region Get Set

	public:
		Size get_capacity() const { return m_capacity; }

		Size get_size() const { return m_size; }

#pragma endregion

#pragma region Methods

	private:
		Size hash(Key const& key) const
		{
			return std::hash<Key>{}(key) % m_capacity;
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

	public:
		/// <summary>
		/// Reserves more space in this Map.
		/// </summary>
		/// <param name="capacity">The new capacity to use.</param>
		void reserve(Size const capacity)
		{
			// do nothing if smaller or same size
			if (capacity <= m_capacity)
			{
				return;
			}

			Node** newTable = construct_array<Node*>(capacity, m_allocator);
			for (Size i = 0; i < m_capacity; ++i)
			{
				Node* node = mp_table[i];
				while (node)
				{
					Node* next = node->next;
					Size index = hash(node->key);
					node->next = newTable[index];
					newTable[index] = node;
					node = next;
				}
			}
			destruct_array<Node*>(mp_table, m_capacity, m_allocator);
			mp_table = newTable;
			m_capacity = capacity;
		}

		/// <summary>
		/// Adds a key-value pair to this Map.
		/// </summary>
		/// <param name="key">The key to add.</param>
		/// <param name="value">The value to add.</param>
		void add(Key const& key, Value const& value)
		{
			// rehash if necessary
			if (m_size >= m_capacity * DEFAULT_COLLECTION_REHASH_THRESHOLD)
			{
				rehash();
			}

			MINTY_ASSERT(!contains(key), "Key already exists in this Map.");

			// insert into bucket
			Size index = hash(key);
			Node* node = construct<Node>(m_allocator, key, value);
			node->next = mp_table[index];
			mp_table[index] = node;

			// add to size
			++m_size;
		}

		/// <summary>
		/// Adds a key-value pair to this Map.
		/// </summary>
		/// <param name="key">The key to add.</param>
		/// <param name="value">The value to add.</param>
		void add(Key const& key, Value&& value)
		{
			// rehash if necessary
			if (m_size >= m_capacity * DEFAULT_COLLECTION_REHASH_THRESHOLD)
			{
				rehash();
			}

			MINTY_ASSERT(!contains(key), "Key already exists in this Map.");

			// insert into bucket
			Size index = hash(key);
			Node* node = construct<Node>(m_allocator, key, std::move(value));
			node->next = mp_table[index];
			mp_table[index] = node;

			// add to size
			++m_size;
		}

		/// <summary>
		/// Removes the key-value pair with the given key.
		/// </summary>
		/// <param name="key">The key of the pair to remove.</param>
		/// <returns>True, if the key was found and the pair was removed.</returns>
		Bool remove(Key const& key)
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
					if (prev)
					{
						prev->next = node->next;
					}
					else
					{
						mp_table[index] = node->next;
					}
					destruct<Node>(node, m_allocator);
					--m_size;
					return true;
				}
				prev = node;
				node = node->next;
			}
			return false;
		}

		/// <summary>
		/// Checks if this Map is empty.
		/// </summary>
		/// <returns>True, if the size is zero.</returns>
		Bool is_empty() const { return m_size == 0; }

		/// <summary>
		/// Gets the Value with the given Key.
		/// </summary>
		/// <param name="key">The Key of the Value to get.</param>
		/// <returns>The Value with the given Key.</returns>
		Value& at(Key const& key)
		{
			MINTY_ASSERT(m_size > 0, "Map is empty.");

			Size index = hash(key);
			Node* node = mp_table[index];

			while (node)
			{
				if (node->key == key)
				{
					return node->value;
				}
				node = node->next;
			}

			MINTY_ASSERT(false, "Key does not exist in this Map.");

			return node->value;
		}

		/// <summary>
		/// Gets the Value with the given Key.
		/// </summary>
		/// <param name="key">The Key of the Value to get.</param>
		/// <returns>The Value with the given Key.</returns>
		Value const& at(Key const& key) const
		{
			MINTY_ASSERT(m_size > 0, "Map is empty.");

			Size index = hash(key);
			Node const* node = mp_table[index];

			while (node)
			{
				if (node->key == key)
				{
					return node->value;
				}
				node = node->next;
			}

			MINTY_ASSERT(false, "Key does not exist in this Map.");

			return node->value;
		}

		/// <summary>
		/// Finds the first occurrence of the given Key.
		/// </summary>
		/// <param name="key">The Key to find.</param>
		/// <returns>An Iterator to the key-value pair with the given Key.</returns>
		Iterator find(Key const& key)
		{
			if (m_capacity == 0)
			{
				return end();
			}

			Size index = hash(key);
			Node* node = mp_table[index];
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

		/// <summary>
		/// Finds the first occurrence of the given Key.
		/// </summary>
		/// <param name="key">The Key to find.</param>
		/// <returns>A ConstIterator to the key-value pair with the given Key.</returns>
		ConstIterator find(Key const& key) const
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
					return ConstIterator(mp_table, m_capacity, index, node);
				}
				node = node->next;
			}
			return end();
		}

		/// <summary>
		/// Checks if this Map contains the given Key.
		/// </summary>
		/// <param name="key">The Key to check.</param>
		/// <returns>True, if the Key is found.</returns>
		Bool contains(Key const& key) const { return find(key) != end(); }

		/// <summary>
		/// Removes all key-value pairs from this Map.
		/// </summary>
		void clear()
		{
			if (mp_table)
			{
				for (Size i = 0; i < m_capacity; ++i)
				{
					Node* node = mp_table[i];
					while (node)
					{
						Node* temp = node;
						node = node->next;
						destruct<Node>(temp, m_allocator);
					}
					mp_table[i] = nullptr;
				}
			}
			m_size = 0;
		}

#pragma endregion
	};
}