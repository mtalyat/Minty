#pragma once
#include "Minty/Core/Base.h"
#include "Minty/Core/Constant.h"
#include "Minty/Core/Types.h"
#include "Minty/Data/Map.h"
#include "Minty/Data/String.h"
#include "Minty/Data/Tuple.h"
#include "Minty/Data/Vector.h"
#include "Minty/Debug/Debug.h"

namespace Minty
{
	/// <summary>
	/// Holds a hash Lookup of string/key-value pairs.
	/// </summary>
	/// <typeparam name="Key">The type of the keys.</typeparam>
	/// <typeparam name="Value">The type of the values.</typeparam>
	template<typename Key, typename Value>
	class Lookup
	{
#pragma region Iterators

	public:
		using Iterator = typename Vector<Tuple<String, Key, Value>>::Iterator;
		using ConstIterator = typename Vector<Tuple<String, Key, Value>>::ConstIterator;

		/// <summary>
		/// Gets an Iterator to the beginning of the Lookup.
		/// </summary>
		/// <returns>An Iterator pointing to the first key-value pair.</returns>
		Iterator begin() { return m_values.begin(); }

		/// <summary>
		/// Gets an Iterator to the end of the Lookup.
		/// </summary>
		/// <returns>An Iterator pointing to the first key-value pair.</returns>
		Iterator end() { return m_values.end(); }

		/// <summary>
		/// Gets a ConstIterator to the beginning of the Lookup.
		/// </summary>
		/// <returns>A ConstIterator pointing to the first key-value pair.</returns>
		ConstIterator begin() const { return m_values.begin(); }

		/// <summary>
		/// Gets a ConstIterator to the end of the Lookup.
		/// </summary>
		/// <returns>A ConstIterator pointing to the first key-value pair.</returns>
		ConstIterator end() const { return m_values.end(); }

#pragma endregion

#pragma region Variables

	private:
		Vector<Tuple<String, Key, Value>> m_values;
		Map<String, Size> m_strings;
		Map<Key, Size> m_keys;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates an empty Lookup.
		/// </summary>
		/// <param name="allocator">The memory allocator to use.</param>
		Lookup(Allocator const allocator = Allocator::Default)
			: m_values(allocator)
			, m_strings(allocator)
			, m_keys(allocator)
		{
		}

		/// <summary>
		/// Creates a Lookup with the given capacity.
		/// </summary>
		/// <param name="capacity">The starting capacity to use.</param>
		/// <param name="allocator">The memory allocator to use.</param>
		Lookup(Size const capacity, Allocator const allocator = Allocator::Default)
			: m_values(allocator)
			, m_strings(allocator)
			, m_keys(allocator)
		{
			reserve(capacity);
		}

		/// <summary>
		/// Creates a Lookup with the given list of key-value pairs.
		/// </summary>
		/// <param name="list">A list of key-value pairs.</param>
		/// <param name="allocator">The memory allocator to use.</param>
		Lookup(std::initializer_list<Tuple<String, Key, Value>> const& list, Allocator const allocator = Allocator::Default)
			: m_values(allocator)
			, m_strings(allocator)
			, m_keys(allocator)
		{
			reserve(list.size() * 2);
			for (Tuple<String, Key, Value> const& pair : list)
			{
				add(pair.get_first(), pair.get_second());
			}
		}

		Lookup(Lookup const& other)
			: m_values(other.m_values)
			, m_strings(other.m_strings)
			, m_keys(other.m_keys)
		{
		}

		Lookup(Lookup&& other) noexcept
			: m_values(std::move(other.m_values))
			, m_strings(std::move(other.m_strings))
			, m_keys(std::move(other.m_keys))
		{
		}

		~Lookup()
		{
			clear();
		}

#pragma endregion

#pragma region Operators

	public:
		Lookup& operator=(Lookup const& other)
		{
			if (this != &other)
			{
				m_values = other.m_values;
				m_strings = other.m_strings;
				m_keys = other.m_keys;
			}
			return *this;
		}

