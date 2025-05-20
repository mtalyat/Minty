#pragma once
#include "Minty/Core/Base.h"
#include "Minty/Core/Macro.h"
#include "Minty/Core/Types.h"

namespace Minty
{
	/// <summary>
	/// Holds a hash map of key-value pairs.
	/// </summary>
	/// <typeparam name="T">The type of the keys.</typeparam>
	/// <typeparam name="Value">The type of the values.</typeparam>
	template<typename T>
	class Set
	{
#pragma region Classes

	private:
		struct Node
		{
			T key;
			Node* next;

			Node(T const& key)
				: key(key)
				, next(nullptr)
			{
			}

			Node(T&& key)
				: key(std::move(key))
				, next(nullptr)
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
			T& operator*() const
			{
				MINTY_ASSERT(mp_current, "Iterator is invalid.");
				return mp_current->key;
			}

			T* operator->() const
			{
				MINTY_ASSERT(mp_current, "Iterator is invalid.");
				return &mp_current->key;
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
			friend class Set;

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
			T const& operator*() const
			{
				MINTY_ASSERT(mp_current, "ConstIterator is invalid.");
				return mp_current->key;
			}

			T const* operator->() const
			{
				MINTY_ASSERT(mp_current, "ConstIterator is invalid.");
				return &mp_current->key;
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
		/// Gets an Iterator to the beginning of the Set.
		/// </summary>
		/// <returns>An Iterator pointing to the first key-value pair.</returns>
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

		/// <summary>
		/// Gets an Iterator to the end of the Set.
		/// </summary>
		/// <returns>An Iterator pointing to the first key-value pair.</returns>
		Iterator end() { return Iterator(mp_table, m_capacity, m_capacity, nullptr); }

		/// <summary>
		/// Gets a ConstIterator to the beginning of the Set.
		/// </summary>
		/// <returns>A ConstIterator pointing to the first key-value pair.</returns>
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

		/// <summary>
		/// Gets a ConstIterator to the end of the Set.
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
		/// Creates an empty Set.
		/// </summary>
		/// <param name="allocator">The memory allocator to use.</param>
		Set(Allocator const allocator = Allocator::Default)
			: m_allocator(allocator)
			, m_capacity(0)
			, m_size(0)
			, mp_table(nullptr)
		{
		}

		/// <summary>
		/// Creates a Set with the given capacity.
		/// </summary>
		/// <param name="capacity">The starting capacity to use.</param>
		/// <param name="allocator">The memory allocator to use.</param>
		Set(Size const capacity, Allocator const allocator = Allocator::Default)
			: m_allocator(allocator)
			, m_capacity(capacity)
			, m_size(0)
			, mp_table(nullptr)
		{
			reserve(capacity);
		}

		/// <summary>
		/// Creates a Set with the given list of key-value pairs.
		/// </summary>
		/// <param name="list">A list of key-value pairs.</param>
		/// <param name="allocator">The memory allocator to use.</param>
		Set(std::initializer_list<T> const& list, Allocator const allocator = Allocator::Default)
			: m_allocator(allocator)
			, m_capacity(0)
			, m_size(0)
			, mp_table(nullptr)
		{
			reserve(list.size() * 2);
			for (T const& key : list)
			{
				add(key);
			}
		}

		Set(Set const& other)
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
					Node* newNode = construct<Node>(m_allocator, node->key);
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

		Set(Set&& other) noexcept
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

		~Set()
		{
			clear();
		}

#pragma endregion

#pragma region Operators

	public:
		Set& operator=(Set const& other)
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
						Node* newNode = construct<Node>(m_allocator, node->key);
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

		Set& operator=(Set&& other) noexcept
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

#pragma endregion

#pragma region Get Set

	public:
		Size get_capacity() const { return m_capacity; }

		Size get_size() const { return m_size; }

#pragma endregion

#pragma region Methods

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

	public:
		/// <summary>
		/// Reserves more space in this Set.
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
			if (m_capacity > 0)
			{
				for (Size i = 0; i < m_capacity; ++i)
				{
					Node* node = mp_table[i];
					while (node)
					{
						Node* next = node->next;
						Size index = hash(node->key, capacity);
						node->next = newTable[index];
						newTable[index] = node;
						node = next;
					}
				}
				destruct_array<Node*>(mp_table, m_capacity, m_allocator);
			}
			mp_table = newTable;
			m_capacity = capacity;
		}

		/// <summary>
		/// Adds a copy of the given key to this Set.
		/// </summary>
		/// <param name="key">The key to add.</param>
		/// <returns>True, if the key was added.</returns>
		Bool add(T const& key)
		{
			if (contains(key))
			{
				return false;
			}

			// rehash if necessary
			if (m_size >= m_capacity * DEFAULT_COLLECTION_REHASH_THRESHOLD)
			{
				rehash();
			}

			// insert into bucket
			Size index = hash(key);
			Node* node = construct<Node>(m_allocator, key);
			node->next = mp_table[index];
			mp_table[index] = node;

			// add to size
			++m_size;

			return true;
		}

		/// <summary>
		/// Adds a copy of the given key to this Set.
		/// </summary>
		/// <param name="key">The key to add.</param>
		/// <returns>True, if the key was added.</returns>
		Bool add(T&& key)
		{
			if (contains(key))
			{
				return false;
			}

			// rehash if necessary
			if (m_size >= m_capacity * DEFAULT_COLLECTION_REHASH_THRESHOLD)
			{
				rehash();
			}

			// insert into bucket
			Size index = hash(key);
			Node* node = construct<Node>(m_allocator, std::move(key));
			node->next = mp_table[index];
			mp_table[index] = node;

			// add to size
			++m_size;
			return true;
		}

		/// <summary>
		/// Adds the range of elements to this Set.
		/// </summary>
		/// <typeparam name="IteratorType">The type of iterator.</typeparam>
		/// <param name="begin">The beginning of the range.</param>
		/// <param name="end">The end of the range.</param>
		/// <returns></returns>
		template<typename IteratorType>
		typename std::enable_if<!std::is_integral<IteratorType>::value, void>::type
			add(IteratorType const& begin, IteratorType const& end)
		{
			IteratorType it = begin;
			while (it != end)
			{
				add(*it);
				++it;
			}
		}

		/// <summary>
		/// Removes the key.
		/// </summary>
		/// <param name="key">The key to remove.</param>
		/// <returns>True, if the key was found and removed.</returns>
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
		/// Checks if this Set is empty.
		/// </summary>
		/// <returns>True, if the size is zero.</returns>
		Bool is_empty() const { return m_size == 0; }

		/// <summary>
		/// Finds the first occurrence of the given T.
		/// </summary>
		/// <param name="key">The T to find.</param>
		/// <returns>An Iterator to the key-value pair with the given T.</returns>
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
					return Iterator(mp_table, m_capacity, index, node);
				}
				node = node->next;
			}
			return end();
		}

		/// <summary>
		/// Finds the first occurrence of the given T.
		/// </summary>
		/// <param name="key">The T to find.</param>
		/// <returns>A ConstIterator to the key-value pair with the given T.</returns>
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
					return ConstIterator(mp_table, m_capacity, index, node);
				}
				node = node->next;
			}
			return end();
		}

		/// <summary>
		/// Checks if this Set contains the given T.
		/// </summary>
		/// <param name="key">The T to check.</param>
		/// <returns>True, if the T is found.</returns>
		Bool contains(T const& key) const { return find(key) != end(); }

		/// <summary>
		/// Removes all key-value pairs from this Set.
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