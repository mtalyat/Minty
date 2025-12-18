#ifndef MINTY_DATA_SCOPE_H
#define MINTY_DATA_SCOPE_H

/**
 * @file Scope.h
 * @brief Defines the Scope class for managing named variables.
 * @author Mitchell Talyat
 */

#include "Minty/Core/Types.h"
#include "Minty/Data/Lookup.h"
#include "Minty/Data/UUID.h"
#include "Minty/Serialization/SerializableObject.h"

namespace Minty
{
	/**
	 * @class Scope
	 * @brief Manages a collection of named variables identified by UUIDs.
	 */
	class Scope
		: public SerializableObject
	{
#pragma region Iterators

	public:
		using Iterator = typename Lookup<UUID, Int>::Iterator;
		using ConstIterator = typename Lookup<UUID, Int>::ConstIterator;

		inline Iterator begin() { return m_values.begin(); }
		inline Iterator end() { return m_values.end(); }
		inline ConstIterator begin() const { return m_values.begin(); }
		inline ConstIterator end() const { return m_values.end(); }

#pragma endregion

#pragma region Constructors

	public:
		/**
		 * @brief Creates an empty Scope.
		 */
		Scope();

		~Scope() = default;

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets the value of the variable with the given ID.
		 * @param key The ID.
		 * @returns The value.
		 */
		inline Int const &get_value(UUID const key) const { return m_values.at(key); }

		/**
		 * @brief Gets the name of the variable with the given ID.
		 * @param key The ID.
		 * @returns The name.
		 */
		inline String const &get_name(UUID const key) const { return m_values.get_string(key); }

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Checks if a variable with the given ID exists in this Scope.
		 * @param key The ID.
		 * @returns True if the variable exists.
		 */
		inline Bool contains(UUID const key) const { return m_values.contains(key); }

		/**
		 * @brief Finds the ID of the variable with the given name.
		 * @param name The name of the variable.
		 * @returns The ID of the variable, or UUID() if not found.
		 */
		UUID find(String const &name) const;

		/**
		 * @brief Adds a variable with the given name and value to this Scope.
		 * @param name The name of the variable.
		 * @param value The initial value of the variable.
		 * @returns The ID of the variable.
		 */
		UUID add(String const &name, Int const value);

		/**
		 * @brief Sets the value of the variable with the given ID.
		 * @param id The ID.
		 * @param value The new value.
		 */
		void set(UUID const id, Int const value);

		/**
		 * @brief Clears all variables from this Scope.
		 */
		inline void clear() { m_values.clear(); }

		/**
		 * @brief Resets all variable values in this Scope to zero.
		 */
		void reset();

		void serialize(Writer &writer) const override;
		Bool deserialize(Reader &reader) override;

#pragma endregion

#pragma region Variables

	private:
		Lookup<UUID, Int> m_values;

#pragma endregion
	};
}

#endif // MINTY_DATA_SCOPE_H