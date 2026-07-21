#pragma once

/**
 * @file Object.hpp
 * @brief Defines the Object class for a collection of named Variables.
 * @author Mitchell Talyat
 */

#include "Variable.hpp"
#include "Core/Data/Vector.hpp"
#include "Core/Data/Tuple.hpp"
#include "Core/Data/String.hpp"
#include "Core/Data/ConstantContainer.hpp"
#include "Core/Serialize/Serializer.hpp"

namespace Minty
{
	/**
	 * @class Object
	 * @brief A collection of named Variables.
	 */
	class Object
	{
		friend struct Serializer<Object>;

#pragma region Constructors

	public:
		/**
		 * @brief Creates an empty Object.
		 */
		Object();

		/**
		 * @brief Creates an empty Object with the given name and capacity.
		 * @param capcity The Variable capacity.
		 */
		Object(Size const capcity);

		/**
		 * @brief Creates an Object with the given name and list of Variables.
		 * @param list A list of names and Variables.
		 */
		Object(std::initializer_list<Tuple<String, Variable>> const& list);

		/**
		 * @brief Creates an Object with the given name and list of Variables.
		 * @param variables The Variables.
		 */
		
		Object(Vector<Tuple<String, Variable>> const& variables);
#pragma endregion

#pragma region Accessors

	public:
		/**
		 * @brief Gets a Vector of all the Variables in this Object.
		 * @return The list.
		 */
		inline Vector<Tuple<String, Variable>> const& get_variables() const { return m_variables; }

		/**
		 * @brief Gets a Vector of all the Variables in this Object.
		 * @return The list.
		 */
		inline Size get_variable_count() const { return m_variables.get_size(); }

		/**
		 * @brief Gets the number of bytes this Object would take up if packed.
		 * @return The size in bytes.
		 */
		Size get_size() const;

		/**
		 * @brief Checks if this Object is empty.
		 * @return True if no Variables are in this Object.
		 */
		inline Bool is_empty() const { return m_variables.is_empty(); }

#pragma endregion

#pragma region Methods

	public:
		/**
		 * @brief Checks if this Object has a Variable with the given name.
		 * @param name The name of the Variable.
		 * @return True if a Variable with the given name exists.
		 */
		Bool contains(StringView const name) const;

		/**
		 * @brief Gets the Variable with the given name.
		 * @param name The name of the Variable.
		 * @return A const reference to the Variable.
		 */
		Variable const& at(StringView const name) const;

		/**
		 * @brief Gets the Variable with the given name.
		 * @param name The name of the Variable.
		 * @return A const reference to the Variable.
		 */
		Variable& at(StringView const name);

		/**
		 * @brief Adds a Variable to this Object.
		 * @param name The name of the Variable.
		 * @param variable The Variable.
		 */
		void add(StringView const name, Variable const& variable);

		/**
		 * @brief Adds a Variable to this Object.
		 * @param name The name of the Variable.
		 * @param variable The Variable.
		 */
		void add(StringView const name, Variable&& variable);

		/**
		 * @brief Sets the Variable with the given name.
		 * @param name The name of the Variable.
		 * @param variable The Variable.
		 */
		void set(StringView const name, Variable const& variable);

		/**
		 * @brief Removes the Variable with the given name.
		 * @param name The name of the Variable.
		 * @return True if a Variable with the given name was removed.
		 */
		Bool remove(StringView const name);

		/**
		 * @brief Packs the data within this Cargo into a byte array.
		 * @return A ConstContainer containing the byte data.
		 */
		ConstantContainer pack() const;

#pragma endregion

#pragma region Variables

	private:
		Vector<Tuple<String, Variable>> m_variables;

#pragma endregion
	};

	template<>
	struct Serializer<Object>
	{
		static Bool serialize(Writer& writer, Object const& value);
		static Bool deserialize(Reader& reader, Object& value);
	};
}