		Lookup& operator=(Lookup&& other) noexcept
		{
			if (this != &other)
			{
				m_values = std::move(other.m_values);
				m_strings = std::move(other.m_strings);
				m_keys = std::move(other.m_keys);
			}
			return *this;
		}

		constexpr Value& operator[](String const& key)
		{
			return at(key);
		}

		constexpr Value& operator[](Key const& key)
		{
			return at(key);
		}

		constexpr Value const& operator[](String const& key) const
		{
			return at(key);
		}

		constexpr Value const& operator[](Key const& key) const
		{
			return at(key);
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the capacity of this Lookup.
		/// </summary>
		/// <returns>The maximum number of elements.</returns>
		Size get_capacity() const { return m_values.get_capacity(); }

		/// <summary>
		/// Gets the size of this Lookup.
		/// </summary>
		/// <returns>The number of elements.</returns>
		Size get_size() const { return m_values.get_size(); }

		/// <summary>
		/// Gets the String associated with the given Key.
		/// </summary>
		/// <param name="key">The Key.</param>
		/// <returns>The String.</returns>
		String const& get_string(Key const& key) const
		{
			MINTY_ASSERT(m_keys.contains(key), F("Key does not exist: {}", key));
			return m_values[m_keys.at(key)].get_first();
		}

		/// <summary>
		/// Gets the Key associated with the given String.
		/// </summary>
		/// <param name="string">The String.</param>
		/// <returns>The Key.</returns>
		Key const& get_key(String const& string) const
		{
			MINTY_ASSERT(m_strings.contains(string), F("String does not exist: {}", string));
			return m_values[m_strings.at(string)].get_second();
		}

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Reserves more space in this Lookup.
		/// </summary>
		/// <param name="capacity">The new capacity to use.</param>
		void reserve(Size const capacity)
		{
			// do nothing if capacity is less than current
			if (capacity <= m_values.get_capacity())
			{
				return;
			}

			// grow
			m_values.reserve(capacity);
			m_strings.reserve(capacity * 2);
			m_keys.reserve(capacity * 2);
		}

		/// <summary>
		/// Adds a key-value pair to this Lookup.
		/// </summary>
		/// <param name="key">The key to add.</param>
		/// <param name="value">The value to add.</param>
		void add(String const& string, Key const& key, Value const& value)
		{
			// get index
			Size index = m_values.get_size();

			// add to values
			m_values.add(Tuple<String, Key, Value>(string, key, value));

			// add to lookups
			m_strings.add(string, index);
			m_keys.add(key, index);
		}

		/// <summary>
		/// Adds a key-value pair to this Lookup.
		/// </summary>
		/// <param name="key">The key to add.</param>
		/// <param name="value">The value to add.</param>
		void add(String const& string, Key const& key, Value&& value)
		{
			// get index
			Size index = m_values.get_size();

			// add to values
			m_values.add(Tuple<String, Key, Value>(string, key, std::move(value)));

			// add to lookups
			m_strings.add(string, index);
			m_keys.add(key, index);
		}

		/// <summary>
		/// Removes the key-value pair with the given key.
		/// </summary>
		/// <param name="key">The key of the pair to remove.</param>
		/// <returns>True, if the key was found and the pair was removed.</returns>
		Bool remove(String const& key)
		{
			// find the index
			auto it = m_strings.find(key);
			if (it == m_strings.end())
			{
				return false;
			}

			// get the index
			Size index = it->get_second();

			// get the values
			Tuple<String, Key, Value> const& tuple = m_values[index];

			// remove data
			m_values.remove(index);
			m_strings.remove(key);
			m_keys.remove(tuple.get_second());

			return true;
		}

		/// <summary>
		/// Removes the key-value pair with the given key.
		/// </summary>
		/// <param name="key">The key of the pair to remove.</param>
		/// <returns>True, if the key was found and the pair was removed.</returns>
		Bool remove(Key const& key)
		{
			// find the index
			auto it = m_keys.find(key);
			if (it == m_keys.end())
			{
				return false;
			}

			// get the index
			Size index = it->get_second();

			// get the values
			Tuple<String, Key, Value> const& tuple = m_values[index];

			// remove data
			m_values.remove(index);
			m_strings.remove(tuple.get_first());
			m_keys.remove(key);

			return true;
		}

		/// <summary>
		/// Checks if this Lookup is empty.
		/// </summary>
		/// <returns>True, if the size is zero.</returns>
		Bool is_empty() const { return m_values.is_empty(); }

		/// <summary>
		/// Gets the Value with the given Key.
		/// </summary>
		/// <param name="key">The Key of the Value to get.</param>
		/// <returns>The Value with the given Key.</returns>
		Value& at(String const& key)
		{
			return m_values.at(m_strings.at(key)).get_third();
		}

		/// <summary>
		/// Gets the Value with the given Key.
		/// </summary>
		/// <param name="key">The Key of the Value to get.</param>
		/// <returns>The Value with the given Key.</returns>
		Value const& at(String const& key) const
		{
			return m_values.at(m_strings.at(key)).get_third();
		}

		/// <summary>
		/// Gets the Value with the given Key.
		/// </summary>
		/// <param name="key">The Key of the Value to get.</param>
		/// <returns>The Value with the given Key.</returns>
		Value& at(Key const& key)
		{
			return m_values.at(m_keys.at(key)).get_third();
		}

		/// <summary>
		/// Gets the Value with the given Key.
		/// </summary>
		/// <param name="key">The Key of the Value to get.</param>
		/// <returns>The Value with the given Key.</returns>
		Value const& at(Key const& key) const
		{
			return m_values.at(m_keys.at(key)).get_third();
		}

		/// <summary>
		/// Finds the first occurrence of the given Key.
		/// </summary>
		/// <param name="key">The Key to find.</param>
		/// <returns>An Iterator to the key-value pair with the given Key.</returns>
		Iterator find(String const& key)
		{
			// get index
			auto it = m_strings.find(key);
			if (it == m_strings.end())
			{
				return end();
			}

			Size index = it->get_second();

			// get iterator at index
			return begin() + index;
		}
		
		/// <summary>
		/// Finds the first occurrence of the given Key.
		/// </summary>
		/// <param name="key">The Key to find.</param>
		/// <returns>An Iterator to the key-value pair with the given Key.</returns>
		Iterator find(Key const& key)
		{
			// get index
			auto it = m_keys.find(key);
			if (it == m_keys.end())
			{
				return end();
			}

			Size index = it->get_second();

			// get iterator at index
			return begin() + index;
		}

		/// <summary>
		/// Finds the first occurrence of the given Key.
		/// </summary>
		/// <param name="key">The Key to find.</param>
		/// <returns>A ConstIterator to the key-value pair with the given Key.</returns>
		ConstIterator find(String const& key) const
		{
			// get index
			auto it = m_strings.find(key);
			if (it == m_strings.end())
			{
				return end();
			}

			Size index = it->get_second();

			// get iterator at index
			return begin() + index;
		}

		/// <summary>
		/// Finds the first occurrence of the given Key.
		/// </summary>
		/// <param name="key">The Key to find.</param>
		/// <returns>A ConstIterator to the key-value pair with the given Key.</returns>
		ConstIterator find(Key const& key) const
		{
			// get index
			auto it = m_keys.find(key);
			if (it == m_keys.end())
			{
				return end();
			}

			Size index = it->get_second();

			// get iterator at index
			return begin() + index;
		}

		/// <summary>
		/// Checks if this Lookup contains the given Key.
		/// </summary>
		/// <param name="key">The Key to check.</param>
		/// <returns>True, if the Key is found.</returns>
		Bool contains(String const& key) const { return find(key) != end(); }

		/// <summary>
		/// Checks if this Lookup contains the given Key.
		/// </summary>
		/// <param name="key">The Key to check.</param>
		/// <returns>True, if the Key is found.</returns>
		Bool contains(Key const& key) const { return find(key) != end(); }

		/// <summary>
		/// Removes all key-value pairs from this Lookup.
		/// </summary>
		void clear()
		{
			m_values.clear();
			m_strings.clear();
			m_keys.clear();
		}

#pragma endregion
	};
}