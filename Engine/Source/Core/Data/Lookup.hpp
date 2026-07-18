#pragma once

#include "Map.hpp"
#include "Tuple.hpp"
#include "Vector.hpp"
#include "String.hpp"

/**
 * @file Lookup.h
 * @brief Header file for the Lookup class.
 * @author Mitchell Talyat
 */

namespace Minty
{
	/**
	 * @brief A Lookup data structure that maps String or Key to Value.
	 * @tparam Key The type of the key.
	 * @tparam Value The type of the value.
	 * @tparam Allocator The type of the memory allocator to use.
	 */
	template<typename Key, typename Value, typename Allocator = DefaultAllocator>
	class Lookup
	{
#pragma region Iterators

	public:
		using Iterator = typename Vector<Tuple<String, Key, Value>>::Iterator;
		using ConstIterator = typename Vector<Tuple<String, Key, Value>>::ConstIterator;

		inline Iterator begin() { return m_values.begin(); }
		inline Iterator end() { return m_values.end(); }
		inline ConstIterator begin() const { return m_values.begin(); }
		inline ConstIterator end() const { return m_values.end(); }

#pragma endregion

#pragma region Constructors

	public:
		/**
		 * @brief Creates an empty Lookup.
		 */
		Lookup()
			: m_values()
			, m_strings()
			, m_keys()
		{
		}

		/**
		 * @brief Creates a Lookup with the given capacity.
		 * @param capacity The initial capacity.
		 */
		Lookup(Size const capacity)
			: m_values()
			, m_strings()
			, m_keys()
		{
			reserve(capacity);
		}

		/**
		 * @brief Creates a Lookup from an initializer list of key-value pairs.
		 * @param list The initializer list of key-value pairs.
		 */
		Lookup(std::initializer_list<Tuple<String, Key, Value>> const& list)
			: m_values()
			, m_strings()
			, m_keys()
		{
			reserve(list.size() * 2);
			for (Tuple<String, Key, Value> const& pair : list)
			{
				add(pair.get_first(), pair.get_second());
			}
		}

		~Lookup()
		{
			clear();
		}

#pragma endregion

#pragma region Operators

	public:
		constexpr Value& operator[](String const& key) { return at(key); }
		constexpr Value& operator[](Key const& key) { return at(key); }
		constexpr Value const& operator[](String const& key) const { return at(key); }
		constexpr Value const& operator[](Key const& key) const { return at(key); }

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the capacity of this Lookup.
		 * @return The capacity.
		 */
		inline Size get_capacity() const { return m_values.get_capacity(); }

		/**
		 * @brief Gets the size of this Lookup.
		 * @return The size.
		 */
		inline Size get_size() const { return m_values.get_size(); }

		/**
		 * @brief Gets the String associated with the given Key.
		 * @param key The Key.
		 * @return The String.
		 */
		String const& get_string(Key const& key) const
		{
			MINTY_ASSERT(m_keys.contains(key), ErrorCodeEnum::Argument_KeyNotFound);
			return m_values[m_keys.at(key)].get_first();
		}

		/**
		 * @brief Gets the Key associated with the given String.
		 * @param string The String.
		 * @return The Key.
		 */
		Key const& get_key(String const& string) const
		{
			MINTY_ASSERT(m_strings.contains(string), ErrorCodeEnum::Argument_KeyNotFound);
			return m_values[m_strings.at(string)].get_second();
		}

		/**
		 * @brief Checks if this Lookup is empty.
		 * @return True, if the Lookup is empty.
		 */
		inline Bool is_empty() const { return m_values.is_empty(); }

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Reserves capacity for the given number of elements.
		 * @param capacity The capacity to reserve.
		 */
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

		/**
		 * @brief Adds a key-value pair to this Lookup.
		 * @param key The key to add.
		 * @param value The value to add.
		 */
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

		/**
		 * @brief Adds a key-value pair to this Lookup.
		 * @param key The key to add.
		 * @param value The value to add.
		 */
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

		/**
		 * @brief Removes the key-value pair with the given key.
		 * @param key The key of the pair to remove.
		 * @return True, if the key was found and the pair was removed.
		 */
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

		/**
		 * @brief Removes the key-value pair with the given key.
		 * @param key The key of the pair to remove.
		 * @return True, if the key was found and the pair was removed.
		 */
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

		/**
		 * @brief Gets the Value with the given Key.
		 * @param key The Key of the Value to get.
		 * @returns The Value with the given Key.
		 */
		Value& at(String const& key)
		{
			return m_values.at(m_strings.at(key)).get_third();
		}

		/**
		 * @brief Gets the Value with the given Key.
		 * @param key The Key of the Value to get.
		 * @returns The Value with the given Key.
		 */
		Value const& at(String const& key) const
		{
			return m_values.at(m_strings.at(key)).get_third();
		}

		/**
		 * @brief Gets the Value with the given Key.
		 * @param key The Key of the Value to get.
		 * @returns The Value with the given Key.
		 */
		Value& at(Key const& key)
		{
			return m_values.at(m_keys.at(key)).get_third();
		}

		/**
		 * @brief Gets the Value with the given Key.
		 * @param key The Key of the Value to get.
		 * @returns The Value with the given Key.
		 */
		Value const& at(Key const& key) const
		{
			return m_values.at(m_keys.at(key)).get_third();
		}

		/**
		 * @brief Finds the first occurrence of the given Key.
		 * @param key The Key to find.
		 * @returns An Iterator to the key-value pair with the given Key.
		 */
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
		
		/**
		 * @brief Finds the first occurrence of the given Key.
		 * @param key The Key to find.
		 * @returns An Iterator to the key-value pair with the given Key.
		 */
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

		/**
		 * @brief Finds the first occurrence of the given Key.
		 * @param key The Key to find.
		 * @returns A ConstIterator to the key-value pair with the given Key.
		 */
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

		/**
		 * @brief Finds the first occurrence of the given Key.
		 * @param key The Key to find.
		 * @returns A ConstIterator to the key-value pair with the given Key.
		 */
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

		/**
		 * @brief Checks if this Lookup contains the given Key.
		 * @param key The Key to check.
		 * @returns True, if the Key is found.
		 */
		Bool contains(String const& key) const { return find(key) != end(); }

		/**
		 * @brief Checks if this Lookup contains the given Key.
		 * @param key The Key to check.
		 * @returns True, if the Key is found.
		 */
		Bool contains(Key const& key) const { return find(key) != end(); }

		/**
		 * @brief Clears this Lookup, removing all key-value pairs.
		 */
		void clear()
		{
			m_values.clear();
			m_strings.clear();
			m_keys.clear();
		}

#pragma endregion

#pragma region Variables

	private:
		Vector<Tuple<String, Key, Value>, Allocator> m_values;
		Map<String, Size, Allocator> m_strings;
		Map<Key, Size, Allocator> m_keys;

#pragma endregion
	};
}
