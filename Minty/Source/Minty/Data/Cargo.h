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
	/// Holds a collection of ordered, named Objects, each of which has an ordered list of named Variables.
	/// </summary>
	class Cargo
	{
#pragma region Variables

	private:
		Allocator m_allocator;
		Vector<Tuple<String, Object>> m_objects;

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
		Cargo(std::initializer_list<Tuple<String, Vector<Tuple<String, Variable>>>> const& list, Allocator const allocator = Allocator::Default)
			: m_allocator(allocator)
			, m_objects(list.size() * 2)
		{
			for (auto const& [name, variables] : list)
			{
				m_objects.add({ name, Object(variables) });
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
		Vector<Tuple<String, Object>>::Iterator begin()
		{
			return m_objects.begin();
		}

		Vector<Tuple<String, Object>>::ConstIterator begin() const
		{
			return m_objects.begin();
		}

		Vector<Tuple<String, Object>>::Iterator end()
		{
			return m_objects.end();
		}

		Vector<Tuple<String, Object>>::ConstIterator end() const
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
			for (auto const& [objectName, object] : m_objects)
			{
				if (name == objectName)
				{
					return true;
				}
			}
			return false;
		}

		/// <summary>
		/// Gets the Object with the given name.
		/// </summary>
		/// <param name="name">The name of the Object.</param>
		/// <returns>The Object.</returns>
		Object& at(String const& name)
		{
			for (auto& [objectName, object] : m_objects)
			{
				if (name == objectName)
				{
					return object;
				}
			}
			MINTY_ASSERT(false, "Cargo has no object with the given name.");
			throw new std::runtime_error("Cargo has no object with the given name.");
		}

		/// <summary>
		/// Gets the Object with the given name.
		/// </summary>
		/// <param name="name">The name of the Object.</param>
		/// <returns>The Object.</returns>
		Object const& at(String const& name) const
		{
			for (auto const& [objectName, object] : m_objects)
			{
				if (name == objectName)
				{
					return object;
				}
			}
			MINTY_ASSERT(false, "Cargo has no object with the given name.");
			throw new std::runtime_error("Cargo has no object with the given name.");
		}

		/// <summary>
		/// Adds the Object with the given name.
		/// </summary>
		/// <param name="name">The name of the Object.</param>
		/// <param name="object">The Object.</param>
		void add(String const& name, Object const& object)
		{
			MINTY_ASSERT(!contains(name), "Cargo already contains an object with the given name.");
			m_objects.add({ name, object });
		}

		/// <summary>
		/// Sets the Object with the given name.
		/// </summary>
		/// <param name="name">The name of the Object.</param>
		/// <param name="object">The Object.</param>
		void set(String const& name, Object const& object)
		{
			// replace if found
			for (auto& [objectName, obj] : m_objects)
			{
				if (objectName == name)
				{
					obj = object;
					return;
				}
			}
			
			// add new
			m_objects.add({ name, object });
		}

		/// <summary>
		/// Removes the Object with the given name.
		/// </summary>
		/// <param name="name">The name of the Object.</param>
		/// <returns>True if an Object was removed.</returns>
		Bool remove(String const& name)
		{
			// find the object and remove it
			for (Size i = 0; i < m_objects.get_size(); ++i)
			{
				if (m_objects[i].get_first() == name)
				{
					m_objects.remove(i);
					return true;
				}
			}

			// not found
			return false;
		}

		/// <summary>
		/// Finds the first occurrence of the given name.
		/// </summary>
		/// <param name="name">The name to find.</param>
		/// <returns>An iterator to the Object with the given name.</returns>
		Vector<Tuple<String, Object>>::Iterator find(String const& name)
		{
			auto it = m_objects.begin();
			while (it != m_objects.end())
			{
				if (it->get_first() == name)
				{
					return it;
				}
				++it;
			}
			return it;
		}

		/// <summary>
		/// Finds the first occurrence of the given name.
		/// </summary>
		/// <param name="name">The name to find.</param>
		/// <returns>An iterator to the Object with the given name.</returns>
		Vector<Tuple<String, Object>>::ConstIterator find(String const& name) const
		{
			auto it = m_objects.begin();
			while (it != m_objects.end())
			{
				if (it->get_first() == name)
				{
					return it;
				}
				++it;
			}
			return it;
		}

		/// <summary>
		/// Packs the data within this Cargo into a byte array.
		/// </summary>
		/// <returns>A ConstContainer with the byte array.</returns>
		ConstantContainer pack() const;

#pragma endregion
	};
}