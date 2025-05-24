#pragma once
#include "Minty/Core/Types.h"
#include "Minty/Data/Lookup.h"
#include "Minty/Data/UUID.h"
#include "Minty/Serialization/Reader.h"
#include "Minty/Serialization/SerializableObject.h"
#include "Minty/Serialization/Writer.h"

namespace Minty
{
	/// <summary>
	/// A Scope is a collection of values.
	/// </summary>
	template<Comparable T>
	class Scope
		: public SerializableObject
	{
#pragma region Variables

	private:
		Lookup<UUID, T> m_values;

#pragma endregion

#pragma region Constructors

	public:
		/// <summary>
		/// Creates a new Scope.
		/// </summary>
		Scope()
			: m_values()
		{
		}

		~Scope()
		{
		}

#pragma endregion

#pragma region Get Set

	public:
		/// <summary>
		/// Gets the value of the variable with the given name.
		/// </summary>
		/// <param name="key">The ID of the variable.</param>
		/// <returns>The value of the variable.</returns>
		T const& get_value(UUID const key) const { return m_values.at(key); }

		/// <summary>
		/// Gets the name of the variable with the given ID.
		/// </summary>
		/// <param name="key">The ID.</param>
		/// <returns>The name.</returns>
		String const& get_name(UUID const key) const { return m_values.get_string(key); }

#pragma endregion

#pragma region Methods

	public:
		/// <summary>
		/// Checks if this Scope contains the given variable.
		/// </summary>
		/// <param name="key">The ID of the variable.</param>
		/// <returns></returns>
		Bool contains(UUID const key) const { return m_values.contains(key); }

		/// <summary>
		/// Finds the ID of the variable with the given name.
		/// </summary>
		/// <param name="name">The name of the variable to find.</param>
		/// <returns>The UUID of the variable, or INVALID_ID if none found.</returns>
		UUID find(String const& name) const
		{
			auto found = m_values.find(name);
			if (found == m_values.end())
			{
				return INVALID_ID;
			}
			return found->get_second();
		}

		/// <summary>
		/// Adds the given value to this Scope.
		/// </summary>
		/// <param name="name">The name of the variable to create.</param>
		/// <param name="value">The initial value of the variable.</param>
		/// <returns>The ID of the variable.</returns>
		UUID add(String const& name, T const& value)
		{
			UUID id = UUID::create();
			m_values.add(name, id, value);
			return id;
		}

		/// <summary>
		/// Sets the value of the variable with the given ID.
		/// </summary>
		/// <param name="id">The ID.</param>
		/// <param name="value">The value.</param>
		void set(UUID const id, T const& value)
		{
			MINTY_ASSERT(m_values.contains(id), F("ID does not exist: {}", id));
			m_values.at(id) = value;
		}

		/// <summary>
		/// Removes all variables from this Scope.
		/// </summary>
		void clear()
		{
			m_values.clear();
		}

		/// <summary>
		/// Zeros all variables in this Scope.
		/// </summary>
		void reset()
		{
			for (auto&& [string, key, value] : m_values)
			{
				memset(&value, 0, sizeof(T));
			}
		}

		void serialize(Writer& writer) const override
		{
			// write each name: value in the scope as a pair
			for (auto const& [string, key, value] : m_values)
			{
				writer.write(string, value);
			}
		}
		Bool deserialize(Reader& reader) override
		{
			clear();

			// read each name: value in the scope as a pair
			String name;
			T value;
			for (Size i = 0; i < reader.get_size(); i++)
			{
				if (!reader.read_name(i, name))
				{
					MINTY_ERROR(F("Reader failed to read name {}.", i));
					continue;
				}

				if (!reader.read(i, value))
				{
					MINTY_ERROR(F("Reader failed to read value {}.", i));
					continue;
				}

				// add to scope
				UUID id = UUID::create();
				m_values.add(name, id, value);
			}

			return true;
		}

#pragma endregion
	};

	using BasicScope = Scope<Int>;
}