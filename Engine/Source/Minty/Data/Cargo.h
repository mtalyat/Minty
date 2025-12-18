#ifndef MINTY_DATA_CARGO_H
#define MINTY_DATA_CARGO_H

/**
 * @file Cargo.h
 * @brief Header file for the Cargo class.
 * @author Mitchell Talyat
 */

#include "Minty/Data/ConstantContainer.h"
#include "Minty/Data/Object.h"
#include "Minty/Data/String.h"
#include "Minty/Data/Variable.h"
#include "Minty/Data/Vector.h"

namespace Minty
{
	/**
	 * @class Cargo
	 * @brief A collection of named Objects, each containing Variables.
	 */
	class Cargo
	{
#pragma region Constructors

	public:
		/**
		 * @brief Creates an empty Cargo.
		 */
		Cargo();

		/**
		 * @brief Creates a Cargo with the given initial capacity.
		 * @param capacity The initial capacity.
		 */
		Cargo(Size const capacity);

		/**
		 * @brief Creates a Cargo with the given list of named Objects.
		 * @param list A list of names and Objects.
		 */
		Cargo(std::initializer_list<Tuple<String, Vector<Tuple<String, Variable>>>> const& list);

#pragma endregion

#pragma region Iterators

	public:
		using Iterator = Vector<Tuple<String, Object>>::Iterator;
		using ConstIterator = Vector<Tuple<String, Object>>::ConstIterator;

		Iterator begin() { return m_objects.begin(); }
		ConstIterator begin() const { return m_objects.begin(); }
		Iterator end() { return m_objects.end(); }
		ConstIterator end() const { return m_objects.end(); }

#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Checks if this Cargo is empty.
		 * @returns True if no Objects are in this Cargo.
		 */
		inline Bool is_empty() const { return m_objects.is_empty(); }

		/**
		 * @brief Gets the number of Objects in this Cargo.
		 * @returns The size.
		 */
		inline Size get_size() const { return m_objects.get_size(); }

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Checks if this Cargo has an Object with the given name.
		 * @param name The name of the Object.
		 * @returns True if an Object with the given name exists.
		 */
		Bool contains(String const& name) const;

		/**
		 * @brief Gets the Object with the given name.
		 * @param name The name of the Object.
		 * @returns The Object.
		 */
		Object& at(String const& name);

		/**
		 * @brief Gets the Object with the given name.
		 * @param name The name of the Object.
		 * @returns The Object.
		 */
		Object const& at(String const& name) const;

		/**
		 * @brief Adds an Object to this Cargo.
		 * @param name The name of the Object.
		 * @param object The Object.
		 */
		void add(String const& name, Object const& object);

		/**
		 * @brief Sets the Object with the given name.
		 * @param name The name of the Object.
		 * @param object The Object.
		 */
		void set(String const& name, Object const& object);
			
		/**
		 * @brief Removes the Object with the given name.
		 * @param name The name of the Object.
		 * @returns True if the Object was found and removed.
		 */
		Bool remove(String const& name);

		/**
		 * @brief Finds the first occurrence of the given name.
		 * @param name The name to find.
		 * @returns An iterator to the Object with the given name.
		 */
		Iterator find(String const& name);

		/**
		 * @brief Finds the first occurrence of the given name.
		 * @param name The name to find.
		 * @returns An iterator to the Object with the given name.
		 */
		ConstIterator find(String const& name) const;

		/**
		 * @brief Packs this Cargo into a ConstantContainer.
		 * @returns The packed ConstantContainer.
		 */
		ConstantContainer pack() const;

#pragma endregion

#pragma region Variables

	private:
		Vector<Tuple<String, Object>> m_objects;

#pragma endregion
	};
}

#endif // MINTY_DATA_CARGO_H