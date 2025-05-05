#pragma once
#include "Minty/Core/Base.h"
#include "Minty/Data/ConstantContainer.h"
#include "Minty/Data/Map.h"
#include "Minty/Data/Object.h"
#include "Minty/Data/String.h"
#include "Minty/Data/Variable.h"
#include "Minty/Data/Vector.h"

namespace Minty
{
	/// <summary>
	/// Holds a collection of named Objects, each of which has an ordered list of named Variables.
	/// </summary>
	class Cargo
	{
#pragma region Variables

	private:
		Allocator m_allocator;
		Map<String, Object> m_objects;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates an empty Cargo.
		/// </summary>
		/// <param name="allocator">The Allocator to use.</param>
		Cargo(Allocator const allocator = Allocator::Default)
			: m_allocator(allocator)
			, m_objects()
		{
		}

		/// <summary>
		/// Creates a Cargo with the given capacity.
		/// </summary>
		/// <param name="capacity">The capacity of the number of Objects.</param>
		/// <param name="allocator">The Allocator to use.</param>
		Cargo(Size const capacity, Allocator const allocator = Allocator::Default)
			: m_allocator(allocator)
			, m_objects(capacity)
		{
		}

		/// <summary>
		/// Creates a Cargo with the given list of Objects.
		/// </summary>
		/// <param name="list">The list of Objects.</param>
		/// <param name="allocator">The Allocator to use.</param>
		Cargo(std::initializer_list<Pair<String, Vector<Pair<String, Variable>>>> const& list, Allocator const allocator = Allocator::Default)
			: m_allocator(allocator)
			, m_objects(list.size() * 2)
		{
			for (auto const& [name, variables] : list)
			{
				m_objects.add(name, Object(variables));
			}
		}

		Cargo(Cargo const& other)
			: m_allocator(other.m_allocator)
			, m_objects(other.m_objects)
		{
		}

		Cargo(Cargo&& other) noexcept
			: m_allocator(std::move(other.m_allocator))
			, m_objects(std::move(other.m_objects))
		{
		}

#pragma endregion

#pragma region Operators

	public:
		Cargo& operator=(Cargo const& other)
		{
			if (this != &other)
			{
				m_allocator = other.m_allocator;
				m_objects = other.m_objects;
			}
			return *this;
		}

		Cargo& operator=(Cargo&& other) noexcept
		{
			if (this != &other)
			{
				m_allocator = std::move(other.m_allocator);
				m_objects = std::move(other.m_objects);
			}
			return *this;
		}

#pragma endregion

#pragma region Iterators

	public:
		Map<String, Object>::Iterator begin()
		{
			return m_objects.begin();
		}

		Map<String, Object>::ConstIterator begin() const
		{
			return m_objects.begin();
		}

		Map<String, Object>::Iterator end()
		{
			return m_objects.end();
		}

		Map<String, Object>::ConstIterator end() const
		{
			return m_objects.end();
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Checks if this Cargo is empty.
		/// </summary>
		/// <returns>True if there are no Objects.</returns>
		Bool is_empty() const { return m_objects.is_empty(); }

		/// <summary>
		/// Gets the number of Objects in this Cargo.
		/// </summary>
		/// <returns>The number of Objects.</returns>
		Size get_size() const { return m_objects.get_size(); }

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Checks if this Cargo has an Object with the given name.
		/// </summary>
		/// <param name="name">The name of the Object.</param>
		/// <returns>True, if an Object with the given name exists.</returns>
		Bool contains(String const& name) const
		{
			return m_objects.contains(name);
		}

		/// <summary>
		/// Gets the Object with the given name.
		/// </summary>
		/// <param name="name">The name of the Object.</param>
		/// <returns>The Object.</returns>
		Object const& at(String const& name) const
		{
			MINTY_ASSERT(m_objects.contains(name), "Cargo has no object with the given name.");
			return m_objects.at(name);
		}

		/// <summary>
		/// Gets the Object with the given name.
		/// </summary>
		/// <param name="name">The name of the Object.</param>
		/// <returns>The Object.</returns>
		Object& at(String const& name)
		{
			MINTY_ASSERT(m_objects.contains(name), "Cargo has no object with the given name.");
			return m_objects.at(name);
		}

		/// <summary>
		/// Adds the Object with the given name.
		/// </summary>
		/// <param name="name">The name of the Object.</param>
		/// <param name="object">The Object.</param>
		void add(String const& name, Object const& object)
		{
			MINTY_ASSERT(!m_objects.contains(name), "Cargo already contains an object with the given name.");
			m_objects.add(name, object);
		}

		/// <summary>
		/// Sets the Object with the given name.
		/// </summary>
		/// <param name="name">The name of the Object.</param>
		/// <param name="object">The Object.</param>
		void set(String const& name, Object const& object)
		{
			m_objects[name] = object;
		}

		/// <summary>
		/// Removes the Object with the given name.
		/// </summary>
		/// <param name="name">The name of the Object.</param>
		/// <returns>True if an Object was removed.</returns>
		Bool remove(String const& name)
		{
			return m_objects.remove(name);
		}

		/// <summary>
		/// Finds the first occurrence of the given name.
		/// </summary>
		/// <param name="name">The name to find.</param>
		/// <returns>An iterator to the Object with the given name.</returns>
		Map<String, Object>::Iterator find(String const& name)
		{
			return m_objects.find(name);
		}

		/// <summary>
		/// Finds the first occurrence of the given name.
		/// </summary>
		/// <param name="name">The name to find.</param>
		/// <returns>An iterator to the Object with the given name.</returns>
		Map<String, Object>::ConstIterator find(String const& name) const
		{
			return m_objects.find(name);
		}

		/// <summary>
		/// Packs the data within this Cargo into a byte array.
		/// </summary>
		/// <returns>A ConstContainer with the byte array.</returns>
		ConstantContainer pack() const;

#pragma endregion
	};
}